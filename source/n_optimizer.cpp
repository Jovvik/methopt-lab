#include "lab/n_optimizer.h"

using namespace lab;

Vector NOptimizer::optimize(const NFunction& f, Vector starting_point,
                            double epsilon) {
    points.clear();
    points.push_back(starting_point);
    while (!is_done(f, epsilon)) {
        points.push_back(step(f));
    }
    return points.back();
}