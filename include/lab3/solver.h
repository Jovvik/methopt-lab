#pragma once

#include <lab2/matrix.h>
#include <lab2/vector.h>

namespace lab3 {
    class Solver {
      public:
        static lab2::Vector solve(const lab2::Matrix& A, const lab2::Vector& b);
    };
}