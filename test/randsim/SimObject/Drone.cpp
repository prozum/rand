#include "Drone.h"

Drone::Drone(Vector2D Pos, int Size) : SimObject(Pos), Size(Size), Angle(M_PI), SonarModule(Pos, 57, DegToRad(0), DegToRad(15), 220), Height(0) {
    //Initialize the structs
    init_fc(&FC, SERIAL0, 1);
    IrTop = *IR_init(A0);
    IrBottom = *IR_init(A1);
    IrBottom.value = 80;
    Laser = *laser_init(TX1);

    init_nav(&NavigationStruct);
    init_rep(&FC, &Laser, &(SonarModule.SonarStruct), &IrTop, &IrBottom, &WorldRepresentation);

    //Set FC duties to simplify movement for this simulation
    FC.duty->MIN_FC_DUTY = 0 * FC_OFFSET;
    FC.duty->MID_FC_DUTY = 1 * FC_OFFSET;
    FC.duty->MAX_FC_DUTY = 2 * FC_OFFSET;

    //Makes sure the drone starts in a non-moving state
    rotate_stop(&FC);
    move_stop(&FC);
    TimeCounter = 0;
}

void Drone::draw() {
    // Drone
    Sim->Render->setColor({0, 0, 0});
    Sim->Render->drawCircleRel(Pos, Size / 2);

    // Direction line
    Sim->Render->setColor({255, 0, 0});
    Sim->Render->drawLineRel(Pos, {Pos.X + int(cos(Angle) * Size / 2), Pos.Y + int(sin(Angle) * Size / 2)});

    // Sonar
    Sim->Render->setColor({255, 0, 0}, 100);
    Sim->Render->drawPieRel(Pos, 500, int(RadToDeg(-Angle) - 7.5), int(RadToDeg(-Angle) + 7.5));
    Sim->Render->drawLineRel(Pos, {Pos.X + int(cos(Angle) * 500), Pos.Y + int(sin(Angle) * 500)});

    // Laser
    Sim->Render->setColor({0, 0, 255}, 100);
    Sim->Render->drawPieRel(Pos, 400, int(RadToDeg (-Angle) - 135), int(RadToDeg(-Angle) + 135));
}

void Drone::update() {
    TimeCounter += Sim->DeltaTime_Millis;
    //calcLaserDist();
    //calcSonarDist();

    //Uncomment to make the drone fly in a box-shape
    /*if(counter == 0) {
        move_stop(&FC);
        rotate_right(&FC);
    }

    if(counter == 100) {
        move_stop(&FC);
        move_left(&FC);
    }
    else if(counter == 200) {
        move_stop(&FC);
        move_forward(&FC);
    }
    else if (counter == 300) {
        move_stop(&FC);
        move_right(&FC);
    }
    else if (counter == 400) {
        move_stop(&FC);
        move_back(&FC);
        counter = 0;
    }
    counter++;*/

    //Uncomment here to move in circles
    /*if(counter % 1 == 0) {
        rotate_right(&FC);
    }
    else
        rotate_stop(&FC);
    counter++;*/
    SonarModule.calcDist(Sim->Blocks, Pos, Angle);

    if(TimeCounter > PERIOD) {
        navigation(&WorldRepresentation, &NavigationStruct);
        TimeCounter = 0;
    }

    updateFromFC();
}

double calculateVelocity(uint8_t direction_value, const float SPEED) {
    double dv_f = (double) direction_value;
    return (dv_f - FC_OFFSET) * SPEED;
}

float Drone::calculateAcceleration(float prev_vel, float new_vel) {
    return (new_vel - prev_vel) / (Sim->DeltaTime_Millis / 1000);
}

void Drone::updateRotation(uint16_t yaw_value) {
    //Check rotation and update, 1 means right, -1 means left and 0 means no rotation
    double rotationVelocity = calculateVelocity(yaw_value, ROTATION_SPEED);
    Angle = Angle + rotationVelocity;
    if (Angle > M_PI * 2)
        Angle = 0;

    //Update gyro with deg/sec
    FC.gyro = fix16_from_dbl(RadToDeg(rotationVelocity));
}

void Drone::updateStrafe(uint16_t roll_value) {
    double strafeVelocity = calculateVelocity(roll_value, STRAFE_SPEED);
    double orthogAngle = Angle + NINETY_DEGREES_IN_RAD + ROTATION_OFFSET;

    Pos.X += strafeVelocity * cos(orthogAngle);
    Pos.Y += strafeVelocity * sin(orthogAngle);

    float prev_vel = FC.vel->x;
    FC.acc->x = fix16_from_float(calculateAcceleration(prev_vel, strafeVelocity));
    FC.vel->x = fix16_from_dbl(strafeVelocity);
}

