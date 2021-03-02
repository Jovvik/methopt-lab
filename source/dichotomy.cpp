#include "lab/dichotomy.h"

#include "lab/segment.h"

using namespace lab;

Dichotomy::Dichotomy(double delta_) : delta(delta_) {}

Segment Dichotomy::step(Segment segment, func optimized_function) {
    auto [x1, f_x1] = segment.get_points()[0];
    auto [x2, f_x2] = segment.get_points()[1];
    double new_start = segment.get_start();
    double new_end = segment.get_end();
    if (f_x1 <= f_x2) {
        new_end = x2;
    } else {
        new_start = x1;
    }
    return new_segment(Segment(new_start, new_end), optimized_function);
}

double Dichotomy::get_x1(double start, double end) {
    return (end + start - delta) / 2;
}

double Dichotomy::get_x2(double start, double end) {
    return (end + start + delta) / 2;
}
