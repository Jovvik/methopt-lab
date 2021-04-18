#include "lab1/brent.h"

#include <cmath>
#include <iostream>

using namespace lab1;

Brent::Brent(const func& optimized_function, double epsilon, double start,
             double end)
    : Optimizer(optimized_function, epsilon, start, end) {
    x = end;
    w = x;
    v = x;
    fx = f(x);
    fw = fx;
    fv = fx;
    d = e = end - start;
}

bool Brent::is_done() { return m_is_done || Optimizer::is_done(); }

void Brent::step() {
    double min = segment.get_start();
    double max = segment.get_end();
    double mid = (min + max) / 2;
    double tol = epsilon * std::abs(x) + epsilon / 10;
    if (std::abs(x - mid) + (max - min) / 2 <= tol * 2) {
        m_is_done = true;
        return;
    }
    double u, fu;
    bool using_parabola = false;

    if (std::abs(e) > tol) {
        double r = (x - w) * (fx - fv);
        double q = (x - v) * (fx - fw);
        double p = (x - v) * q - (x - w) * r;
        q = 2 * (q - r);
        if (q > 0) p = -p;
        q = std::abs(q);
        double g = e;
        e = d;
        // Проверка точности параболы:
        if ((std::abs(p) >= std::abs(q * g / 2)) || (p <= q * (min - x))
            || (p >= q * (max - x))) {
            // Парабола неточная, используем золотое сечение
            e = (x >= mid) ? min - x : max - x;
            d = TAU * e;
        } else {
            // Используем параболу
            d = p / q;
            u = x + d;
            if (((u - min) < tol * 2) || ((max - u) < tol * 2)) {
                d = std::copysign(tol, mid - x);
            }
            using_parabola = true;
        }
    } else {
        // Используем золотое сечение
        e = (x >= mid) ? min - x : max - x;
        d = TAU * e;
    }
    if (std::abs(d) >= tol) {
        u = x + d;
    } else {
        u = x + std::copysign(tol, d);
    }
    fu = f(u);
    if (using_parabola) {
        segment.set_mid(u);
    }

    segment.saved_points["u"] = {u, fu};
    segment.saved_points["w"] = {w, fw};
    segment.saved_points["x"] = {x, fx};
    segment.saved_points["v"] = {v, fv};
    save_segment();

    if (fu <= fx) {
        if (u >= x) {
            min = x;
        } else {
            max = x;
        }
        v = w;
        w = x;
        x = u;
        fv = fw;
        fw = fx;
        fx = fu;
    } else {
        if (u < x) {
            min = u;
        } else {
            max = u;
        }
        if ((fu <= fw) || (w == x)) {
            v = w;
            w = u;
            fv = fw;
            fw = fu;
        } else if ((fu <= fv) || (v == x) || (v == w)) {
            v = u;
            fv = fu;
        }
    }

    segment = {min, max};
}
