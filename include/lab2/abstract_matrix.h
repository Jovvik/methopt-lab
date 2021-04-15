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

        const std::optional<double> max_eigenvalue;

        virtual ~AbstractMatrix() = default;

      protected:
        explicit AbstractMatrix(std::optional<double> max_eigenvalue);
    };

}  // namespace lab2
