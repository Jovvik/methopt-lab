#pragma once

#include "lab2/n_function.h"
#include "lab2/vector.h"

namespace lab2 {

    class NOptimizer {
      public:
        Vector optimize(NFunction& f, Vector starting_point, double epsilon);
        std::vector<Vector>& get_points() const;

      protected:
        bool is_done(NFunction& f, double epsilon) const;
        virtual Vector step(const NFunction& f) const = 0;

      private:
        std::vector<Vector> points;
    };

}  // namespace lab2
