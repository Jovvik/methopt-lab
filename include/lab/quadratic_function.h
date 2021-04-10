#include "lab/matrix.h"
#include "lab/n_function.h"
#include "lab/vector.h"

namespace lab {
    class QuadraticFunction : public NFunction {
      private:
        const Matrix A;
        const Vector b;
        const double c;

      public:
        QuadraticFunction(Matrix&& A, Vector&& b, double c);
        double operator()(Vector x);
        Vector grad(Vector x);
        std::size_t get_dim();
    };
}  // namespace lab
