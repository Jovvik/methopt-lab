#pragma once

#include <lab/vector.h>

#include <vector>

namespace lab {

    class Matrix {
      private:
        std::vector<Vector> data;

      public:
        Matrix(const std::vector<std::vector<double>>& data);
        Matrix(std::vector<std::vector<double>>&& data);

        Vector operator[](std::size_t idx) const;
        std::size_t size() const;

        Vector operator*(Vector other) const;
    };

}  // namespace lab
