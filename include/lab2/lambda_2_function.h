#include "n_function.h"

namespace lab2 {

    class Lambda2Function : public NFunction {
      public:
        explicit Lambda2Function(
            std::function<double(double, double)> f,
            std::function<std::pair<double, double>(double, double)> grad);

        [[nodiscard]] double operator()(Vector x) override;
        [[nodiscard]] Vector grad(Vector x) override;
        [[nodiscard]] std::size_t get_dim() override;

      private:
        const std::function<double(double, double)> f;
        std::function<std::pair<double, double>(double, double)> f_grad;
    };

}  // namespace lab2
