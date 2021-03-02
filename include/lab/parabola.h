#pragma once

#include "lab/optimizer.h"

namespace lab {
    /**
     * Оптимизатор на основе метода парабол
     */
    class Parabola : public Optimizer {
      protected:
        Segment new_segment(Segment current_segment, func optimized_function);
        Segment step(Segment current_segment, func optimized_function);
        double answer(Segment current_segment);
    };
}  // namespace lab
