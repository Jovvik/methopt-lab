#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <vector>

#include "lab/segment.h"

namespace lab {

    using func = std::function<double(double)>;

    /**
     * Абстрактный класс оптимизатора
     */
    class Optimizer {
      public:
        /**
         * @param optimized_function Оптимизируемая функция
         * @param epsilon Необходимая точность ответа
         * @param start Левая граница отрезка, на котором происходит оптимизация
         * @param end Правая граница отрезка, на котором происходит оптимизация
         * @return Локальный минимум
         */
        Optimizer(const func& optimized_function, double epsilon, double start,
                  double end);

        /**
         * Процедура оптимизации
         *
         * @return результат оптимизации
         */
        double optimize();

        /**
         * @return Сегменты, которые рассматривались во время оптимизации
         */
        const std::vector<Segment>& get_segments();

      protected:
        /**
         * @param current_segment Рассматриваемый сегмент
         * @param epsilon Искомая точность
         * @return Достигнута ли искомая точность
         */
        virtual bool is_done();

        /**
         * Выполняет один шаг
         */
        virtual void step() = 0;

        /**
         * @return Результат работы метода
         */
        virtual double answer() = 0;

        func f;
        Segment segment;
        double epsilon;

        /**
         * Число выполненных шагов алгоритма
         */
        int steps_count;

      private:
        std::vector<Segment> calculated_segments;
    };

}  // namespace lab