void Drone::updateFrontal(uint16_t pitch_value) {
    //Calculate the direction of movement
    double moveVelocity = -calculateVelocity(pitch_value, MOVEMENT_SPEED);

    double conv_angle = Angle + ROTATION_OFFSET;

    //Calculate the new position of the drone
    Pos.X += cos(conv_angle) * moveVelocity;
    Pos.Y += sin(conv_angle) * moveVelocity;

    float prev_vel = FC.vel->y;
    FC.acc->y = fix16_from_float(calculateAcceleration(prev_vel, moveVelocity));
    FC.vel->y = fix16_from_dbl(moveVelocity);
}

void Drone::updateHeight(uint16_t throttle_value) {
    //Calculate the altitude velocity based on input from FC
    double altitudeVelocity = calculateVelocity(throttle_value, ALTITUDE_SPEED);

    //Update height field and IR-sensors
    Height += altitudeVelocity;
    uint16_t dist_to_floor = Height;
    if(dist_to_floor >= IR_MAX_DIST_CM)
        IrBottom.value = IR_MAX_DIST_CM;
    else if (dist_to_floor < IR_MIN_DIST_CM)
        IrBottom.value = IR_MIN_DIST_CM;
    else
        IrBottom.value = dist_to_floor;

    uint16_t dist_to_ceil = ROOM_HEIGHT - Height;
    if(dist_to_ceil >= IR_MAX_DIST_CM)
        IrTop.value = IR_MAX_DIST_CM;
    else if (dist_to_ceil < IR_MIN_DIST_CM)
        IrTop.value = IR_MIN_DIST_CM;
    else
        IrTop.value = dist_to_ceil;

    float prev_vel = FC.vel->z;
    FC.acc->z = fix16_from_float(calculateAcceleration(prev_vel, altitudeVelocity));
    FC.vel->z = fix16_from_dbl(altitudeVelocity);
}

void Drone::updateFromFC() {
    updateRotation(FC.yaw);
    updateFrontal(FC.pitch);
    updateStrafe(FC.roll);
    updateHeight(FC.throttle);
}

