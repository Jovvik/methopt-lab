#include "lab/optimizer.h"

#include <iostream>

using namespace lab;

double Optimizer::optimize(
    const std::function<double(double)>& optimized_function,
    const double epsilon, double start, double end) {
    Segment current_segment
        = new_segment(Segment(start, end), optimized_function);
    calculated_segments.push_back(current_segment);
    while (!is_done(current_segment, epsilon)) {
        current_segment = step(current_segment, optimized_function);
        calculated_segments.push_back(current_segment);
    }
    return answer(current_segment);
}

const std::vector<Segment>& Optimizer::get_segments() {
    return calculated_segments;
}
