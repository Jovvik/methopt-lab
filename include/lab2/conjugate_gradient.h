#include "lab2/n_optimizer.h"

namespace lab2 {
    class ConjugateGradient : public NOptimizer {
      public:
        Vector iteration(NFunction &f, double epsilon) override;

      private:
        Vector p      = Vector({1, 1});
        Vector f_grad = p;
    };
}  // namespace lab2
