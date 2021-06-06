#include "lab2/n_optimizer.h"

namespace lab4 {
    class OneDSearchNewton : public lab2::NOptimizer {
      public:
        OneDSearchNewton();

        lab2::Vector iteration(lab2::NFunction& f, double epsilon) override;
        bool is_done(lab2::NFunction& f, double epsilon) const override;

      private:
        const double EPS = 1e-7;
        const int START = -100, END = 100;
        lab2::Vector p;
    };
}  // namespace lab4
