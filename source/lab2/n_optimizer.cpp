#include "lab2/n_optimizer.h"

#include <lab2/quadratic_function.h>

using namespace lab2;

Vector NOptimizer::optimize(NFunction& f, const Vector& starting_point,
                            double epsilon) {
    iteration_count = 0;
    points.clear();
    points.push_back(starting_point);
    while (!is_done(f, epsilon) && iteration_count <= 100) {
        points.push_back(iteration(f, epsilon));
        iteration_count++;
    }
    return points.back();
}

bool NOptimizer::is_done(NFunction& f, double epsilon) const {
    return f.grad(points.back()).norm() <= epsilon;
}

const std::vector<Vector>& NOptimizer::get_points() const { return points; }
