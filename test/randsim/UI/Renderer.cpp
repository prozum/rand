#include "Renderer.h"

#include <iomanip>

std::string DoubleToStr(double Double, int Precision) {
    std::ostringstream out;
    out << std::setprecision(Precision) << Double;
    return out.str();
}
