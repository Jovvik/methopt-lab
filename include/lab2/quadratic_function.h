#include "lab2/matrix.h"
#include "lab2/n_function.h"
#include "lab2/vector.h"

namespace lab2 {
    class QuadraticFunction : public NFunction {
      private:
        const Matrix A;
        const Vector b;
        const double c;

      public:
        QuadraticFunction(Matrix&& A, Vector&& b, double c);
        double operator()(Vector x) override;
        Vector grad(Vector x) override;
        std::size_t get_dim() override;
    };
}  // namespace lab2
