package matrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import javafx.util.Pair;

import static matrix.Utils.parseDoubleList;
import static matrix.Utils.parseIntegerList;

/**
 * Профильная матрица
 */
public class ProfileMatrix extends Matrix {

    public ProfileMatrix(BufferedReader reader) throws IOException {
        super(Integer.parseInt(reader.readLine()));
        di = parseDoubleList(reader);
        al = parseDoubleList(reader);
        au = parseDoubleList(reader);
        ia = parseIntegerList(reader);
    }

    @Override
    public List<Double> gauss(List<Double> b, boolean modified) {
        if (modified) {
            throw new UnsupportedOperationException("modified gauss is used only on dense matrices");
        }
        return reverseMethod(directMethod(b, false));
    }

    @Override
    public List<Double> mulVector(List<? extends Number> b) {
        List<Double> res = new ArrayList<>(Collections.nCopies(dim, 0.));
        if ((dim != b.size()))
            throw new IllegalStateException();
        for (int i = 0; i < dim; i++) {
            int count = ia.get(i + 1) - ia.get(i);
            res.set(i, res.get(i) + di.get(i) * b.get(i).doubleValue());
            for (int j = i - count, index = ia.get(i) - 1; j < i; j++, index++) {
                res.set(i, res.get(i) + al.get(index) * b.get(j).doubleValue());
                res.set(j, res.get(j) + au.get(index) * b.get(i).doubleValue());
            }
        }
        return res;
    }

    @Override
    public double getImpl(int row, int column) {
        return getImpl(indexPair(row, column));
    }

    @Override
    public void setImpl(int row, int column, Number value) {
        var indexPair = indexPair(row, column);
        if (indexPair == null && value.doubleValue() == 0) {
            return;
        }
        assert (indexPair != null);
        int lDUIndex = indexPair.getKey();
        switch (indexPair.getValue()) {
            case 0 -> al.set(lDUIndex, value.doubleValue());
            case 1 -> di.set(lDUIndex, value.doubleValue());
            case 2 -> au.set(lDUIndex, value.doubleValue());
            default -> throw new IllegalStateException("Invalid indexPair");
        }
    }

    /**
     * @return Пара из (a, b), где b - в котором из (al, di, au) брать искомый
     *         элемент, а a - индекс в соответствующем массиве
     */
    private Pair<Integer, Integer> indexPair(int row, int column) {
        row--;
        column--;
        if (row == column) {
            return new Pair<>(row, 1);
        }
        List<Double> aul = al;
        if (row < column) {
            aul = au;
            int temp = row;
            row = column;
            column = temp;
        }
        int add = column - (row - (ia.get(row + 1) - ia.get(row)));
        if (add < 0) {
            return null;
        }
        return new Pair<>(ia.get(row) - 1 + add, (aul == al ? 0 : 2));
    }

    private double getImpl(Pair<Integer, Integer> indexPair) {
        if (indexPair == null) {
            return 0;
        }
        int lDUIndex = indexPair.getKey();
        return switch (indexPair.getValue()) {
            case 0 -> al.get(lDUIndex);
            case 1 -> di.get(lDUIndex);
            case 2 -> au.get(lDUIndex);
            default -> throw new IllegalStateException("Invalid indexPair");
        };
    }

    private final List<Double> di, al, au;
    private final List<Integer> ia;
}
