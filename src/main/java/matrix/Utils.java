package matrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.Arrays;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

public interface Utils {
    static <T> List<T> parseList(BufferedReader reader, Function<String, T> parser) throws IOException {
        return Arrays.stream(reader.readLine().split("\\s+"))
                .map(parser)
                .collect(Collectors.toList());
    }

    static List<Double> parseDoubleList(BufferedReader reader) throws IOException {
        return parseList(reader, Double::parseDouble);
    }

    static List<Integer> parseIntegerList(BufferedReader reader) throws IOException {
        return parseList(reader, Integer::parseInt);
    }

    static boolean eof(Reader r) throws IOException {
        r.mark(1);
        int i = r.read();
        r.reset();
        return i < 0;
    }   
}
