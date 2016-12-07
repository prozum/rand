#include "Sonar.h"

Sonar::Sonar(Vector2D Start, uint32_t RayCount, double Angle, double Span, double Length)
        : Length(Length), Angle(Angle), Span(Span), RayCount(RayCount) {

    double Resolution = Span / (double)RayCount;
    double StartAngle = Angle + (Span/2);

    for (int i = 0; i < RayCount; ++i) {
        Rays.push_back(Ray(Start, Length, Angle + StartAngle + (i * Resolution)));
    }
}

void Sonar::calcDist(std::vector<Block> Blocks, Vector2D& Origin, double Angle) {
    Vector2D Res;
    double TmpDist = INFINITY;
    double Dist = INFINITY;
    this->SonarStruct.valid = 0;

    update(Origin, Angle);

    for (auto Block : Blocks) {
        for (auto Ray : Rays) {
            bool Intersects = Block.intersection(Ray, Res);
            TmpDist = Res.length();
            if (Intersects && TmpDist <= Length) {
                Dist = std::min(TmpDist, Dist);
                printf("%lf\n", Dist);
                SonarStruct.valid = 1;
            }
        }
    }

    SonarStruct.value = (uint16_t)Dist;
}

void Sonar::update(Vector2D& Origin, double Angle) {
    for (auto Ray : Rays) {
        Ray.update(Origin, Angle);
    }
}