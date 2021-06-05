package matrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javafx.util.Pair;

import static matrix.Utils.parseDoubleList;
import static matrix.Utils.parseIntegerList;

public class SparseMatrix extends Matrix {

    public SparseMatrix(BufferedReader reader) throws IOException {
        super(Integer.parseInt(reader.readLine()));
        di = parseDoubleList(reader);
        al = parseDoubleList(reader);
        au = parseDoubleList(reader);
        ia = parseIntegerList(reader);
        ja = parseIntegerList(reader);
    }

    public SparseMatrix(List<List<Double>> source) {
        super(source.size());
        di = new ArrayList<>();
        al = new ArrayList<>();
        au = new ArrayList<>();
        ia = new ArrayList<>();
        ja = new ArrayList<>();
        ia.add(1);
        for (int i = 1; i <= dim; i++) {
            ia.add(ia.get(ia.size() - 1));
            int temp = 0;
            for (int j = 1; j < i; j++) {
                double d = source.get(i - 1).get(j - 1);
                if (d == 0) {
                    continue;
                }
                temp++;
                al.add(d);
                au.add(source.get(j - 1).get(i - 1));
                ja.add(j);
            }
            ia.set(ia.size() - 1, ia.get(ia.size() - 1) + temp);
            di.add(source.get(i - 1).get(i - 1));
        }
    }

    public Vector msg(Vector f, double eps) {
        Vector
                x = new Vector(Collections.nCopies(dim, 1.)),
                r = f.subVector(mulVector(x)),
                z = r.copy();
        for (int k = 1; k <= MAX_ITERATIONS && r.norm() / f.norm() > eps; k++) {
            Vector rOld = r.copy();
            double a = r.mulVector(r) / mulVector(z).mulVector(z);
            x = x.addVector(z.mulNumber(a));
            r = r.subVector(mulVector(z).mulNumber(a));
            double b = r.mulVector(r) / rOld.mulVector(rOld);
            z = r.addVector(z.mulNumber(b));
        }
        return x;
    }

    public Vector mulVector(Vector b) {
        List<Double> res = new ArrayList<>(Collections.nCopies(dim, 0.));
        if ((dim != b.size())) throw new IllegalStateException();
        for (int i = 0; i < dim; i++) {
            int count = ia.get(i + 1) - ia.get(i);
            res.set(i, res.get(i) + di.get(i) * b.get(i + 1));
            for (int index = ia.get(i) - 1, indexLast = index + count; index < indexLast; index++) {
                int j = ja.get(index) - 1;
                res.set(i, res.get(i) + al.get(index) * b.get(j + 1));
                res.set(j, res.get(j) + au.get(index) * b.get(i + 1));
            }
        }
        return new Vector(res);
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

    /**
     * @return Пара из (a, b), где b - в котором из (al, di, au)
     * брать искомый элемент, а a - индекс в соответствующем массиве
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
        int count = ia.get(row + 1) - ia.get(row);
        for (int i = ia.get(row) - 1, lastI = i + count; i < lastI; i++) {
            if (column + 1 == ja.get(i)) {
                return new Pair<>(i, (aul == al ? 0 : 2));
            }
        }
        return null;
    }

    private static final int MAX_ITERATIONS = 50000;
    private final List<Double> di, al, au;
    private final List<Integer> ia, ja;
}
