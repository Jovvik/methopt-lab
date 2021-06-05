package matrix;

import static matrix.Utils.parseDoubleList;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Solver {
    public static void main(String[] args) throws IOException {
        int n = Integer.parseInt(args[0]);
        List<List<Double>> mat = new ArrayList<>();
        try (var reader = Files.newBufferedReader(Path.of("data", "A.txt"))) {
            for (int i = 0; i < n; i++) {
                mat.add(parseDoubleList(reader));
            }
        }
        List<Double> b = parseDoubleList(Files.newBufferedReader(Path.of("data", "b.txt")));
        Files.writeString(Path.of("data", "x.txt"), new DenseMatrix(mat).gauss(b, true).stream().map(Object::toString)
                .collect(Collectors.joining(" ", "", "\n")));
    }
}
