package matrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Function;

import static java.lang.Math.max;

/**
 * Генератор разреженных матриц
 */
public class SparseMatrixGenerator extends Generator {
    SparseMatrixGenerator(Args args) {
        super(args);
    }

    @Override
    void generate(BiFunction<Integer, Integer, Double> aValueGenerator, Function<Integer, Double> bValueGenerator)
            throws IOException {
        List<Double> di = new ArrayList<>(), al = new ArrayList<>(), au = new ArrayList<>(), b = new ArrayList<>();
        List<Integer> ia = new ArrayList<>(), ja = new ArrayList<>();
        ia.add(1);
        for (int i = 1; i <= args.dim; i++) {
            ia.add(ia.get(ia.size() - 1));
            int temp = 0;
            for (int j = max(1, i - args.belowDiagsCount); j < i; j++) {
                double dAL = valueOrZero(aValueGenerator.apply(i, j), args.zeroProbability), dAU;
                if (dAL == 0) {
                    continue;
                }
                temp++;
//                dAU = valueNonZero(aValueGenerator, i, j);
                al.add(dAL);
                au.add(dAL);
                ja.add(j);
            }
            ia.set(ia.size() - 1, ia.get(ia.size() - 1) + temp);
            di.add(valueNonZero(aValueGenerator, i, i));
            b.add(valueOrZero(bValueGenerator.apply(i), args.zeroProbability));
        }
        prepareDir();
        writeList(List.of(args.dim), "A");
        writeList(di, "A");
        writeList(al, "A");
        writeList(au, "A");
        writeList(ia, "A");
        writeList(ja, "A");
        writeList(b, "b");
    }

    @Override
    Matrix readMatrix(BufferedReader reader) throws IOException {
        return new SparseMatrix(reader);
    }
}
