#include "Simulator.h"
#include "Drone.h"
#include "Block.h"

extern "C" {
#include "nav/nav.h"
}

#include <cmath>
#include <iostream>

Drone::Drone(Vector2D Pos, int Size) : SimObject(Pos), Size(Size), Angle(0), sonar(57, 15.0) { }

void Drone::draw() {
    // Drone
    Sim->Render->drawCircleRel(Pos, Size / 2);

    // Direction line
    Sim->Render->setColor({255, 0, 0});
    Sim->Render->drawLineRel(Pos, {Pos.x + int(sin(Angle) * Size / 2), Pos.y + int(cos(Angle) * Size / 2)});

    // Sonar
    Sim->Render->setColor({255, 0, 0}, 100);
    //Sim->Render->drawPieRel(Pos, 500, int(rad_to_deg(Angle) - 7.5), int(rad_to_deg(Angle) + 7.5));
    Sim->Render->drawLineRel(Pos, {Pos.x + int(sin(Angle) * 500), Pos.y + int(cos(Angle) * 500)});

    // Laser
    Sim->Render->setColor({0, 0, 255}, 100);
    //Sim->Render->drawPieRel(Pos, 400, int(rad_to_deg(Angle) - 135), int(rad_to_deg(Angle) + 135));
}

void Drone::update() {
    //calcLaserDist();
    //calcSonarDist();

    rep_t rep;
    nav_t nav; //don't know what to do with this
    init_nav(&nav);
    init_rep(&FC, &Laser, &(sonar.sonar), &IrTop, &IrBottom, &rep);

    sonar.calcDist(Sim->Blocks);

    //Pos.X += 1;
    Pos.x = 500;
    Pos.y = 525;

    navigation(&rep, &nav);

    Angle = Angle + 0.05;
    if (Angle > M_PI * 2)
        Angle = 0;

    //if (Pos.X > 575)
    //    Pos.X = 475;
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
