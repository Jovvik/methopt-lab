#include "lab/golden_ratio.h"

#include <cmath>

#include "lab/segment.h"

using namespace lab;

Segment GoldenRatio::step(Segment current_segment, func optimized_function) {
    auto [x1, f_x1] = current_segment.points[0];
    auto [x2, f_x2] = current_segment.points[1];
    double start = current_segment.start;
    double end = current_segment.end;
    if (f_x1 <= f_x2) {
        double new_x1 = get_x1(start, x2);
        return Segment(start, x2,
                       {{new_x1, optimized_function(new_x1)}, {x1, f_x1}});
    } else {
        double new_x2 = get_x2(x1, end);
        return Segment(x1, end,
                       {{x2, f_x2}, {new_x2, optimized_function(new_x2)}});
    }
}

double GoldenRatio::get_x1(double start, double end) {
    return start + (1 - TAU) * (end - start);
}

double GoldenRatio::get_x2(double start, double end) {
    return start + TAU * (end - start);
}
