package matrix;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class LUDecomposition extends Matrix {

    public LUDecomposition(ProfileMatrix matrix) {
        super(matrix.dim);
        this.matrix = matrix;
        decompose();
    }

    @Override
    public List<Double> directMethod(List<Double> b_, boolean modified) {
        List<Double> b = new ArrayList<>(b_);
        for (int k = 1; k <= dim - 1; k++) {
            if (modified) {
                swap(k, b);
            }
            for (int i = k + 1; i <= dim; i++) {
                double tIK = getL(i, k) / getL(k, k);
                b.set(i - 1, b.get(i - 1) - tIK * b.get(k - 1));
                for (int j = k; j <= i; j++) {
                    setL(i, j, getL(i, j) - tIK * getL(k, j));
                }
            }
        }
        for (int k = 1; k <= dim; k++) {
            b.set(k - 1, b.get(k - 1) / getL(k, k));
        }
        return b;
    }

    @Override
    public List<Double> reverseMethod(List<Double> b) {
        List<Double> x = new ArrayList<>(Collections.nCopies(dim, 0.));
        x.set(dim - 1, b.get(dim - 1) / getU(dim, dim));
        for (int k = dim - 1; k >= 1; k--) {
            double temp = b.get(k - 1);
            for (int j = k + 1; j <= dim; j++) {
                temp -= getU(k, j) * x.get(j - 1);
            }
            x.set(k - 1, temp / getU(k, k));
        }
        return x;
    }

    @Override
    public double getImpl(int row, int column) {
        return matrix.get(row, column);
    }

    @Override
    public void setImpl(int row, int column, Number value) {
        matrix.set(row, column, value);
    }

    public double getL(int row, int column) {
        if (row < column) {
            return 0;
        }
        return matrix.get(row, column);
    }

    public double getU(int row, int column) {
        if (row > column) {
            return 0;
        }
        if (row == column) {
            return 1;
        }
        return matrix.get(row, column);
    }

    public void setL(int row, int column, Number value) {
        expectL(row, column);
        matrix.set(row, column, value);
    }

    public void setU(int row, int column, Number value) {
        expectR(row, column);
        matrix.set(row, column, value);
    }

    private void expectL(int row, int column) {
        if (row < column) {
            throw new IllegalArgumentException("row must be >= column");
        }
    }

    private void expectR(int row, int column) {
        if (row > column) {
            throw new IllegalArgumentException("row must be <= column");
        }
    }

    /**
     * Процедура LU-разложения
     */
    private void decompose() {
        double temp;
        for (int i = 2; i <= dim; i++) {
            // Lij
            for (int j = 1; j <= i - 1; j++) {
                temp = matrix.get(i, j);
                for (int k = 1; k <= j - 1; k++) {
                    temp -= getL(i, k) * getU(k, j);
                }
                setL(i, j, temp);
            }
            // Uji
            for (int j = 1; j <= i - 1; j++) {
                temp = matrix.get(j, i);
                for (int k = 1; k <= j - 1; k++) {
                    temp -= getL(j, k) * getU(k, i);
                }
                setU(j, i, temp / getL(j, j));
            }
            // Lii
            temp = matrix.get(i, i);
            for (int k = 1; k <= i - 1; k++) {
                temp -= getL(i, k) * getU(k, i);
            }
            setL(i, i, temp);
        }
    }

    public final Matrix matrix;
}
