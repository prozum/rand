#include "Simulator.h"
#include "Drone.h"
#include "Block.h"

extern "C" {
#include "nav/nav.h"
}

#include <cmath>
#include <iostream>

Drone::Drone(Dot Pos, int Size) : SimObject(Pos), Size(Size), Angle(0) { }

void Drone::draw() {
    // Drone
    Sim->Render->drawCircleRel(Pos, Size / 2);

    // Direction line
    Sim->Render->setColor({255, 0, 0});
    Sim->Render->drawLineRel(Pos, {Pos.X + int(sin(Angle) * Size / 2), Pos.Y + int(cos(Angle) * Size / 2)});

    // Sonar
    Sim->Render->setColor({255, 0, 0}, 100);
    //Sim->Render->drawPieRel(Pos, 500, int(rad_to_deg(Angle) - 7.5), int(rad_to_deg(Angle) + 7.5));
    Sim->Render->drawLineRel(Pos, {Pos.X + int(sin(Angle) * 500), Pos.Y + int(cos(Angle) * 500)});

    // Laser
    Sim->Render->setColor({0, 0, 255}, 100);
    //Sim->Render->drawPieRel(Pos, 400, int(rad_to_deg(Angle) - 135), int(rad_to_deg(Angle) + 135));
}

void Drone::update() {
    calcSonarDist();
    navigation(&FC, &Laser, &Sonar, &IrTop, &IrBottom);

    //Pos.X += 1;
    Pos.Y = 525;
    Pos.X = 500;

    Angle = Angle + 0.01;
    if (Angle > M_PI * 2)
        Angle = 0;

    //if (Pos.X > 575)
    //    Pos.X = 475;
}

void Drone::calcSonarDist() {
    int MinDist = 2200;
    double DeltaX, DeltaY, Dist;
    int X1, X2, Y1, Y2;
    double StartAngle, EndAngle;
    int HalfBlock = Block::Size / 2;

    //for (auto B : Sim->Blocks) {
        auto B = Sim->Blocks[70];
        if (Pos.X > B.Pos.X - HalfBlock &&
            Pos.X < B.Pos.X + HalfBlock) {
            X1 = - HalfBlock;
            X2 = HalfBlock;
        } else {
            X1 = B.Pos.X - (Pos.X - HalfBlock);
            X2 = B.Pos.X - (Pos.X + HalfBlock);
        }

        if (Pos.Y > B.Pos.Y - HalfBlock &&
            Pos.Y < B.Pos.Y + HalfBlock) {
            Y1 = - HalfBlock;
            Y2 = HalfBlock;
        } else {
            Y1 = B.Pos.Y - (Pos.Y - HalfBlock);
            Y2 = B.Pos.Y - (Pos.Y + HalfBlock);
        }

        std::cout << "Block: x: " << B.Pos.X << " y: " << B.Pos.Y << std::endl;
        std::cout << "Drone: x: " <<    Pos.X << " y: " <<    Pos.Y << std::endl;
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

