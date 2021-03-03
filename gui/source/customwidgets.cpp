#include "customwidgets.h"

#include "../../include/lab/segment.h"

Drawer::Drawer(QWidget *parent) : QCustomPlot(parent) {
    Drawer::setInteraction(QCP::iRangeDrag, true);
    Drawer::setInteraction(QCP::iRangeZoom, true);
    Drawer::setInteraction(QCP::iSelectPlottables, true);
    connect(this, &QCustomPlot::beforeReplot, this, &Drawer::replot_f);
    connect(this, &QCustomPlot::plottableClick, this,
            &Drawer::rescale_on_click);
    // TODO
    auto optimizer = lab::Dichotomy(f, 1e-4, -2, 3);
    optimizer.optimize();
    segments = optimizer.get_segments();
    //
    setup();
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
    if (method == "Дихотомия" || method == "Золотое сечение"
        || method == "Фиббоначи") {
        double a = segment.get_start();
        double b = segment.get_end();
        graph(2)->setPen(QPen(Qt::red));
        graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
        graph(2)->addData(a, f(a));
        graph(2)->addData(b, f(b));
    }
}
void Drawer::_draw(int iteration) {
    lab::Segment segment = segments[iteration];
    draw_answer(segment.get_ans());
    draw_method(segment);
    replot();
}
void Drawer::set_method(const QString &text) {
    method = text.toStdString();
    setup();
    emit method_changed(segments.size());
}

void Drawer::setup() {
    clearGraphs();
    addGraph();
    xAxis->setRange(-2, 3);
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