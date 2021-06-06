#include "lab4/powell.h"

#include "iostream"
#include "lab1/brent.h"
#include "lab3/solver.h"

using namespace lab4;

Powell::Powell()
    : w(lab2::Vector({1})),
      p(lab2::Vector({1})),
      delta_x(lab2::Vector({1})),
      G(lab2::Matrix({{1}}, std::nullopt)) {}

lab2::Vector Powell::iteration(lab2::NFunction &f, double) {
    const lab2::Vector x_k_1 = get_points().back(), grad = f.grad(x_k_1),
                       anti_grad = grad * (-1);
    if (iteration_count == 0) {
        w                = anti_grad;
        p                = w;
        const auto alpha = lab1::Brent(
                               [&f, x = x_k_1, p_ = p](double a) {
                                   return f(x + p_ * a);
                               },
                               ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
                               .optimize();
        delta_x = p * alpha;
        G       = lab2::Matrix::I(x_k_1.size());
        return x_k_1 + delta_x;
    }
    const auto w_k = anti_grad, delta_w_k = w_k - w, v_k = G * delta_w_k,
               delta_x_wave_k = delta_x + G * delta_w_k;
    G                       = G
        - lab2::Matrix::vector_mul(delta_x_wave_k, delta_x_wave_k)
              / (delta_w_k * delta_x_wave_k);
    p                = G * w_k;
    const auto alpha = lab1::Brent(
                           [&f, x = x_k_1, p_ = p](double a) {
                               return f(x + p_ * a);
                           },
                           ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
                           .optimize();
    delta_x = p * alpha;
    return x_k_1 + delta_x;
}

bool Powell::is_done(lab2::NFunction &, double epsilon) const {
    return delta_x.norm() < epsilon;
}