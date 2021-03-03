#include "lab/optimizer.h"

#include <iostream>

using namespace lab;

Optimizer::Optimizer(const func& f, const double epsilon, double start,
                     double end)
    : f(f), segment(start, end), epsilon(epsilon), steps_count(0) {}

double Optimizer::optimize() {
    calculated_segments.push_back(segment);
    while (!is_done()) {
        step();
        segment.set_ans(answer());
        calculated_segments.push_back(segment);
        steps_count++;
    }
    return answer();
}

const std::vector<Segment>& Optimizer::get_segments() {
    return calculated_segments;
}

bool Optimizer::is_done() {
    return segment.get_end() <= 2 * epsilon + segment.get_start();
}
