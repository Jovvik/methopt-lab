#include "lab2/drawer.h"

#include "iostream"
#include "lab1/brent.h"
#include "lab1/dichotomy.h"
#include "lab1/fibonacci.h"
#include "lab1/golden_ratio.h"
#include "lab1/optimizer.h"
#include "lab1/parabola.h"
#include "lab2/conjugate_gradient.h"
#include "lab2/fastest_descent.h"
#include "lab2/function_2d.h"
#include "lab2/gradient_descent.h"

using namespace gui2;
using namespace lab2;

#define new_fastest(_optimizer_1d)                                       \
    new lab2::FastestDescent(                                            \
        [](const std::function<double(double)> &optimized_function,      \
           double epsilon, double start, double end) {                   \
            return std::make_unique<_optimizer_1d>(optimized_function,   \
                                                   epsilon, start, end); \
        })

// class Parabola {
//   public:
//     Parabola(double a, double b, double c) {
//         x1 = a;
//         x2 = b;
//         x3 = c;
//         a0 = f(x1);
//         a1 = (f(x2) - f(x1)) / (x2 - x1);
//         a2 = ((f(x3) - f(x1)) / (x3 - x1) - (f(x2) - f(x1)) / (x2 - x1))
//              / (x3 - x2);
//     }
//
//     double q(double x) const {
//         return a0 + a1 * (x - x1) + a2 * (x - x1) * (x - x2);
//     }
//
//   private:
//     double a0, a1, a2, x1, x2, x3;
// };

Drawer::Drawer(QWidget *parent) : QCustomPlot(parent) {
    Drawer::setInteraction(QCP::iRangeDrag, true);
    Drawer::setInteraction(QCP::iRangeZoom, true);
    Drawer::setInteraction(QCP::iSelectPlottables, true);
    connect(this, &QCustomPlot::beforeReplot, this, &Drawer::replot_f);
    connect(this, &QCustomPlot::plottableClick, this,
            &Drawer::rescale_on_click);
}
// void Drawer::draw(int iteration) {
//     clearGraphs();
//     addGraph();
//     addGraph();
//     addGraph();
//     graph(0)->setPen(QPen(Qt::blue));
//     graph(1)->setPen(QPen(Qt::green));
//     graph(2)->setPen(QPen(Qt::red));
//     graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
//     graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
//     iteration == 0 ? replot() : _draw(iteration - 1);
// }
// void Drawer::_draw(int iteration) {
//     lab1::Segment segment = segments[iteration];
//     draw_answer(segment.get_ans());
//     draw_method(segment);
//     replot();
// }
// void Drawer::draw_answer(std::optional<double> ans) {
//     if (ans) {
//         graph(1)->addData(*ans, f(*ans));
//     }
// }
// void Drawer::draw_method(lab1::Segment segment) {
//     double a = segment.get_start(), b = segment.get_end();
//     auto mid_opt = segment.get_mid();
//     graph(2)->addData(a, f(a));
//     graph(2)->addData(b, f(b));
//     if (mid_opt) {
//         addGraph();
//         double mid = *mid_opt;
//         graph(2)->setLineStyle(QCPGraph::LineStyle::lsNone);
//         graph(2)->addData(mid, f(mid));
//         graph(3)->setPen(QPen(Qt::red));
//         replot_function_and_set(
//             std::bind(&Parabola::q, Parabola(a, mid, b),
//             std::placeholders::_1), -2, 3, 3);
//     }
// }
void Drawer::recalc_optimize_points() {
    lab2::NOptimizer *n_optimizer;
    switch (method_2d) {
        case lab2::NOptimizers::GRADIENT_DESCENT:
            n_optimizer = new lab2::GradientDescent(0.005);
            break;
        case lab2::NOptimizers::CONJUGATE_GRADIENT:
            n_optimizer = new lab2::ConjugateGradient();
            break;
        case lab2::NOptimizers::FASTEST_DESCENT:
            switch (method_1d) {
                case lab1::Optimizers::DICHOTOMY:
                    n_optimizer = new_fastest(lab1::Dichotomy);
                    break;
                case lab1::Optimizers::GOLDEN_RATIO:
                    n_optimizer = new_fastest(lab1::GoldenRatio);
                    break;
                case lab1::Optimizers::FIBONACCI:
                    n_optimizer = new_fastest(lab1::Fibonacci);
                    break;
                case lab1::Optimizers::PARABOLA:
                    n_optimizer = new_fastest(lab1::Parabola);
                    break;
                case lab1::Optimizers::BRENT:
                    n_optimizer = new_fastest(lab1::Brent);
                    break;
            }
    }
    n_optimizer->optimize(*func.f, starting_point, pepsilon);
    optimize_points = n_optimizer->get_points();
}

