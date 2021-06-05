package matrix;

import java.util.ArrayList;
import java.util.List;

/**
 * Плотная матрица
 */
public class DenseMatrix extends Matrix {
    DenseMatrix(List<List<Double>> matrix) {
        super(matrix.size());
        this.matrix = matrix;
    }

    /**
     * @return Эта матрица, умноженная на транспозицию себя
     */
    public DenseMatrix mulMatrixWithTransposeSelf() {
        List<List<Double>> res = new ArrayList<>();
        for (int i = 0; i < dim; i++) {
            res.add(new ArrayList<>());
            for (int j = 0; j < dim; j++) {
                res.get(i).add(0.);
            }
        }

        for (int i = 1; i <= dim; i++) {
            for (int j = 1; j <= dim; j++) {
                for (int r = 1; r <= dim; r++) {
                    res.get(i - 1).set(j - 1, res.get(i - 1).get(j - 1) + get(r, i) * get(r, j));
                }
            }
        }
        return new DenseMatrix(res);
    }

    @Override
    public void setImpl(int row, int column, Number value) {
        matrix.get(row - 1).set(column - 1, value.doubleValue());
    }

    @Override
    public double getImpl(int row, int column) {
        return matrix.get(row - 1).get(column - 1);
    }

    private final List<List<Double>> matrix;
}
