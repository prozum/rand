#include "Drone.h"

Drone::Drone(Vector2D Pos, int Size) : SimObject(Pos), Size(Size), Angle(M_PI),
                                       SonarModule(Pos, 57, Angle, DegToRad(15), 220),
                                       LaserModule(Pos, 220.0, Angle),
                                       Height(0) {
    //Initialize the structs
    init_fc(&FC, SERIAL0, 1);
    IrTop = *IR_init(A0);
    IrBottom = *IR_init(A1);
    IrBottom.value = 80;

    init_nav(&NavigationStruct);
    init_rep(&FC, &Laser, &(SonarModule.SonarStruct), &IrTop, &IrBottom, &WorldRepresentation);

    //Set FC duties to simplify movement for this simulation
    FC.duty->MIN_FC_DUTY = 0 * FC_OFFSET;
    FC.duty->MID_FC_DUTY = 1 * FC_OFFSET;
    FC.duty->MAX_FC_DUTY = 2 * FC_OFFSET;

    //Makes sure the drone starts in a non-moving state
    rotate_stop(&FC);
    move_stop(&FC);
    LastNavUpdate = 0;
}

void Drone::draw() {
    // Drone
    Sim->Render->setColor({0, 0, 0});
    Sim->Render->drawCircleRel(Pos, Size / 2);

    // Direction line
    Sim->Render->setColor({255, 0, 0});
    Sim->Render->drawLineRel(Pos, {Pos.X + int(cos(Angle) * Size / 2), Pos.Y + int(sin(Angle) * Size / 2)});

    // Sonar
    SonarModule.draw();
    //LaserModule.
    //Sim->Render->setColor({255, 0, 0}, 100);
    //Sim->Render->drawPieRel(Pos, 500, int(RadToDeg(-Angle) - 7.5), int(RadToDeg(-Angle) + 7.5));
    //Sim->Render->drawLineRel(Pos, {Pos.X + int(cos(Angle) * 500), Pos.Y + int(sin(Angle) * 500)});

    // Laser
    //Sim->Render->setColor({0, 0, 255}, 100);
    //Sim->Render->drawPieRel(Pos, 400, int(RadToDeg (-Angle) - 135), int(RadToDeg(-Angle) + 135));
}

void Drone::update() {

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

    //rotate_left(&FC);

    SonarModule.calcDist(Sim->Blocks, Pos, Angle);

    if((Sim->Time - LastNavUpdate) >= NAV_UPDATE_TIME) {
        //navigation(&WorldRepresentation, &NavigationStruct);
        LastNavUpdate = Sim->Time;
    }
    rotate_right(&FC);
    updateFromFC();
}

double calculateVelocity(uint8_t direction_value, const float SPEED) {
    double dv_f = (double) direction_value;
    return (dv_f - FC_OFFSET) * SPEED;
}

float Drone::calculateAcceleration(float prev_vel, float new_vel) {
    return (new_vel - prev_vel) / (Sim->DeltaTime / 1000);
}

void Drone::updateRotation(uint16_t yaw_value) {
    //Check rotation and update, 1 means right, -1 means left and 0 means no rotation
    double rotationVelocity = -calculateVelocity(yaw_value, ROTATION_SPEED);
    Angle = Angle + rotationVelocity;
    if (Angle > M_PI * 2)
        Angle = Angle - M_PI * 2;
    else if (Angle < 0)
        Angle = Angle + M_PI * 2;

    //Update gyro with deg/sec
    //FC.gyro = fix16_from_dbl(RadToDeg(rotationVelocity));
    FC.gyro = fix16_from_dbl(RadToDeg(ROTATION_SPEED * 100));
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
