#include <doctest/doctest.h>
#include <lab/lab.h>
#include <lab/version.h>

#include <string>

TEST_CASE("Lab") {
    using namespace lab;

    Lab lab("Tests");

    CHECK(lab.greet(LanguageCode::EN) == "Hello, Tests!");
    CHECK(lab.greet(LanguageCode::DE) == "Hallo Tests!");
    CHECK(lab.greet(LanguageCode::ES) == "¡Hola Tests!");
    CHECK(lab.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Lab version") {
    static_assert(std::string_view(LAB_VERSION) == std::string_view("1.0"));
    CHECK(std::string(LAB_VERSION) == std::string("1.0"));
}
