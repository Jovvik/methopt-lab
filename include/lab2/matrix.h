#pragma once

#include <lab2/vector.h>

#include <vector>

namespace lab2 {

    class Matrix {
      private:
        std::vector<Vector> data;

        void check_size() const;

      public:
        Matrix(const std::vector<std::vector<double>>& data);
        Matrix(std::vector<std::vector<double>>&& data);

        bool operator==(Matrix other) const;
        Vector operator[](std::size_t idx) const;
        std::size_t size() const;

        Vector operator*(Vector other) const;
    };

}  // namespace lab2
