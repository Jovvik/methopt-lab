#pragma once

#include <optional>
#include <vector>

#include "lab2/vector.h"

namespace lab2 {
    /**
     * Абстрактный класс матрицы
     */
    class AbstractMatrix {
      public:
        [[nodiscard]] virtual Vector operator[](std::size_t idx) const = 0;
        [[nodiscard]] virtual ::size_t size() const                    = 0;

        // TODO: ref
        [[nodiscard]] virtual Vector operator*(Vector other) const = 0;

        [[nodiscard]] double max_eigenvalue() const;

        virtual ~AbstractMatrix() = default;
        bool has_max_eigenvalue;

      protected:
        explicit AbstractMatrix(std::optional<double> max_eigenvalue);

      private:
        double max_eigenvalue_;
    };

}  // namespace lab2
