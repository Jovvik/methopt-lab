#pragma once

#include "lab2/n_function.h"
#include "lab2/quadratic_function.h"
#include "lab2/vector.h"

namespace lab2 {
    /**
     * Абстрактный класс оптимизатора N-мерных функций
     */
    enum class NOptimizers {
        CONJUGATE_GRADIENT,
        FASTEST_DESCENT,
        GRADIENT_DESCENT
    };

    static std::unordered_map<std::string, NOptimizers> const n_optimizers_table
        = {{"Градиентный спуск", NOptimizers::GRADIENT_DESCENT},
           {"Наискорейший спуск", NOptimizers::FASTEST_DESCENT},
           {"Сопряжённые градиенты", NOptimizers::CONJUGATE_GRADIENT}};

    class NOptimizer {
      public:
        /**
         * Процедура оптимизации.
         * @param f Оптимизируемая функция
         * @param starting_point Точка, из которой производится оптимизация
         * @param epsilon Искомая точность оптимизации
         * @return Минимум f
         */
        Vector optimize(QuadraticFunction& f, const Vector& starting_point,
                        double epsilon);
        /**
         * Возвращает вектор точек, рассмотренных в ходе оптимизации
         * @return Рассмотренные точки
         */
        [[nodiscard]] const std::vector<Vector>& get_points() const;

      protected:
        /**
         * @param f Оптимизируемая функция
         * @param epsilon Искомая точность
         * @return Достигнута ли искомая точность
         */
        [[nodiscard]] bool is_done(QuadraticFunction& f, double epsilon) const;
        /**
         * Итерация алгоритма оптимизации
         * @param f Оптимизируемая функция
         * @return Новая рассматриваемая точка
         */
        [[nodiscard]] virtual Vector iteration(QuadraticFunction& f,
                                               double epsilon)
            = 0;

        std::size_t iteration_count;

      private:
        /**
         * Вектор точек, рассмотренных в ходе оптимизации
         */
        std::vector<Vector> points;
    };

}  // namespace lab2
