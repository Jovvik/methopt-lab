#pragma once

#include <vector>

namespace lab {

    class Vector {
      private:
        const std::vector<double> data;

      public:
        Vector(const std::vector<double>& data);
        Vector(std::vector<double>&& data);

        double operator[](std::size_t idx) const;
        std::size_t size() const;

        Vector operator+(Vector other) const;
        double operator*(Vector other) const;
        Vector operator*(double val) const;
    };

}  // namespace lab
