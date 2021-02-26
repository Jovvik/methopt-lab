#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <vector>

#include "lab/segment.h"

namespace lab {

    using func = const std::function<double(double)>&;

    class Optimizer {
      public:
        double optimize(const std::function<double(double)>& optimized_function, double epsilon,
                        double start, double end);
        const std::vector<Segment>& get_segments();

      protected:
        virtual bool is_done(Segment current_segment, double epsilon) = 0;
        virtual Segment step(Segment current_segment, func optimized_function) = 0;
        virtual double answer(Segment current_segment) = 0;
        virtual Segment new_segment(Segment current_segment, func optimized_function) = 0;

      private:
        std::vector<Segment> calculated_segments;
    };

}  // namespace lab
