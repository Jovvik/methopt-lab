#include "lab/brent.h"

#include <cmath>

using namespace lab;

Brent::Brent(const func& optimized_function, double epsilon, double start,
             double end)
    : Optimizer(optimized_function, epsilon, start, end) {
    x = (start + end) / 2;
    w = x;
    v = x;
    fx = f(x);
    fw = fx;
    fv = fx;
    d = end - start;
    e = d;
}

void Brent::step() {
    double a = segment.get_start();
    double c = segment.get_end();
    g = e;
    e = d;
    double u;

    if (areDistinct(x, w, v) && areDistinct(fx, fw, fv)) {
        u = parabola(x, w, v, fx, fw, fv);
        if (u >= a + epsilon && u <= c - epsilon && std::abs(u - x) < g / 2) {
            d = std::abs(u - x);
        } else {
            if (x < (c - a) / 2) {
                u = a + TAU * (c - x);
                d = c - x;
            } else {
                u = c - TAU * (x - a);
                d = x - a;
            }
        }
    } else {
        if (x < (c - a) / 2) {
            u = x + TAU * (c - x);
            d = c - x;
        } else {
            u = x - TAU * (x - a);
            d = x - a;
        }
        if (std::abs(u - x) < epsilon) {
            u = x + std::copysign(epsilon, u - x);
        }
    }
    double fu = f(u);
    if (fu <= fx) {
        if (u >= x) {
            segment = {x, c};
        } else {
            segment = {a, x};
        }
        v = w;
        w = x;
        x = u;
        fv = fw;
        fw = fx;
        fx = fu;
    } else {
        if (u >= x) {
            segment = {a, u};
        } else {
            segment = {u, c};
        }
        if (fu <= fw || w == x) {
            v = w;
            w = u;
            fv = fw;
            fw = fu;
        } else if (fu <= fv || v == x || v == w) {
            v = u;
            fv = fu;
        }
    }
}