/*
void Drone::calcSonarDist() {
    int HalfBlock = Block::Size / 2;

    auto leftSonarAngle = Angle + 0.13;
    auto rightSonarAngle = Angle - 0.13;

    double closest = 0;

    for (auto B : Sim->Blocks) {
        if (Pos.X >= B.Pos.X + HalfBlock &&
            Pos.Y >= B.Pos.Y + HalfBlock) {
            auto bTopAngle = calcAngle(B.Pos.X + HalfBlock, B.Pos.Y - HalfBlock);
            auto bMidAngle = calcAngle(B.Pos.X + HalfBlock, B.Pos.Y + HalfBlock);
            auto bBotAngle = calcAngle(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);

            if (bTopAngle <= rightSonarAngle && bMidAngle >= rightSonarAngle &&
                bBotAngle >= leftSonarAngle && bMidAngle <= leftSonarAngle) {
                auto d = calcDist(B.Pos.X + HalfBlock, B.Pos.Y + HalfBlock);
                if (closest == 0 || (d > closest && d <= 220)) {
                    closest = d;
                }
            } else if (bTopAngle > rightSonarAngle &&
                       bMidAngle >= leftSonarAngle) {
                auto d = calcDist(B.Pos.X + HalfBlock, B.Pos.Y + HalfBlock);
                if (closest == 0 || (d > closest && d <= 220)) {
                    closest = d;
                }
            } else if (bBotAngle > leftSonarAngle &&
                       bMidAngle <= rightSonarAngle) {
                auto d = calcDist(B.Pos.X + HalfBlock, B.Pos.Y + HalfBlock);
                if (closest == 0 || (d > closest && d <= 220)) {
                    closest = d;
                }
            } else {
                break;
            }
        } else if (Pos.X <= B.Pos.X - HalfBlock &&
                   Pos.Y >= B.Pos.Y + HalfBlock) {
            auto bTopAngle = calcAngle(B.Pos.X - HalfBlock, B.Pos.Y - HalfBlock);
            auto bMidAngle = calcAngle(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);
            auto bBotAngle = calcAngle(B.Pos.X + HalfBlock, B.Pos.Y + HalfBlock);

            if (bTopAngle >= leftSonarAngle && bMidAngle <= bTopAngle &&
                bBotAngle <= rightSonarAngle && bMidAngle >= rightSonarAngle) {
                auto d = calcDist(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);
                if (closest == 0 || (d > closest && d <= 220)) {
                    closest = d;
                }
            } else if (bTopAngle > rightSonarAngle &&
                       bMidAngle >= leftSonarAngle) {
                auto d = calcDist(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);
                if (closest == 0 || (d > closest && d <= 220)) {
                    closest = d;
                }
            } else if (bBotAngle > leftSonarAngle &&
                       bMidAngle <= rightSonarAngle) {
                auto d = calcDist(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);
                if (closest == 0 || (d > closest && d <= 220)) {
                    closest = d;
                }
            } else {
                break;
            }
        } else if (Pos.X <= B.Pos.X - HalfBlock &&
                   Pos.Y >= B.Pos.Y - HalfBlock) {
            auto bTopAngle = calcAngle(B.Pos.X + HalfBlock, B.Pos.Y - HalfBlock);
            auto bMidAngle = calcAngle(B.Pos.X - HalfBlock, B.Pos.Y - HalfBlock);
            auto bBotAngle = calcAngle(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);

        } else if (Pos.X <= B.Pos.X + HalfBlock &&
                   Pos.Y >= B.Pos.Y - HalfBlock) {
            auto bTopAngle = calcAngle(B.Pos.X + HalfBlock, B.Pos.Y - HalfBlock);
            auto bMidAngle = calcAngle(B.Pos.X + HalfBlock, B.Pos.Y + HalfBlock);
            auto bBotAngle = calcAngle(B.Pos.X - HalfBlock, B.Pos.Y + HalfBlock);

        } else if (Pos.X >= B.Pos.X - HalfBlock &&
                   Pos.X <= B.Pos.X + HalfBlock &&
                   Pos.Y >= B.Pos.Y + HalfBlock) {

        } else if (Pos.X <= B.Pos.X - HalfBlock &&
                   Pos.Y >= B.Pos.Y - HalfBlock &&
                   Pos.Y <= B.Pos.Y + HalfBlock) {

        } else if (Pos.X >= B.Pos.X - HalfBlock &&
                   Pos.X <= B.Pos.X + HalfBlock &&
                   Pos.Y <= B.Pos.Y - HalfBlock) {

        } else if (Pos.X >= B.Pos.X + HalfBlock &&
                   Pos.Y >= B.Pos.Y - HalfBlock &&
                   Pos.Y <= B.Pos.Y + HalfBlock) {

        }

        std::cout << "Block: x: " << B.Pos.X << " y: " << B.Pos.Y << std::endl;
        std::cout << "Drone: x: " <<   Pos.X << " y: " <<   Pos.Y << std::endl;
        std::cout << "X1: " << X1 << " Y1: " << Y1 << std::endl;
        std::cout << "X2: " << X2 << " Y2: " << Y2 << std::endl;
        Dist = sqrt(X1 * X1 + Y1 * Y1);
        std::cout << "Delta: " << Dist << std::endl;


        StartAngle = atan((abs(DeltaX) - Block::Size / 2) / (abs(DeltaX) + Block::Size / 2));
        EndAngle =   M_PI / 2 - atan((abs(DeltaY) - Block::Size / 2) / (abs(DeltaY) + Block::Size / 2));
        std::cout << "Start Angle: " << StartAngle << " End Angle: " << EndAngle << std::endl;
        std::cout << "Angle: " << Angle << std::endl;
        std::cout << "Found: " << (Angle < StartAngle && Angle > EndAngle) << std::endl;
    //}
    }
}
 */

/*
void Drone::calcLaserDist() {

    int Radius = Size/2;
    auto B = Sim->Blocks[0];

    int LRange = 400;


    int MaxDist = 2200;
    double DeltaX, DeltaY, Dist;
    int X1, X2, Y1, Y2;
    double StartAngle, EndAngle;
    int HalfBlock = Block::Size / 2;

    //for (auto B : Sim->Blocks) {
    X1 = abs(B.Pos.X - HalfBlock - Pos.X);
    X2 = abs(B.Pos.X + HalfBlock - Pos.X);

    Y1 = abs(B.Pos.Y - HalfBlock - Pos.Y);
    Y2 = abs(B.Pos.Y + HalfBlock - Pos.Y);

    DeltaX = abs(B.Pos.X - Pos.X);
    DeltaY = abs(B.Pos.Y - Pos.Y);

    // Distance
    std::cout << "Block: x: " << B.Pos.X << " y: " << B.Pos.Y << std::endl;
    std::cout << "Drone: x: " <<    Pos.X << " y: " <<    Pos.Y << std::endl;
    std::cout << "X1: " << X1 << " Y1: " << Y1 << std::endl;
    std::cout << "X2: " << X2 << " Y2: " << Y2 << std::endl;
    Dist = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
    Laser.front_value = Dist;


    StartAngle = atan((abs(DeltaX) - Block::Size / 2) / (abs(DeltaX) + Block::Size / 2));
    EndAngle =   M_PI / 2 - atan((abs(DeltaY) - Block::Size / 2) / (abs(DeltaY) + Block::Size / 2));
    std::cout << "Start Angle: " << StartAngle << " End Angle: " << EndAngle << std::endl;
    std::cout << "Angle: " << Angle << std::endl;
    std::cout << "Found: " << (Angle < StartAngle && Angle > EndAngle) << std::endl;
    //}
}
*/
