#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <vector>

#include "lab/segment.h"

namespace lab {

    using func = const std::function<double(double)>&;

    /**
     * Абстрактный класс оптимизатора
     */
    class Optimizer {
      public:
        /**
         * Главная процедура оптимизации
         *
         * @param optimized_function Оптимизируемая функция
         * @param epsilon Необходимая точность ответа
         * @param start Левая граница отрезка, на котором происходит оптимизация
         * @param end Правая граница отрезка, на котором происходит оптимизация
         * @return Локальный минимум
         */
        double optimize(func optimized_function, double epsilon, double start,
                        double end);

        /**
         * Возвращает сегменты, которые рассматривались во время оптимизации
         */
        const std::vector<Segment>& get_segments();

      protected:
        /**
         * @param current_segment Рассматриваемый сегмент
         * @param epsilon Искомая точность
         * @return Достигнута ли искомая точность
         */
        virtual bool is_done(Segment current_segment, double epsilon) = 0;

        /**
         * Выполняет один шаг
         */
        virtual Segment step(Segment current_segment, func optimized_function)
            = 0;

        /**
         * @return Результат работы метода
         */
        virtual double answer(Segment current_segment) = 0;

        /**
         * Находит точки в `current_segment`, которые будут использоваться для
         * следующего шага
         */
        virtual Segment new_segment(Segment current_segment,
                                    func optimized_function)
            = 0;

        /**
         * Число выполненных шагов алгоритма
         */
        int steps_count;

      private:
        std::vector<Segment> calculated_segments;
    };

}  // namespace lab
