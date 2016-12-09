#include "Drone.h"

Drone::Drone(Vector2D Pos, int Size) : SimObject(Pos), Size(Size), Angle(M_PI),
                                       SonarModule(Pos, 57, Angle, DegToRad(15), 220),
                                       LaserModule(Pos, 400.0, Angle),
                                       Height(0) {
    //Initialize the structs
    init_fc(&FC, SERIAL0, 1);
    IrTop = *IR_init(A0);
    IrBottom = *IR_init(A1);
    IrBottom.value = 80;

    init_nav(&NavigationStruct);
    init_rep(&FC, &LaserModule.Struct, &SonarModule.Struct, &IrTop, &IrBottom, &WorldRepresentation);

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
    Sim->Render->setColor(BLACK);
    Sim->Render->drawCircleRel(Pos, Size / 2);

    // Direction line
    Sim->Render->setColor(RED);
    Sim->Render->drawLineRel(Pos, {Pos.X + int(cos(Angle) * Size / 2), Pos.Y + int(sin(Angle) * Size / 2)});

    // Modules
    SonarModule.draw();
    LaserModule.draw();
}

void Drone::update() {
    SonarModule.calcDist(Sim->Blocks, Pos, Angle);
    LaserModule.calcDist(Sim->Blocks, Pos, Angle);

    if((Sim->Time - LastNavUpdate) >= NAV_UPDATE_TIME) {
        navigation(&WorldRepresentation, &NavigationStruct);
        LastNavUpdate = Sim->Time;
    }
    updateFromFC();
}

double Drone::calcAcceleration(double PrevVel, double NewVel) {
    return (NewVel - PrevVel) / (Sim->DeltaTime / MS_PR_SEC);
}

double Drone::calcVelocity(double DirectionValue, const double Speed) {
    return (DirectionValue - FC_OFFSET) * Speed;
}

double Drone::calcDistance(const double Speed, double DeltaTime) {
    return Speed * (DeltaTime / MS_PR_SEC);
}

void Drone::updateYaw(uint16_t YawValue) {
    //Check rotation and update, 1 means right, -1 means left and 0 means no rotation
    double YawVelocity = calcVelocity(YawValue, ROTATION_SPEED);
    double YawDistance = calcDistance(YawVelocity, Sim->DeltaTime);

    Angle -= YawDistance;
    if (Angle >= M_PI * 2)
        Angle -= M_PI * 2;
    else if (Angle <= 0)
        Angle += M_PI * 2;

    //Update gyro with deg/sec
    FC.gyro = fix16_from_dbl(RadToDeg(abs(YawVelocity)));
}

void Drone::updateRoll(uint16_t RollValue) {
    double RollVelocity = calcVelocity(RollValue, STRAFE_SPEED);
    double RollDistance = calcDistance(RollVelocity, Sim->DeltaTime);
    //double OrthogAngle = Angle + NINETY_DEGREES_IN_RAD + ROTATION_OFFSET;
    double OrthogAngle = Angle + NINETY_DEGREES_IN_RAD;

    Pos.X += cos(OrthogAngle) * RollDistance;
    Pos.Y += sin(OrthogAngle) * RollDistance;

    float PrevVel = FC.vel->x;
    FC.acc->x = fix16_from_dbl(calcAcceleration(PrevVel, RollVelocity));
    FC.vel->x = fix16_from_dbl(RollVelocity);
}

void Drone::updatePitch(uint16_t PitchValue) {
    //Calculate the direction of movement
    double PitchVelocity = calcVelocity(PitchValue, MOVEMENT_SPEED);
    double PitchDistance = calcDistance(PitchVelocity, Sim->DeltaTime);

    //Calculate the new position of the drone
    Pos.X += cos(Angle) * PitchDistance;
    Pos.Y += sin(Angle) * PitchDistance;

    float PrevVel = FC.vel->y;
    FC.acc->y = fix16_from_dbl(calcAcceleration(PrevVel, PitchVelocity));
    FC.vel->y = fix16_from_dbl(PitchVelocity);
}

void Drone::updateThrottle(uint16_t ThrottleValue) {
    //Calculate the altitude velocity based on input from FC
    double ThrottleVelocity = calcVelocity(ThrottleValue, ALTITUDE_SPEED);
    double ThrottleDistance = calcDistance(ThrottleVelocity, Sim->DeltaTime);

    //Update height field and IR-sensors
    Height += ThrottleDistance;
    uint16_t DistToFloor = Height;
    if(DistToFloor >= IR_MAX_DIST_CM)
        IrBottom.value = IR_MAX_DIST_CM;
    else if (DistToFloor < IR_MIN_DIST_CM)
        IrBottom.value = IR_MIN_DIST_CM;
    else
        IrBottom.value = DistToFloor;

    uint16_t DistToCeil = ROOM_HEIGHT - Height;
    if(DistToCeil >= IR_MAX_DIST_CM)
        IrTop.value = IR_MAX_DIST_CM;
    else if (DistToCeil < IR_MIN_DIST_CM)
        IrTop.value = IR_MIN_DIST_CM;
    else
        IrTop.value = DistToCeil;

    float PrevVel = FC.vel->z;
    FC.acc->z = fix16_from_dbl(calcAcceleration(PrevVel, ThrottleVelocity));
    FC.vel->z = fix16_from_dbl(ThrottleVelocity);
}

void Drone::updateFromFC() {
    updateYaw(FC.yaw);
    updatePitch(FC.pitch);
    updateRoll(FC.roll);
    updateThrottle(FC.throttle);
}
