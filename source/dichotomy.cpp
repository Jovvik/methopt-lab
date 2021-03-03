#include "lab/dichotomy.h"

#include "lab/segment.h"

using namespace lab;

void Dichotomy::step() {
    calc_points();
    double new_start = segment.get_start();
    double new_end = segment.get_end();
    if (fx1 <= fx2) {
        new_end = x2;
    } else {
        new_start = x1;
    }
    segment = {new_start, new_end};
}

double Dichotomy::get_x1(double start, double end) {
    return (end + start - delta) / 2;
}

double Dichotomy::get_x2(double start, double end) {
    return (end + start + delta) / 2;
}
