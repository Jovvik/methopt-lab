import matrix.LUDecomposition;
import matrix.ProfileMatrix;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;

class MatrixTest {
    @Test
    void read() throws IOException {
        final ProfileMatrix matrix = new ProfileMatrix(Files.newBufferedReader(Path.of("data", "test1.txt")));
        var coordinates = new ArrayList<Map.Entry<Integer, Integer>>();
        for (int i = 1; i <= 9; i++) {
            coordinates.add(Map.entry(i, i));
        }
        coordinates.add(Map.entry(3, 2));
        coordinates.add(Map.entry(4, 2));
        coordinates.add(Map.entry(5, 3));
        coordinates.add(Map.entry(5, 4));
        coordinates.add(Map.entry(6, 3));
        coordinates.add(Map.entry(6, 5));
        coordinates.add(Map.entry(7, 4));
        coordinates.add(Map.entry(8, 5));
        coordinates.add(Map.entry(8, 6));
        coordinates.add(Map.entry(9, 5));
        coordinates.add(Map.entry(9, 7));
        coordinates.add(Map.entry(2, 3));
        coordinates.add(Map.entry(2, 4));
        coordinates.add(Map.entry(3, 5));
        coordinates.add(Map.entry(4, 5));
        coordinates.add(Map.entry(3, 6));
        coordinates.add(Map.entry(5, 6));
        coordinates.add(Map.entry(4, 7));
        coordinates.add(Map.entry(5, 8));
        coordinates.add(Map.entry(6, 8));
        coordinates.add(Map.entry(5, 9));
        coordinates.add(Map.entry(7, 9));
        for (int i = 0; i < coordinates.size(); i++) {
            int x = coordinates.get(i).getKey();
            int y = coordinates.get(i).getValue();
            assertEquals(i + 1, matrix.get(x, y));
        }

        var coordinatesSet = new HashSet<>(coordinates);
        for (int x = 1; x <= 9; x++) {
            for (int y = 1; y <= 9; y++) {
                if (!coordinatesSet.contains(Map.entry(x, y))) {
                    assertEquals(0, matrix.get(x, y));
                }
            }
        }
    }

    @Test
    void mulVector() throws IOException {
        final ProfileMatrix matrix = new ProfileMatrix(Files.newBufferedReader(Path.of("data", "test1.txt")));
        assertEquals(List.of(1., 155., 294., 347., 763., 385., 392., 257., 316.), matrix.mulVector(List.of(1., 2., 3., 4., 5., 6., 7., 8., 9.)));
    }

    @Test
    void decomposition() throws IOException {
        final var matrix = new ProfileMatrix(Files.newBufferedReader(Path.of("data", "test2.txt")));
        final var LU = new LUDecomposition(matrix);
        final var L = List.of(-1., -1., 2., -1., 2., 2., 0., -3., -1.5, -7., 0., 0., -2., 3., -5.928571428571429, 0., 0., 0., -3., -0.07142857142857117, -0.2168674698795184);
        final var U = List.of(1., 3., 3., 0., 0., 0., 1., -0.5, -2., 0., 0., 1., 2., -1., 0., 1., 0.6428571428571429, 0.5714285714285714, 1., 0.963855421686747, 1.);
        int idx = 0;
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= i; j++, idx++) {
                assertEquals(L.get(idx), LU.getL(i, j));
            }
        }
        idx = 0;
        for (int i = 1; i <= 6; i++) {
            for (int j = i; j <= 6; j++, idx++) {
                assertEquals(U.get(idx), LU.getU(i, j));
            }
        }
    }

    @Test
    void directMethod() throws IOException {
        final var cases = List.of(
                Map.entry(List.of(1., 2., 3., 4., 5., 6.), List.of(-1.0, 0.5, 0.5, -0.8928571428571429, -1.463855421686747, -14.833333333333313)),
                Map.entry(List.of(6., 5., 4., 3., 2., 1.), List.of(-6.0, -0.5, -0.5, -0.10714285714285714, -0.22289156626506024, -3.0555555555555514)),
                Map.entry(List.of(1., 1., 1., 1., 1., 1.), List.of(-1.0, 0.0, 0.0, -0.14285714285714285, -0.24096385542168675, -2.555555555555552))
        );
        for (var t : cases) {
            var b = t.getKey();
            var x = t.getValue();
            var matrix = new ProfileMatrix(Files.newBufferedReader(Path.of("data", "test2.txt")));
            var LU = new LUDecomposition(matrix);
            assertEquals(x, LU.directMethod(b, false));
        }
    }
}
