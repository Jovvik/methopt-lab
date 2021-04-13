#include "lab2/vector.h"

namespace lab2 {
    /**
     * Абстрактный класс N-мерной функции
     */
    class NFunction {
      public:
        /**
         * Вычисление функции
         * @param x Точка, в которой нужно вычислить функцию
         * @return Значение функции в точке x
         */
        [[nodiscard]] virtual double operator()(Vector x) = 0;
        /**
         * Вычисление градиента функции
         * @param x Точка, в которой нужно вычислить градиент функции
         * @return Значение градиента функции в точке x
         */
        [[nodiscard]] virtual Vector grad(Vector x) = 0;
        /**
         * @return Размерность функции
         */
        [[nodiscard]] virtual std::size_t get_dim() = 0;
        /**
         * @return Число вызовов функции
         */
        [[nodiscard]] std::size_t get_call_count() const;
        /**
         * @return Число вычислений градиента фукнции
         */
        [[nodiscard]] std::size_t get_grad_count() const;

      protected:
        /**
         * Увеличивает число вызовов функции на 1
         */
        void inc_call_count();
        /**
         * Увеличивает число вычислений градиента функции на 1
         */
        void inc_grad_count();

      private:
        std::size_t call_count = 0;
        std::size_t grad_count = 0;
    };
}  // namespace lab2
