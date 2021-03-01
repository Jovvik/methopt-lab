#include "lab/dichotomy.h"

#include "lab/segment.h"

using namespace lab;

Dichotomy::Dichotomy(double delta_) : delta(delta_) {}

bool Dichotomy::is_done(Segment current_segment, double epsilon) {
    return current_segment.end <= 2 * epsilon + current_segment.start;
}

Segment Dichotomy::step(Segment current_segment, func optimized_function) {
    auto [x1, f_x1] = current_segment.points[0];
    auto [x2, f_x2] = current_segment.points[1];
    double new_start = current_segment.start;
    double new_end = current_segment.end;
    if (f_x1 <= f_x2) {
        new_end = x2;
    } else {
        new_start = x1;
    }
    return new_segment(Segment(new_start, new_end), optimized_function);
}

double Dichotomy::answer(Segment current_segment) {
    return (current_segment.end + current_segment.start) / 2;
}

Segment Dichotomy::new_segment(Segment current_segment,
                               func optimized_function) {
    double start = current_segment.start;
    double end = current_segment.end;
    double x1 = get_x1(start, end);
    double x2 = get_x2(start, end);
    return Segment(
        start, end,
        {{x1, optimized_function(x1)}, {x2, optimized_function(x2)}});
}

double Dichotomy::get_x1(double start, double end) {
    return (end + start - delta) / 2;
}

double Dichotomy::get_x2(double start, double end) {
    return (end + start + delta) / 2;
}
