#pragma once

#include <cmath>

#include "lab/optimizer.h"

namespace lab {
    /**
     * Общий класс оптимизаторов, которые на каждом шаге рассматривают две точки
     */
    class TwoPoint : public Optimizer {
        using Optimizer::Optimizer;

      protected:
        /**
         * Вычисляет `x1`, `x2`, `fx1` и `fx2`
         */
        void calc_points();

      protected:
        /**
         * Вычисляет первую точку для рассмотрения
         */
        virtual double get_x1(double start, double end) = 0;

        /**
         * Вычисляет вторую точку для рассмотрения
         */
        virtual double get_x2(double start, double end) = 0;

        /**
         * Рассматриваемые в отрезке точки
         */
        double x1, x2;
        /**
         * Значения оптимизируемой функции в рассматриваемых точках
         */
        double fx1, fx2;
    };

}  // namespace lab