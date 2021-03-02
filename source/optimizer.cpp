#include "lab/optimizer.h"

#include <iostream>

using namespace lab;

double Optimizer::optimize(func f, const double epsilon, double start,
                           double end) {
    steps_count = 0;
    auto segment = new_segment(Segment(start, end), f);
    calculated_segments.push_back(segment);
    while (!is_done(segment, epsilon)) {
        segment = step(segment, f);
        segment.set_ans(answer(segment));
        calculated_segments.push_back(segment);
        steps_count++;
    }
    return answer(segment);
}

const std::vector<Segment>& Optimizer::get_segments() {
    return calculated_segments;
}

bool Optimizer::is_done(Segment segment, double epsilon) {
    return segment.get_end() <= 2 * epsilon + segment.get_start();
}
