#pragma once

#include <memory>

#include "lab1/optimizer.h"
#include "lab2/n_optimizer.h"

namespace lab2 {

    class FastestDescent : public NOptimizer {
        using Gen = std::function<std::unique_ptr<lab1::Optimizer>(
            const std::function<double(double)>&, double, double, double)>;

      public:
        FastestDescent(Gen generator);

        Vector iteration(NFunction& f, double epsilon) override;

      private:
        Gen generator;
    };

}  // namespace lab2
