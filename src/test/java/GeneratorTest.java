import matrix.ProfileMatrix;
import matrix.ProfileMatrixGenerator;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import static matrix.Utils.parseDoubleList;
import static matrix.Utils.parseIntegerList;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class GeneratorTest {
    @Test
    void intTest() throws IOException {
        ProfileMatrixGenerator.main("--test_name", "1", "--type", "int", "--kind", "profile");
        Path matrixPath = Path.of("data", "1", "A.txt");
        Path vectorPath = Path.of("data", "1", "b.txt");
        assertTrue(Files.exists(matrixPath));
        assertTrue(Files.exists(vectorPath));
        var reader = Files.newBufferedReader(matrixPath);
        var dim = parseIntegerList(reader);
        assertEquals(1, dim.size());
        assertTrue(dim.get(0) > 0);
        reader.close();
        var matrix = new ProfileMatrix(Files.newBufferedReader(matrixPath));
        for (int i = 1; i <= dim.get(0); i++) {
            for (int j = 1; j <= dim.get(0); j++) {
                assertEquals(matrix.get(i, j), Math.rint(matrix.get(i, j)));
            }
        }
    }

    @Test
    void seqTest() throws IOException {
        ProfileMatrixGenerator.main("--test_name", "bruh", "--type", "seq", "--maxk", "10", "-d", "5", "--kind", "profile");
        for (int k = 0; k < 10; k++) {
            Path matrixPath = Path.of("data", "bruh_" + k, "A.txt");
            Path vectorPath = Path.of("data", "bruh_" + k, "b.txt");
            assertTrue(Files.exists(matrixPath));
            assertTrue(Files.exists(vectorPath));
            var A = new ProfileMatrix(Files.newBufferedReader(matrixPath));
            var b = parseDoubleList(Files.newBufferedReader(vectorPath));
            assertEquals(A.mulVector(IntStream.rangeClosed(1, 5).boxed().collect(Collectors.toList())), b);
        }
    }
}
