#include "lab/parabola.h"

#include <fmt/core.h>

using namespace lab;

Segment Parabola::new_segment(Segment current_segment, func f) {
    double x1 = current_segment.start;
    double x3 = current_segment.end;
    double x2;
    do {
        x2 = ((double)rand()) / RAND_MAX * (x3 - x1) + x1;
    } while (f(x1) < f(x2) || f(x2) > f(x3));
    return Segment(x1, x3, {{x1, f(x1)}, {x2, f(x2)}, {x3, f(x3)}});
}

double Parabola::answer(Segment current_segment) {
    auto [x1, f1] = current_segment.points[0];
    auto [x2, f2] = current_segment.points[1];
    auto [x3, f3] = current_segment.points[2];
    return x2
           - 0.5
                 * ((x2 - x1) * (x2 - x1) * (f2 - f3)
                    - (x2 - x3) * (x2 - x3) * (f2 - f1))
                 / ((x2 - x1) * (f2 - f3) - (x2 - x3) * (f2 - f1));
}

Segment Parabola::step(Segment current_segment, func f) {
    auto [x1, f1] = current_segment.points[0];
    auto [x2, f2] = current_segment.points[1];
    auto [x3, f3] = current_segment.points[2];
    double ans = answer(current_segment);
    double f_ans = f(ans);
    if (ans < x2) {
        if (f_ans >= f2) {
            return Segment(ans, x3, {{ans, f_ans}, {x2, f2}, {x3, f3}});
        } else {
            return Segment(x1, x2, {{x1, f1}, {ans, f_ans}, {x2, f2}});
        }
    } else {
        if (f_ans <= f2) {
            return Segment(x2, x3, {{x2, f2}, {ans, f_ans}, {x3, f3}});
        } else {
            return Segment(x1, ans, {{x1, f1}, {x2, f2}, {ans, f_ans}});
        }
    }
}
