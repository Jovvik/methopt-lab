#pragma once

#include "lab/n_function.h"
#include "lab/vector.h"

namespace lab {

    class NOptimizer {
      public:
        Vector optimize(const NFunction& f, Vector starting_point,
                        double epsilon);
        std::vector<Vector>& get_points() const;

      protected:
        virtual bool is_done(const NFunction& f, double epsilon);
        virtual Vector step(const NFunction& f) = 0;

      private:
        std::vector<Vector> points;
    };

}  // namespace lab
