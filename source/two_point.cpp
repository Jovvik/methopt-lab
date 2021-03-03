#include "lab/two_point.h"

#include "lab/segment.h"

using namespace lab;

void TwoPoint::calc_points() {
    double start = segment.get_start();
    double end = segment.get_end();
    x1 = get_x1(start, end);
    fx1 = f(x1);
    x2 = get_x2(start, end);
    fx2 = f(x2);
    segment.saved_points["x1"] = {x1, fx1};
    segment.saved_points["x2"] = {x2, fx2};
    save_segment();
}
