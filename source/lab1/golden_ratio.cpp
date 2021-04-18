#include "lab1/golden_ratio.h"

#include <cmath>

#include "lab1/segment.h"

using namespace lab1;

GoldenRatio::GoldenRatio(const func& optimized_function, double epsilon,
                         double start, double end)
    : TwoPoint(optimized_function, epsilon, start, end) {
    calc_points();
}

void GoldenRatio::step() {
    double start = segment.get_start();
    double end = segment.get_end();
    segment.saved_points["x1"] = {x1, fx1};
    segment.saved_points["x2"] = {x2, fx2};
    save_segment();
    if (fx1 <= fx2) {
        segment = {start, x2};
        double new_x1 = get_x1(start, x2);
        x2 = x1;
        fx2 = fx1;
        x1 = new_x1;
        fx1 = f(x1);
    } else {
        segment = {x1, end};
        double new_x2 = get_x2(x1, end);
        x1 = x2;
        fx1 = fx2;
        x2 = new_x2;
        fx2 = f(x2);
    }
}

double GoldenRatio::get_x1(double start, double end) {
    return start + (1 - TAU) * (end - start);
}

double GoldenRatio::get_x2(double start, double end) {
    return start + TAU * (end - start);
}
