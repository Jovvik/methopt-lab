#include <doctest/doctest.h>

#include <string>

#include "lab/version.h"

TEST_CASE("Lab version") {
    static_assert(std::string_view(LAB_VERSION) == std::string_view("1.0"));
    CHECK(std::string(LAB_VERSION) == std::string("1.0"));
}
