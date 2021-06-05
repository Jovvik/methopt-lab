#pragma once

#include <functional>
#include <istream>
#include <ostream>
#include <vector>

namespace lab2 {
    /**
     * Вектор
     */
    class Vector {
      private:
        std::vector<double> data;

      public:
        Vector(const std::vector<double>& data);
        Vector(std::istream& is);
        Vector(std::size_t size,
               const std::function<double(std::size_t)>& generator);

        double operator[](std::size_t idx) const;
        [[nodiscard]] std::size_t size() const;
        [[nodiscard]] double norm() const;

        Vector operator+(Vector other) const;
        Vector operator-(Vector other) const;
        double operator*(const Vector& other) const;
        Vector operator*(double val) const;
        bool operator==(const Vector& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    };

}  // namespace lab2
