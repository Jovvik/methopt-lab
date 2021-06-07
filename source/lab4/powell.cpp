#include "lab4/powell.h"

#include "iostream"
#include "lab1/brent.h"
#include "lab3/solver.h"

using namespace lab4;

Powell::Powell()
    : s(lab2::Vector({1})),
      d(lab2::Vector({1})),
      G(lab2::Matrix({{1}}, std::nullopt)) {}

lab2::Vector Powell::iteration(lab2::NFunction &f, double) {
    lab2::Vector x_k_1 = get_points().back(), g_x = f.grad(x_k_1);
    if (iteration_count == 0) {
        G = lab2::Matrix::I(x_k_1.size());
        d = g_x * (-1);
        return x_k_1;
    }
    const auto r = lab1::Brent(
                       [&f, x = x_k_1, d_ = d](double a) {
                           return f(x + d_ * a);
                       },
                       ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
                       .optimize();
    s      = d * r;
    auto x = x_k_1 + s, g_y = g_x;
    g_x    = f.grad(x);
    auto p = g_x - g_y, v = G * p;
    G = G + lab2::Matrix::vector_mul(s, s) / (s * p)
        - lab2::Matrix::vector_mul(v, v) / (v * p);
    d                 = (G * g_x) * (-1);
    auto delta_x_wave = s + G * p;
    G                 = G
        - lab2::Matrix::vector_mul(delta_x_wave, delta_x_wave)
              / (p * delta_x_wave);
    return x;
}

bool Powell::is_done(lab2::NFunction &, double epsilon) const {
    return s.norm() < epsilon;
}