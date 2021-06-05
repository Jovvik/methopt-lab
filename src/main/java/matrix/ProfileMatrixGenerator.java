package matrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Function;

import static java.lang.Math.max;

public class ProfileMatrixGenerator extends Generator {
    ProfileMatrixGenerator(Args args) {
        super(args);
    }

    @Override
    protected void generate(BiFunction<Integer, Integer, Double> aValueGenerator,
                            Function<Integer, Double> bValueGenerator) throws IOException {
        List<Double> di = new ArrayList<>(), al = new ArrayList<>(), au = new ArrayList<>(), b = new ArrayList<>();
        List<Integer> ia = new ArrayList<>();
        ia.add(1);
        for (int i = 1; i <= args.dim; i++) {
            ia.add(ia.get(ia.size() - 1));
            boolean flag = false;
            for (int j = max(1, i - args.belowDiagsCount); j < i; j++) {
                double dAL = valueOrZero(aValueGenerator.apply(i, j), args.zeroProbability), dAU;
                if (dAL == 0) {
                    dAU = 0;
                } else {
                    dAU = valueNonZero(aValueGenerator, i, j);
                }
                if (!flag) {
                    if (dAL != 0) {
                        flag = true;
                        al.add(dAL);
                        au.add(dAU);
                        ia.set(ia.size() - 1, ia.get(ia.size() - 1) + i - j);
                    }
                } else {
                    al.add(dAL);
                    au.add(dAU);
                }
            }
            di.add(valueNonZero(aValueGenerator, i, i));
            b.add(valueOrZero(bValueGenerator.apply(i), args.zeroProbability));
        }
        prepareDir();
        writeList(List.of(args.dim), "A");
        writeList(di, "A");
        writeList(al, "A");
        writeList(au, "A");
        writeList(ia, "A");
        writeList(b, "b");
    }

    @Override
    Matrix readMatrix(BufferedReader reader) throws IOException {
        return new ProfileMatrix(reader);
    }
}