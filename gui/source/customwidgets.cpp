#include "customwidgets.h"

#include "lab/brent.h"
#include "lab/dichotomy.h"
#include "lab/fibonacci.h"
#include "lab/functions.h"
#include "lab/golden_ratio.h"
#include "lab/parabola.h"
#include "lab/segment.h"

class Parabola {
  public:
    Parabola(double a, double b, double c) {
        x1 = a;
        x2 = b;
        x3 = c;
        a0 = f(x1);
        a1 = (f(x2) - f(x1)) / (x2 - x1);
        a2 = ((f(x3) - f(x1)) / (x3 - x1) - (f(x2) - f(x1)) / (x2 - x1))
             / (x3 - x2);
    }

    double q(double x) const {
        return a0 + a1 * (x - x1) + a2 * (x - x1) * (x - x2);
    }

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
}
void Drawer::recalc_segments() {
    lab::Optimizer *optimizer;
    switch (method) {
        case lab::Optimizers::DICHOTOMY:
            optimizer = new lab::Dichotomy(f, 1e-8, -2, 3);
            break;
        case lab::Optimizers::GOLDEN_RATIO:
            optimizer = new lab::GoldenRatio(f, 1e-8, -2, 3);
            break;
        case lab::Optimizers::FIBONACCI:
            optimizer = new lab::Fibonacci(f, 1e-8, -2, 3);
            break;
        case lab::Optimizers::PARABOLA:
            optimizer = new lab::Parabola(f, 1e-8, -2, 3);
            break;
        case lab::Optimizers::BRENT:
            optimizer = new lab::Brent(f, 1e-8, -2, 3);
            break;
    }
    optimizer->optimize();
    segments = optimizer->get_segments();
}
void Drawer::draw(int iteration) {
    clearGraphs();
    addGraph();
    addGraph();
    addGraph();
    graph(0)->setPen(QPen(Qt::blue));
    graph(1)->setPen(QPen(Qt::green));
    graph(2)->setPen(QPen(Qt::red));
    graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
    iteration == 0 ? replot() : _draw(iteration - 1);
}
void Drawer::_draw(int iteration) {
    lab::Segment segment = segments[iteration];
    draw_answer(segment.get_ans());
    draw_method(segment);
    replot();
}
void Drawer::draw_answer(std::optional<double> ans) {
    if (ans) {
        graph(1)->addData(*ans, f(*ans));
    }
}
void Drawer::draw_method(lab::Segment segment) {
    double a = segment.get_start(), b = segment.get_end();
    auto mid_opt = segment.get_mid();
    graph(2)->addData(a, f(a));
    graph(2)->addData(b, f(b));
    if (mid_opt) {
        addGraph();
        double mid = *mid_opt;
        graph(2)->setLineStyle(QCPGraph::LineStyle::lsNone);
        graph(2)->addData(mid, f(mid));
        graph(3)->setPen(QPen(Qt::red));
        replot_function_and_set(
            std::bind(&Parabola::q, Parabola(a, mid, b), std::placeholders::_1),
            -2, 3, 3);
    }
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
    yAxis->setRange(0, 10);
    recalc_segments();
    replot();
}
void Drawer::replot_function_and_set(const std::function<double(double)> &func,
                                     double start, double end,
                                     int graph_index) {
    double step = (end - start) / COUNT;
    std::vector<double> x, y;
    for (double point = start; point < end; point += step) {
        x.emplace_back(point);
        y.emplace_back(func(point));
    }
    graph(graph_index)
        ->setData(QVector<double>(x.begin(), x.end()),
                  QVector<double>(y.begin(), y.end()));
}
void Drawer::replot_f() {
    auto [start, end] = xAxis->range();
    replot_function_and_set(f, start, end, 0);
}
void Drawer::rescale_on_click(QCPAbstractPlottable *plottable, int,
                              QMouseEvent *) {
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
    connect(slider, &QSlider::valueChanged, this, &Slider::valueChanged);
}
void Slider::setup(int size) {
    slider->setSliderPosition(0);
    slider->setMaximum(size);
}