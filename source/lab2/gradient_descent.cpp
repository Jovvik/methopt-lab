#include "lab2/n_optimizer.h"

using namespace lab2;

class GradientDescent : NOptimizer {
    Vector iteration(NFunction &f) override {
        Vector x = points_last(), y = x - f.grad(x) * a;
        while (f(y) >= f(x)) {
            a /= 2;
            x = points_last();
            y = x - f.grad(x) * a;
        }
        return y;
    }

  public:
    explicit GradientDescent(double step) { a = step; }

  private:
    Vector points_last() { return get_points().back(); }
    double a;
};