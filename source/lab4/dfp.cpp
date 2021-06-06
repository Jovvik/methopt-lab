#include "lab4/dfp.h"

#include "iostream"
#include "lab1/brent.h"
#include "lab3/solver.h"

using namespace lab4;

DFP::DFP()
    : w(lab2::Vector({1})), p(lab2::Vector({1})), delta_x(lab2::Vector({1})) {}

lab2::Vector DFP::iteration(lab2::NFunction &f, double) {
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
        delta_x        = p * alpha;
        lab2::Matrix I = lab2::Matrix::I(x_k_1.size());
        G              = std::make_unique<lab2::Matrix>(I);
        return x_k_1 + delta_x;
    }
    std::cout << *G;
    auto w_k = anti_grad, delta_w_k = w_k - w;
    //    lab2::Matrix G_k
    //        = (*G)
    //          - lab2::Matrix::vector_mul(delta_x, delta_x) / (delta_w_k *
    //          delta_x)
    //          - lab2::Matrix::vector_mul(v_k, v_k) / (v_k * delta_w_k);
    //    G                = &G_k;
    //    p                = (*G) * w_k;
    //    const auto alpha = lab1::Brent(
    //                           [&f, x = x_k_1, p_ = p](double a) {
    //                               return f(x + p_ * a);
    //                           },
    //                           ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
    //                           .optimize();
    //    delta_x = p * alpha;
    return x_k_1 + delta_x;
}

bool DFP::is_done(lab2::NFunction &, double epsilon) const {
    return delta_x.norm() < epsilon;
}