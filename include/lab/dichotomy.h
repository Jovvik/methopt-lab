#include "lab/optimizer.h"

namespace lab {
    class Dichotomy : Optimizer {
      public:
        explicit Dichotomy(double delta);
        bool is_done(Segment current_segment, double epsilon);
        Segment step(Segment current_segment, func optimized_function);
        double answer(Segment current_segment);
        Segment initial_step(double start, double end, func optimized_function);

      private:
        double get_x1(double start, double end);
        double get_x2(double start, double end);

        double delta;
    };

}  // namespace lab