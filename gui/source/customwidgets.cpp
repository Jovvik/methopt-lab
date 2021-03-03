#include "customwidgets.h"

#include "../../include/lab/dichotomy.h"
#include "../../include/lab/fibonacci.h"
#include "../../include/lab/golden_ratio.h"
#include "../../include/lab/parabola.h"
#include "../../include/lab/segment.h"
#include "../include/customwidgets.h"
class Parabola {
  public:
    Parabola(double a, double b, double c) {
        x1 = a;
        x2 = b;
        x3 = c;
        a0 = Drawer::f(x1);
        a1 = (Drawer::f(x2) - Drawer::f(x1)) / (x2 - x1);
        a2 = ((Drawer::f(x3) - Drawer::f(x1)) / (x3 - x1)
              - (Drawer::f(x2) - Drawer::f(x1)) / (x2 - x1))
             / (x3 - x2);
    }

    double q(double x) { return a0 + a1 * (x - x1) + a2 * (x - x1) * (x - x2); }

  private:
    double a0, a1, a2, x1, x2, x3;
};

Drawer::Drawer(QWidget *parent) : QCustomPlot(parent) {
    Drawer::setInteraction(QCP::iRangeDrag, true);
    Drawer::setInteraction(QCP::iRangeZoom, true);
    Drawer::setInteraction(QCP::iSelectPlottables, true);
    connect(this, &QCustomPlot::beforeReplot, this, &Drawer::replot_f);
    connect(this, &QCustomPlot::plottableClick, this,
            &Drawer::rescale_on_click);
    setup();
}
void Drawer::recalc_segments() {
    std::cout << "123";
    lab::Optimizer* optimizer;
    switch (method) {
//        case lab::Optimizers ::DICHOTOMY:
//            optimizer = new lab::Dichotomy(f, 1e-4, -2, 3);
//            break;
//        case lab::Optimizers ::GOLDEN_RATIO:
//            optimizer = new lab::GoldenRatio(f, 1e-4, -2, 3);
//            break;
//        case lab::Optimizers ::FIBONACCI:
//            optimizer = new lab::Fibonacci(f, 1e-4, -2, 3);
//            break;
        case lab::Optimizers ::PARABOLA:
            optimizer = new lab::Parabola(f, 1e-4, -2, 3);
            break;
//        case lab::Optimizers ::BRENT:
//            optimizer = new lab::Dichotomy(f, 1e-4, -2, 3);
//            break;
//        default:
//            break;
    }
//    optimizer->optimize();
//    segments = optimizer->get_segments();
}
void Drawer::draw(int iteration) {
    clearGraphs();
    addGraph();
    addGraph();
    addGraph();
    iteration == 0 ? replot() : _draw(iteration);
}
void Drawer::draw_answer(std::optional<double> ans) {
    if (ans) {
        graph(1)->setPen(QPen(Qt::green));
        graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
        graph(1)->addData(*ans, f(*ans));
    }
}
void Drawer::draw_method(lab::Segment segment) {
    double a = segment.get_start();
    double b = segment.get_end();
    graph(2)->setPen(QPen(Qt::red));
    switch (method) {
        case lab::Optimizers ::DICHOTOMY:
        case lab::Optimizers ::GOLDEN_RATIO:
        case lab::Optimizers ::FIBONACCI: {
            graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
            graph(2)->addData(a, f(a));
            graph(2)->addData(b, f(b));
            break;
        }
        case lab::Optimizers ::PARABOLA: {
            auto parabola = new Parabola(a, *segment.get_mid(), b);
            double step = (b - a) / COUNT;
            std::vector<double> x, y;
            for (double point = a; point < b; point += step) {
                x.emplace_back(point);
                y.emplace_back(parabola->q(point));
            }
            graph(2)->setData(QVector<double>::fromStdVector(x),
                              QVector<double>::fromStdVector(y));
            break;
        }
    }
}
void Drawer::_draw(int iteration) {
    lab::Segment segment = segments[iteration];
    draw_answer(segment.get_ans());
    draw_method(segment);
    replot();
}
void Drawer::set_method(const QString &text) {
    method = lab::optimizers_table.at(text.toStdString());
    setup();
    emit method_changed(segments.size());
}
void Drawer::setup() {
    clearGraphs();
    addGraph();
    xAxis->setRange(-2, 3);
    recalc_segments();
    replot();
}
void Drawer::replot_f() {
    auto [start, end] = xAxis->range();
    double step = (end - start) / COUNT;
    std::vector<double> x, y;
    for (double point = start; point < end; point += step) {
        x.emplace_back(point);
        y.emplace_back(f(point));
    }
    graph(0)->setPen(QPen(Qt::blue));
    graph(0)->setData(QVector<double>::fromStdVector(x),
                      QVector<double>::fromStdVector(y));
}
void Drawer::rescale_on_click(QCPAbstractPlottable *plottable, int _,
                              QMouseEvent *__) {
    plottable->rescaleAxes();
}

Slider::Slider(QWidget *parent)
    : QWidget(parent),
      slider(new QSlider(Qt::Horizontal, this)),
      label(new QLabel("0", this)) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(slider);
    layout->addWidget(label);
    connect(slider, &QSlider::valueChanged, label,
            static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
}
void Slider::setup(int size) {
    slider->setSliderPosition(0);
    slider->setMaximum(size);
}