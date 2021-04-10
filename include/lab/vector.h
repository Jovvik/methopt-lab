#pragma once

#include <functional>
#include <vector>

namespace lab {

    class Vector {
      private:
        std::vector<double> data;

      public:
        Vector(const std::vector<double>& data);
        Vector(std::size_t size, std::function<double(std::size_t)> generator);
        Vector(std::vector<double>&& data);

        double operator[](std::size_t idx) const;
        std::size_t size() const;

        Vector operator+(Vector other) const;
        double operator*(Vector other) const;
        Vector operator*(double val) const;
        bool operator==(Vector other) const;
    };

}  // namespace lab
