#include <cassert>
#include <chrono>
#include <cxxopts.hpp>
#include <iostream>
#include <random>

#include "lab2/matrix.h"
#include "lab2/vector.h"

void generate(int n, int max_k) {
    assert(max_k >= 0);
    assert(n >= 10);
    assert(1000 >= n);

    std::default_random_engine rng(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());
    lab2::Matrix A(n, [&rng](std::size_t, std::size_t) {
        return -std::discrete_distribution<int>({40, 15, 15, 15, 15})(rng);
    });
    lab2::Vector x(n, [](std::size_t i) {
        return i;
    });

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            std::cout << A[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) {
    cxxopts::Options options(
        "Генератор",
        "Генератор матриц для третьей лабораторной методов оптимизации");
    // clang-format off
    options.add_options()
        ("n,dimensions", "Размерность матрицы", cxxopts::value<int>()->default_value("10"))
        ("k,maxk", "Максимальное значение k", cxxopts::value<int>()->default_value("10"))
        ("h,help", "Вывести помощь");
    // clang-format on

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    generate(result["n"].as<int>(), result["k"].as<int>());
}
