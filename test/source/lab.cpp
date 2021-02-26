#include <doctest/doctest.h>

#include <cmath>
#include <numbers>
#include <string>

#include "lab/dichotomy.h"
#include "lab/version.h"

TEST_CASE("Lab version") {
    static_assert(std::string_view(LAB_VERSION) == std::string_view("1.0"));
    CHECK(std::string(LAB_VERSION) == std::string("1.0"));
}

TEST_CASE("Dichotomy") {
    for (double epsilon = 1e-1; epsilon > 1e-10; epsilon /= 10) {
        for (double delta_multiplier = 2; delta_multiplier >= 0.1; delta_multiplier -= 0.1) {
            auto optimizer = lab::Dichotomy(epsilon * delta_multiplier);
            CHECK(abs(optimizer.optimize([](double x) { return x * x; }, epsilon, -1, 1) - 0)
                  <= epsilon);
            CHECK(abs(optimizer.optimize([](double x) { return sin(x); }, epsilon,
                                         std::numbers::pi / 2, 2 * std::numbers::pi)
                      - std::numbers::pi * 3 / 2)
                  <= epsilon);
        }
    }
}
