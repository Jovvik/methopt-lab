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
        Optimizer();
        virtual ~Optimizer();
        double optimize(const std::function<double(double)>& optimized_function, double epsilon,
                        double start, double end);
        const std::vector<Segment>& get_segments();

      protected:
        virtual bool is_done(Segment current_segment, double epsilon);
        virtual Segment step(Segment current_segment, func optimized_function);
        virtual double answer(Segment current_segment);
        virtual Segment initial_step(double start, double end, func optimized_function);

      private:
        std::vector<Segment> calculated_segments;
    };

}  // namespace lab
