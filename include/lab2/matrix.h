#pragma once

#include <optional>
#include <vector>

#include "lab2/abstract_matrix.h"
#include "lab2/vector.h"

namespace lab2 {
    /**
     * Произвольная матрица
     */
    class Matrix : public AbstractMatrix {
      public:
        explicit Matrix(const std::vector<std::vector<double>>& data,
                        std::optional<double> max_eigenvalue = std::nullopt);

        [[nodiscard]] Vector operator[](std::size_t idx) const override;
        [[nodiscard]] std::size_t size() const override;

        [[nodiscard]] Vector operator*(Vector other) const override;

        const std::optional<double> max_eigenvalue;

        ~Matrix() override = default;

      private:
        std::vector<Vector> data;

        void check_size() const;
    };

}  // namespace lab2
