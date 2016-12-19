#include "Vector2D.h"

Vector2D::Vector2D() : X(0), Y(0) {}

Vector2D::Vector2D(const Vector2D &vector) : X(vector.X), Y(vector.Y) {}

Vector2D::Vector2D(double X, double Y) : X(X), Y(Y) {}
Vector2D::Vector2D(int X, int Y) : X(X), Y(Y) {}

Vector2D Vector2D::operator*(const double &Arg) { return Vector2D(this->X * Arg, this->Y * Arg); }

Vector2D Vector2D::operator+(const Vector2D &Arg) { return Vector2D(this->X + Arg.X, this->Y + Arg.Y); }

Vector2D Vector2D::operator-(const Vector2D &Arg) { return Vector2D(this->X - Arg.X, this->Y - Arg.Y); }

void Vector2D::compose(double Length, double Angle) {
    X = cos(Angle) * Length;
    Y = sin(Angle) * Length;
}

double Vector2D::determinant(Vector2D &V) { return (X * V.Y) - (Y * V.X); }

double Vector2D::dot(Vector2D &V) { return (X * V.X) + (Y * V.Y); }

double Vector2D::length() { return sqrt(pow(X, 2) + pow(Y, 2)); }

Vector2D Vector2D::invert() { return Vector2D(1 / X, 1 / Y); }
