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
        Matrix operator*(double value) ;
        Matrix operator/(double value) ;
        Matrix operator+(Matrix other) ;
        Matrix operator-(Matrix other) ;

        bool operator==(const Matrix& other) const;

        const std::optional<double> max_eigenvalue;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

        static Matrix I(size_t size);

        static Matrix vector_mul(const Vector& first, const Vector& second);

        ~Matrix() override = default;

      private:
        std::vector<Vector> data;

        void check_size() const;
    };

}  // namespace lab2
