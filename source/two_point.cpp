#include "lab/two_point.h"

#include "lab/segment.h"

using namespace lab;

double TwoPoint::answer(Segment segment) {
    return (segment.get_end() + segment.get_start()) / 2;
}

Segment TwoPoint::new_segment(Segment segment, func f) {
    double start = segment.get_start();
    double end = segment.get_end();
    double x1 = get_x1(start, end);
    double x2 = get_x2(start, end);
    return Segment(start, end, {{x1, f(x1)}, {x2, f(x2)}});
}
