package matrix;

import com.beust.jcommander.JCommander;
import com.beust.jcommander.Parameter;
import org.apache.commons.io.FileUtils;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import static java.lang.Math.pow;
import static matrix.Utils.*;

/**
 * Абстрактный класс генератора матрицы
 */
public abstract class Generator {

    Generator(Args args) {
        this.args = args;
    }

    /**
     * Фабрика матриц
     */
    abstract Matrix readMatrix(BufferedReader reader) throws IOException;

    abstract void generate(BiFunction<Integer, Integer, Double> aValueGenerator,
                           Function<Integer, Double> bValueGenerator) throws IOException;

    /**
     * Очищает и создает папку
     */
    public void prepareDir() throws IOException {
        final var testDirectory = Path.of(args.root, args.testName);
        FileUtils.deleteDirectory(new File(testDirectory.toString()));
        Files.createDirectories(testDirectory);
    }

    /**
     * Процедура генерации матрицы
     */
    protected void generate() throws IOException {
        switch (args.type) {
            case "int" -> generateInt();
            case "random" -> generateRandom();
            case "hilbert" -> generateHilbert();
            case "seq" -> generateSequence();
            default -> throw new IllegalStateException("Unexpected type: " + args.type);
        }
    }

    protected void generateRandom() throws IOException {
        generate((i, j) -> ThreadLocalRandom.current().nextDouble(args.min, args.max),
                i -> ThreadLocalRandom.current().nextDouble(args.min, args.max));
    }

    protected void generateInt() throws IOException {
        generate((i, j) -> (double) ThreadLocalRandom.current().nextInt((int) args.min, (int) args.max),
                i -> (double) ThreadLocalRandom.current().nextInt((int) args.min, (int) args.max));
    }

    protected void generateHilbert() throws IOException {
        args.zeroProbability = 0;
        args.belowDiagsCount = args.dim;
        generate((i, j) -> 1. / (i + j - 1), i -> ThreadLocalRandom.current().nextDouble(args.min, args.max));

        var A = readMatrix(Files.newBufferedReader(Path.of(args.root, args.testName, "A.txt")));
        Files.delete(Path.of(args.root, args.testName, "b.txt"));
        writeList(A.mulVector(IntStream.rangeClosed(1, args.dim).boxed().collect(Collectors.toList())), "b");
    }

    protected double valueOrZero(double value, double zeroProbability) {
        if (ThreadLocalRandom.current().nextDouble(0, 1) < zeroProbability) {
            return 0;
        }
        return value;
    }

    protected double valueNonZero(BiFunction<Integer, Integer, Double> doubleGenerator, int i, int j) {
        double res = doubleGenerator.apply(i, j);
        while (res == 0) {
            res = doubleGenerator.apply(i, j);
        }
        return res;
    }

    protected void generateSequence() throws IOException {
        main("-t", "int", "--min", "-4", "--max", "0", "-n", "tmp", "-d", String.valueOf(args.dim), "-c",
                String.valueOf(args.belowDiagsCount), "--kind", args.kind);
        final String originalTestName = args.testName;
        for (int k = 0; k <= args.maxk; k++) {
            var APath = Path.of(args.root, "tmp", "A.txt");
            var A = readMatrix(Files.newBufferedReader(APath));

            var di = new ArrayList<Double>();
            for (int i = 1; i <= args.dim; i++) {
                double sum = 0;
                for (int j = 1; j <= args.dim; j++) {
                    if (i == j) {
                        continue;
                    }
                    sum += A.get(i, j);
                }
                if (i == 1) {
                    sum -= pow(10, -k);
                }
                di.add(-sum);
            }

            try (var reader = Files.newBufferedReader(APath)) {
                args.testName = originalTestName + "_" + k;
                prepareDir();
                writeList(parseIntegerList(reader), "A");
                writeList(di, "A");
                parseDoubleList(reader); // old di ignored
                writeList(parseDoubleList(reader), "A");
                writeList(parseDoubleList(reader), "A");
                while (!eof(reader)) {
                    writeList(parseIntegerList(reader), "A");
                }
            }

            var newA = readMatrix(Files.newBufferedReader(Path.of(args.root, args.testName, "A.txt")));
            writeList(newA.mulVector(IntStream.rangeClosed(1, args.dim).boxed().collect(Collectors.toList())), "b");
        }
    }

    /**
     * Записывает список в файл с именем {@code name} в папку {@code root}
     */
    protected <T> void writeList(List<T> list, String name) throws IOException {
        Files.writeString(Path.of(args.root, args.testName, name + ".txt"),
                list.stream().map(Object::toString).collect(Collectors.joining(" ", "", "\n")),
                StandardOpenOption.APPEND, StandardOpenOption.WRITE, StandardOpenOption.CREATE);
    }

    protected static class Args {
        @Parameter(names = {"-r", "--root"}, description = "Корень всех тестов")
        protected String root = "data";

        @Parameter(names = {"-n", "--test_name"}, description = "Название теста и соотвествующей папки")
        protected String testName;

        @Parameter(names = {"-h", "--help"}, help = true, description = "Вывести помощь")
        protected boolean help;

        @Parameter(names = {"-d", "--dimensionality"}, description = "Размерность")
        protected int dim = 6;

        @Parameter(names = {"-c", "--diag_count"}, description = "Количество ненулевых диагоналей")
        protected int belowDiagsCount = 2;

        @Parameter(names = {"-z", "--zero_probability"}, description = "Вероятность элемента матрицы быть нулём")
        protected double zeroProbability = 0.2;

        @Parameter(names = "--min", description = "Минимальное значение элемента")
        protected double min = -4;

        @Parameter(names = "--max", description = "Максимальное значение элемента")
        protected double max = 0;

        @Parameter(names = {"-t", "--type"}, description = "Тип генератора")
        protected String type = "int";

        @Parameter(names = "--maxk", description = "Максимальное k")
        protected int maxk = 10;

        @Parameter(names = {"-k", "--kind"}, description = "Вид генерируемой матрицы (sparse, profile)")
        protected String kind;
    }

    protected final Args args;

    public static void main(String... args) throws IOException {
        var argv = new Args();
        var jc = new JCommander(argv);
        jc.parse(args);

        if (argv.help) {
            jc.usage();
            return;
        }

        switch (argv.kind) {
            case "sparse" -> new SparseMatrixGenerator(argv).generate();
            case "profile" -> new ProfileMatrixGenerator(argv).generate();
            default -> throw new IllegalArgumentException(argv.kind + " is not a valid matrix kind");
        }
    }
}
