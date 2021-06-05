#pragma once

#include <optional>
#include <ostream>
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
        explicit Matrix(std::size_t size,
                        const std::function<double(std::size_t, std::size_t)>& generator);

        [[nodiscard]] Vector operator[](std::size_t idx) const override;
        [[nodiscard]] std::size_t size() const override;

        [[nodiscard]] Vector operator*(Vector other) const override;

        bool operator==(const Matrix& other) const;

        const std::optional<double> max_eigenvalue;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

        ~Matrix() override = default;

      private:
        std::vector<Vector> data;

        void check_size() const;
    };

}  // namespace lab2
