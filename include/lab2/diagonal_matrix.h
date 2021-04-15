#pragma once

#include "lab2/abstract_matrix.h"

namespace lab2 {

    class DiagonalMatrix : public AbstractMatrix {
      public:
        explicit DiagonalMatrix(const std::vector<double>& diagonal,
                                std::optional<double> max_eigenvalue
                                = std::nullopt);

        [[nodiscard]] Vector operator[](std::size_t idx) const override;
        [[nodiscard]] std::size_t size() const override;

        [[nodiscard]] Vector operator*(Vector other) const override;

        ~DiagonalMatrix() override = default;

      private:
        const std::vector<double> diagonal;
    };

}  // namespace lab2
