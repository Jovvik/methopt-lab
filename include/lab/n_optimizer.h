#pragma once

#include "lab/n_function.h"
#include "lab/vector.h"

namespace lab {

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

}  // namespace lab
