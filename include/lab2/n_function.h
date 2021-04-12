#include "lab2/vector.h"

namespace lab2 {
    class NFunction {
      public:
        virtual double operator()(Vector x) = 0;
        virtual Vector grad(Vector x) = 0;
        virtual std::size_t get_dim() = 0;
        std::size_t get_call_count() const;
        std::size_t get_grad_count() const;

      protected:
        void inc_call_count();
        void inc_grad_count();

      private:
        std::size_t call_count = 0;
        std::size_t grad_count = 0;
    };
}  // namespace lab2
