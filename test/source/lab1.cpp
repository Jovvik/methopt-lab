#include <doctest/doctest.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#define PI 3.141592653589793238462643383279502884197169399375105820974944

#include "lab/version.h"
#include "lab1/brent.h"
#include "lab1/dichotomy.h"
#include "lab1/fibonacci.h"
#include "lab1/golden_ratio.h"
#include "lab1/parabola.h"

using namespace lab1;

TEST_CASE("Lab version") {
    static_assert(std::string_view(LAB_VERSION) == std::string_view("1.0"));
    CHECK(std::string(LAB_VERSION) == std::string("1.0"));
}

auto f = [](double x) {
    return x * x + exp(-0.35 * x);
};

TEST_CASE("Segment") {
    auto optimizer = Dichotomy(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segments = optimizer.get_segments();
    CHECK(segments.size() > 0);
    CHECK(segments[0].get_start() == -2);
    CHECK(segments[0].get_end() == 3);
    CHECK(segments[0].get_mid() == std::nullopt);
    segments[0].set_ans(42);
    CHECK(*segments[0].get_ans() == 42);
}

TEST_CASE("Dichotomy ratio f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        Dichotomy optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Golden ratio f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        GoldenRatio optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Fibonacci f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        Fibonacci optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Parabola f") {
    for (double epsilon = 1e-1; epsilon > 1e-6; epsilon /= 10) {
        Parabola optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Brent f") {
    for (double epsilon = 1e-1; epsilon > 1e-8; epsilon /= 10) {
        Brent optimizer(f, epsilon, -2, 3);
        CHECK(std::abs(optimizer.optimize() - 0.165170191649) < epsilon);
    }
}

TEST_CASE("Dichotomy logging") {
    auto optimizer = Dichotomy(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segms = optimizer.get_segments();
    CHECK(segms.size() != 0);
    CHECK(segms[0].saved_points.count("x1") != 0);
    CHECK(segms[0].saved_points.count("x2") != 0);
}

TEST_CASE("Golden ratio logging") {
    auto optimizer = GoldenRatio(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segms = optimizer.get_segments();
    CHECK(segms.size() != 0);
    CHECK(segms[0].saved_points.count("x1") != 0);
    CHECK(segms[0].saved_points.count("x2") != 0);
}

TEST_CASE("Fibonacci logging") {
    auto optimizer = Fibonacci(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segms = optimizer.get_segments();
    CHECK(segms.size() != 0);
    CHECK(segms[0].saved_points.count("x1") != 0);
    CHECK(segms[0].saved_points.count("x2") != 0);
}

TEST_CASE("Parabola logging") {
    auto optimizer = Parabola(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segms = optimizer.get_segments();
    CHECK(segms.size() != 0);
    CHECK(segms[0].saved_points.count("x1") != 0);
    CHECK(segms[0].saved_points.count("x2") != 0);
    CHECK(segms[0].saved_points.count("x3") != 0);
}

TEST_CASE("Brent logging") {
    auto optimizer = Brent(f, 1e-4, -2, 3);
    optimizer.optimize();
    auto segms = optimizer.get_segments();
    CHECK(segms.size() != 0);
    CHECK(segms[0].saved_points.count("u") != 0);
    CHECK(segms[0].saved_points.count("w") != 0);
    CHECK(segms[0].saved_points.count("v") != 0);
    CHECK(segms[0].saved_points.count("x") != 0);
}