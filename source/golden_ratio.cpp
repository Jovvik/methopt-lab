#include "lab/golden_ratio.h"

#include <cmath>

#include "lab/segment.h"

using namespace lab;

Segment GoldenRatio::step(Segment segment, func f) {
    auto [x1, f_x1] = segment.get_points()[0];
    auto [x2, f_x2] = segment.get_points()[1];
    double start = segment.get_start();
    double end = segment.get_end();
    if (f_x1 <= f_x2) {
        double new_x1 = get_x1(start, x2);
        return Segment(start, x2, {{new_x1, f(new_x1)}, {x1, f_x1}});
    } else {
        double new_x2 = get_x2(x1, end);
        return Segment(x1, end, {{x2, f_x2}, {new_x2, f(new_x2)}});
    }
}

double GoldenRatio::get_x1(double start, double end) {
    return start + (1 - TAU) * (end - start);
}

double GoldenRatio::get_x2(double start, double end) {
    return start + TAU * (end - start);
}