void Drawer::change() {
    setup();
    emit method_changed(optimize_points.size());
}

// void Drawer::set_func(const QString &text) { change(); }

void Drawer::set_method_2d(const QString &text) {
    method_2d = lab2::n_optimizers_table.at(text.toStdString());
    change();
}

void Drawer::set_method_1d(const QString &text) {
    method_1d = lab1::optimizers_table.at(text.toStdString());
    change();
}

void Drawer::setup() {
    xAxis->setRange(-10, 10);
    yAxis->setRange(-10, 10);
    recalc_optimize_points();
//    curves = std::vector<QCPCurve *>(LINE_COUNT, new QCPCurve(xAxis, yAxis));
        for (int i=0;i<LINE_COUNT;i++) {
            curves.emplace_back(new QCPCurve(xAxis, yAxis));
        }
    replot();
}

void Drawer::replot_f() {
    auto [start, end]     = xAxis->range();
    auto [start_y, end_y] = yAxis->range();
    double step = (end - start) / COUNT, line_step = (end - start) / LINE_COUNT,
           y = start_y + (end_y - start_y) / 2;
    for (int index = 0; index < LINE_COUNT; index++) {
        std::vector<double> x_up, x_down, y_up, y_down, t;
        double z = func(start + index * line_step, y);
        std::cout << index << "\n";
        for (double point = start; point < end; point += step) {
            try {
                auto temp  = func.get_y(point, z);
                double y_d = temp.first, y_u = temp.second;
                if (y_d > y_u) {
                    std::swap(y_d, y_u);
                }
                if (y_d == y_d) {
                    x_down.emplace_back(point);
                    y_down.emplace_back(y_d);
                }
                if (y_u == y_u && y_u != y_d) {
                    x_up.emplace_back(point);
                    y_up.emplace_back(y_u);
                }
            } catch (std::overflow_error &ignored) {
            }
        }
        x_up.insert(x_up.end(), x_down.rbegin(), x_down.rend());
        y_up.insert(y_up.end(), y_down.rbegin(), y_down.rend());
        //        std::cout << x_up.size() << "!\n";
        //        for (double x_1 : x_up) {
        //            std::cout << (int)x_1 << " ";
        //        }
        //        std::cout << "\n";
        //        for (double y_1 : y_up) {
        //            std::cout << (int)y_1 << " ";
        //        }
        //        std::cout << "\n";
        curves[index]->setData(QVector<double>::fromStdVector(x_up),
                               QVector<double>::fromStdVector(y_up));
        //                graph(index)->setData(QVector<double>::fromStdVector(x_up),
        //                                      QVector<double>::fromStdVector(y_up),
        //                                      true);
        //        graph(index)->setBrush(QBrush(QColor(0, 0, 255, 20)));
        //        graph(index)->setData(QVector<double>(), QVector<double>());
        //        graph(index)->addData(QVector<double>::fromStdVector(x_down),
        //                              QVector<double>::fromStdVector(y_down));
        //        graph(index)->addData(QVector<double>::fromStdVector(x_up),
        //                              QVector<double>::fromStdVector(y_up));
    }
    //    auto *curve = new QCPCurve(xAxis, yAxis);
    //    curve->setData(
    //        QVector<double>::fromStdVector({-15, -4, 5, 15, 15, 5, -4, -15}),
    //        QVector<double>::fromStdVector({19, 19, 13, 2, -20, -21, -16,
    //        -5}));
    //    graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    //    graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
}

void Drawer::rescale_on_click(QCPAbstractPlottable *plottable, int,
                              QMouseEvent *) {
    plottable->rescaleAxes();
}