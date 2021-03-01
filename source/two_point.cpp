#include "lab/two_point.h"

#include "lab/segment.h"

using namespace lab;

bool TwoPoint::is_done(Segment current_segment, double epsilon) {
    return current_segment.end <= 2 * epsilon + current_segment.start;
}

double TwoPoint::answer(Segment current_segment) {
    return (current_segment.end + current_segment.start) / 2;
}

Segment TwoPoint::new_segment(Segment current_segment,
                              func optimized_function) {
    double start = current_segment.start;
    double end = current_segment.end;
    double x1 = get_x1(start, end);
    double x2 = get_x2(start, end);
    return Segment(
        start, end,
        {{x1, optimized_function(x1)}, {x2, optimized_function(x2)}});
}
