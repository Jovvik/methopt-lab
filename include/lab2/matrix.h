#pragma once

#include <lab2/vector.h>

#include <vector>

namespace lab2 {

    class Matrix {
      private:
        std::vector<Vector> data;

        void check_size() const;

      public:
        explicit Matrix(const std::vector<std::vector<double>>& data);
        explicit Matrix(std::vector<std::vector<double>>&& data);

        [[nodiscard]] bool operator==(const Matrix& other) const;
        [[nodiscard]] Vector operator[](std::size_t idx) const;
        [[nodiscard]] std::size_t size() const;

        [[nodiscard]] Vector operator*(Vector other) const;
    };

}  // namespace lab2
