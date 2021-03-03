#include <doctest/doctest.h>
#include <fmt/core.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#define PI 3.141592653589793238462643383279502884197169399375105820974944

#include "lab/dichotomy.h"
#include "lab/fibonacci.h"
#include "lab/golden_ratio.h"
#include "lab/parabola.h"
#include "lab/version.h"

TEST_CASE("Lab version") {
    static_assert(std::string_view(LAB_VERSION) == std::string_view("1.0"));
    CHECK(std::string(LAB_VERSION) == std::string("1.0"));
}

auto square = [](double x) { return x * x; };
auto my_sin = [](double x) { return sin(x); };
auto f = [](double x) { return x * x + exp(-0.35 * x); };

TEST_CASE("Segment") {
    auto optimizer = lab::Dichotomy(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segments = optimizer.get_segments();
    CHECK(segments.size() > 0);
    CHECK(segments[0].get_start() == -2);
    CHECK(segments[0].get_end() == 3);
    CHECK(segments[0].get_ans() == std::nullopt);
    CHECK(segments[0].get_mid() == std::nullopt);
    segments[0].set_ans(42);
    CHECK(*segments[0].get_ans() == 42);
}

TEST_CASE("Dichotomy square") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Dichotomy optimizer(square, epsilon, -1, 1);
        CHECK(std::abs(optimizer.optimize()) < epsilon);
    }
}
TEST_CASE("Dichotomy sin") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Dichotomy optimizer(my_sin, epsilon, PI / 2, 2 * PI);
        CHECK(std::abs(optimizer.optimize() - PI * 3 / 2) < epsilon);
    }
}

TEST_CASE("Golden ratio f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Dichotomy optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Golden ratio square") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::GoldenRatio optimizer(square, epsilon, -1, 1);
        CHECK(std::abs(optimizer.optimize()) < epsilon);
    }
}
TEST_CASE("Golden ratio sin") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::GoldenRatio optimizer(my_sin, epsilon, PI / 2, 2 * PI);
        CHECK(std::abs(optimizer.optimize() - PI * 3 / 2) < epsilon);
    }
}

TEST_CASE("Golden ratio f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::GoldenRatio optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Fibonacci square") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Fibonacci optimizer(square, epsilon, -1, 1);
        CHECK(std::abs(optimizer.optimize()) < epsilon);
    }
}
TEST_CASE("Fibonacci sin") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Fibonacci optimizer(my_sin, epsilon, PI / 2, 2 * PI);
        CHECK(std::abs(optimizer.optimize() - PI * 3 / 2) < epsilon);
    }
}

TEST_CASE("Fibonacci f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Fibonacci optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Parabola f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        lab::Parabola optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}
