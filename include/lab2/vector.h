#pragma once

#include <functional>
#include <vector>

namespace lab2 {

    class Vector {
      private:
        std::vector<double> data;

      public:
        explicit Vector(const std::vector<double>& data);
        Vector(std::size_t size,
               const std::function<double(std::size_t)>& generator);
        explicit Vector(std::vector<double>&& data);

        double operator[](std::size_t idx) const;
        [[nodiscard]] std::size_t size() const;
        [[nodiscard]] double norm() const;

        Vector operator+(Vector other) const;
        double operator*(const Vector& other) const;
        Vector operator*(double val) const;
        bool operator==(const Vector& other) const;
    };

}  // namespace lab2
