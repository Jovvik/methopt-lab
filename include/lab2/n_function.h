#include "lab2/vector.h"

namespace lab2 {
    class NFunction {
      public:
        [[nodiscard]] virtual double operator()(Vector x) = 0;
        [[nodiscard]] virtual Vector grad(Vector x) = 0;
        [[nodiscard]] virtual std::size_t get_dim() = 0;
        [[nodiscard]] std::size_t get_call_count() const;
        [[nodiscard]] std::size_t get_grad_count() const;

      protected:
        void inc_call_count();
        void inc_grad_count();

      private:
        std::size_t call_count = 0;
        std::size_t grad_count = 0;
    };
}  // namespace lab2
