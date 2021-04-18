#include "lab1/parabola.h"

#include <fmt/core.h>

using namespace lab1;

Parabola::Parabola(const func& optimized_function, double epsilon, double start,
                   double end)
    : Optimizer(optimized_function, epsilon, start, end) {
    f_start = f(start);
    f_end = f(end);
    double mid;
    do {
        mid = ((double)rand()) / RAND_MAX * (end - start) + start;
        f_mid = f(mid);
    } while (f_start < f_mid || f_mid > f_end);
    segment.set_mid(mid);
}

double Parabola::answer() {
    double start = segment.get_start();
    double mid = *segment.get_mid();
    double end = segment.get_end();
    return mid
           - 0.5
                 * ((mid - start) * (mid - start) * (f_mid - f_end)
                    - (mid - end) * (mid - end) * (f_mid - f_start))
                 / ((mid - start) * (f_mid - f_end)
                    - (mid - end) * (f_mid - f_start));
}

void Parabola::step() {
    double ans = answer();
    double f_ans = f(ans);
    double start = segment.get_start();
    double mid = *segment.get_mid();
    double end = segment.get_end();

    segment.saved_points["x1"] = {start, f_start};
    segment.saved_points["x2"] = {mid, f_mid};
    segment.saved_points["x3"] = {end, f_end};
    save_segment();

    if (ans < mid) {
        if (f_ans >= f_mid) {
            segment = {ans, mid, end};
            f_start = f_ans;
        } else {
            segment = {start, ans, mid};
            f_end = f_mid;
            f_mid = f_ans;
        }
    } else {
        if (f_ans <= f_mid) {
            segment = {mid, ans, end};
            f_start = f_mid;
            f_mid = f_ans;
        } else {
            segment = {start, mid, ans};
            f_end = f_ans;
        }
    }
}
