package matrix;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import static matrix.Utils.parseDoubleList;

/**
 * Абстрактный класс матрицы
 */
public abstract class Matrix {

    Matrix(int dim) {
        this.dim = dim;
        index = IntStream.range(1, dim + 1)
                .boxed()
                .collect(Collectors.toList());
    }

    /**
     * @return Матрица в виде двумерного списка
     */
    public List<List<Double>> to2DList() {
        List<List<Double>> res = new ArrayList<>();
        for (int i = 1; i <= dim; i++) {
            res.add(new ArrayList<>());
            for (int j = 1; j <= dim; j++) {
                res.get(i - 1).add(get(i, j));
            }
        }
        return res;
    }

    /**
     * @return A * b
     */
    public List<Double> mulVector(List<? extends Number> b) {
        List<Double> res = new java.util.ArrayList<>(Collections.nCopies(dim, 0.));
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                res.set(i, res.get(i) + get(i + 1, j + 1) * b.get(j).doubleValue());
            }
        }
        return res;
    }

    public double get(int row, int column) {
        return getImpl(index.get(row - 1), column);
    }

    public void set(int row, int column, Number value) {
        setImpl(index.get(row - 1), column, value);
    }

    /**
     * Прямой шаг метода Гаусса
     *
     * @param b
     * @param modified Использовать ли выбор ведущего элемента
     */
    public List<Double> directMethod(List<Double> b, boolean modified) {
        List<Double> b1 = new ArrayList<>(b);
        for (int k = 1; k <= dim - 1; k++) {
            if (modified) {
                swap(k, b1);
            }
            for (int i = k + 1; i <= dim; i++) {
                double tIK = get(i, k) / get(k, k);
                b1.set(i - 1, b1.get(i - 1) - tIK * b1.get(k - 1));
                for (int j = k; j <= dim; j++) {
                    set(i, j, get(i, j) - tIK * get(k, j));
                }
            }
        }
        return b1;
    }

    /**
     * Обратный шаг метода Гаусса
     *
     * @param b
     */
    public List<Double> reverseMethod(List<Double> b) {
        List<Double> x = new ArrayList<>(Collections.nCopies(dim, 0.));
        x.set(dim - 1, b.get(dim - 1) / get(dim, dim));
        for (int k = dim - 1; k >= 1; k--) {
            double temp = b.get(k - 1);
            for (int j = k + 1; j <= dim; j++) {
                temp -= get(k, j) * x.get(j - 1);
            }
            x.set(k - 1, temp / get(k, k));
        }
        return x;
    }

    /**
     * Метод Гаусса
     *
     * @param b
     * @param modified Использовать ли выбор ведущего элемента
     * @return x такое, что Ax = b
     */
    public List<Double> gauss(List<Double> b, boolean modified) {
        return reverseMethod(directMethod(b, modified));
    }

    /**
     * Метод Гаусса
     *
     * @param b
     * @return x такое, что Ax = b
     */
    public List<Double> gauss(List<Double> b) {
        return gauss(b, false);
    }

    /**
     * Вывод матрицы в консоль
     */
    public void print() {
        print(Collections.emptyList());
    }

    /**
     * Вывод матрицы в консоль
     */
    public void print(List<?> b) {
        for (int i = 1; i <= dim; i++) {
            for (int j = 1; j <= dim; j++) {
                System.out.print(get(i, j) + " ");
            }
            if (b.isEmpty()) {
                System.out.println();
            } else {
                System.out.println(b.get(i - 1));
            }
        }
    }

    public abstract double getImpl(int row, int column);

    public abstract void setImpl(int row, int column, Number value);

    /**
     * Список переставленных строк
     */
    protected final List<Integer> index;

    /**
     * Размерность матрицы
     */
    protected final int dim;

    protected void swap(int row, List<Double> b) {
        int minRow = row;
        for (int i = row; i <= dim; i++) {
            if (Math.abs(get(i, row)) > Math.abs(get(minRow, row))) {
                minRow = i;
            }
        }
        int temp = index.get(row - 1);
        index.set(row - 1, index.get(minRow - 1));
        index.set(minRow - 1, temp);
        double temp2 = b.get(row - 1);
        b.set(row - 1, b.get(minRow - 1));
        b.set(minRow - 1, temp2);
    }
}
