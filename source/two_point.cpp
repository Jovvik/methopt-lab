#include "lab/two_point.h"

#include "lab/segment.h"

using namespace lab;

double TwoPoint::answer() {
    return (segment.get_end() + segment.get_start()) / 2;
}

void TwoPoint::calc_points() {
    double start = segment.get_start();
    double end = segment.get_end();
    x1 = get_x1(start, end);
    fx1 = f(x1);
    x2 = get_x2(start, end);
    fx2 = f(x2);
}
