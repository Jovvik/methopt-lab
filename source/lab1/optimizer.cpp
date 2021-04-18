#include "lab1/optimizer.h"

#include <iostream>

using namespace lab1;

Optimizer::Optimizer(const func& f, const double epsilon, double start,
                     double end)
    : f(f), segment(start, end), epsilon(epsilon), steps_count(0) {}

double Optimizer::optimize() {
    while (!is_done() && steps_count <= 1000) {
        step();
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

double Optimizer::answer() {
    return (segment.get_end() + segment.get_start()) / 2;
}

void Optimizer::save_segment() {
    segment.set_ans(answer());
    calculated_segments.push_back(segment);
}
