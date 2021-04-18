#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <vector>

#include "lab1/segment.h"

namespace lab1 {

    using func = std::function<double(double)>;

    enum class Optimizers {
        DICHOTOMY,
        GOLDEN_RATIO,
        FIBONACCI,
        PARABOLA,
        BRENT
    };
    static std::unordered_map<std::string, Optimizers> const optimizers_table
        = {{"Дихотомия", Optimizers::DICHOTOMY},
           {"Золотое сечение", Optimizers::GOLDEN_RATIO},
           {"Фиббоначи", Optimizers::FIBONACCI},
           {"Параболы", Optimizers::PARABOLA},
           {"Брент", Optimizers::BRENT}};
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

        virtual ~Optimizer() = default;

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
        virtual double answer();

        void save_segment();

        void unsave_segment();

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

}  // namespace lab1
