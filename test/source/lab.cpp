#include <doctest/doctest.h>
#include <fmt/core.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#define PI 3.141592653589793238462643383279502884197169399375105820974944

#include "lab/dichotomy.h"
#include "lab/version.h"

TEST_CASE("Lab version") {
    static_assert(std::string_view(LAB_VERSION) == std::string_view("1.0"));
    CHECK(std::string(LAB_VERSION) == std::string("1.0"));
}

TEST_CASE("Dichotomy") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        for (double delta_multiplier = 1.5; delta_multiplier >= 0.1; delta_multiplier -= 0.1) {
            auto optimizer = lab::Dichotomy(epsilon * delta_multiplier);
            CHECK(std::abs(optimizer.optimize([](double x) { return x * x; }, epsilon, -1, 1) - 0)
                  <= epsilon);
            CHECK(std::abs(
                      optimizer.optimize([](double x) { return sin(x); }, epsilon, PI / 2, 2 * PI)
                      - PI * 3 / 2)
                  <= epsilon);
            CHECK(std::abs(optimizer.optimize([](double x) { return x * x + exp(-0.35 * x); },
                                              epsilon, -2, 3)
                           - 0.165170191649)
                  <= epsilon);
        }
    }
}
