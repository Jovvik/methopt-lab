#include "lab2/n_optimizer.h"

using namespace lab2;

Vector NOptimizer::optimize(NFunction& f, const Vector& starting_point,
                            double epsilon) {
    points.clear();
    points.push_back(starting_point);
    while (!is_done(f, epsilon)) {
        points.push_back(iteration(f));
    }
    return points.back();
}

bool NOptimizer::is_done(NFunction& f, double epsilon) const {
    return f.grad(points.back()).norm() <= epsilon;
}

const std::vector<Vector>& NOptimizer::get_points() const { return points; }
