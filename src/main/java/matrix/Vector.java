package matrix;

import java.util.ArrayList;
import java.util.List;

public class Vector {

    public Vector(List<Double> list) {
        values = list;
        dim = list.size();
    }

    public double get(int index) {
        return values.get(index - 1);
    }

    public void set(int index, double value) {
        values.set(index - 1, value);
    }

    public double mulVector(Vector other) {
        assert (other.dim == dim);
        double res = 0;
        for (int i = 1; i <= dim; i++) {
            res += other.get(i) * get(i);
        }
        return res;
    }

    public Vector addVector(Vector other) {
        assert (other.dim == dim);
        List<Double> res = new ArrayList<>();
        for (int i = 1; i <= dim; i++) {
            res.add(get(i) + other.get(i));
        }
        return new Vector(res);
    }

    public Vector subVector(Vector other) {
        return addVector(other.mulNumber(-1));
    }

    public Vector mulNumber(double value) {
        List<Double> res = new ArrayList<>();
        for (double d : values) {
            res.add(d * value);
        }
        return new Vector(res);
    }

    public double norm() {
        double res = 0;
        for (double value : values) {
            res += value * value;
        }
        return Math.sqrt(res);
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        for (double value : values) {
            res.append(value).append(" ");
        }
        return res.toString();
    }

    public int size() {
        return dim;
    }

    public Vector copy() {
        return new Vector(getValues());
    }

    public List<Double> getValues() {
        return new ArrayList<>(values);
    }

    private final List<Double> values;
    private final int dim;
}
