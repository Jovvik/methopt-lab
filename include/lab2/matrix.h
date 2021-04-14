#pragma once

#include <lab2/vector.h>

#include <optional>
#include <vector>

namespace lab2 {
    /**
     * Матрица
     */
    class Matrix {
      public:
        explicit Matrix(const std::vector<std::vector<double>>& data,
                        std::optional<double> max_eigenvalue = std::nullopt);

        [[nodiscard]] bool operator==(const Matrix& other) const;
        [[nodiscard]] Vector operator[](std::size_t idx) const;
        [[nodiscard]] std::size_t size() const;

        [[nodiscard]] Vector operator*(Vector other) const;

        const std::optional<double> max_eigenvalue;

      private:
        std::vector<Vector> data;

        void check_size() const;
    };

}  // namespace lab2
