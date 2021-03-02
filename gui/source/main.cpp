#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QFile>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPen>
#include <QPushButton>
#include <QSizePolicy>
#include <QSlider>
#include <QSpinBox>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <iostream>

#include "lab/dichotomy.h"
#include "qcustomplot.h"

class Drawer : public QCustomPlot {
public:
    Drawer(QWidget *parent = 0)
            : QCustomPlot(parent) {
        Drawer::setInteraction(QCP::iRangeDrag, true);
        Drawer::setInteraction(QCP::iRangeZoom, true);
        Drawer::setInteraction(QCP::iSelectPlottables, true);
        connect(this, &QCustomPlot::beforeReplot, this, &Drawer::replot_f);
        connect(this, &QCustomPlot::plottableClick, this, &Drawer::rescale_on_click);
        auto optimizer = lab::Dichotomy(1e-5);
        optimizer.optimize(f, 1e-4, -2, 3);
        segments = optimizer.get_segments();
        draw();
        rescaleAxes();
    }

    void draw(int iteration = 0) {
        clearGraphs();
        addGraph();
        addGraph();
        if (iteration == 0) {
            draw_f(-2, 3);
            return;
        }
        auto[a, b, _] = segments[iteration - 1];
        graph(0)->setPen(QPen(Qt::red));
        graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        graph(0)->addData(a, f(a));
        graph(0)->addData(b, f(b));
        replot();
    }

    std::vector <lab::Segment> segments;

private:

    void rescale_on_click(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event) {
        plottable->rescaleAxes();
        std::cout << 1;
    }

    void replot_f() {
        auto range = xAxis->range();
        draw_f(range.lower, range.upper);
    }

    void draw_f(double a, double b) {
        std::vector<double> x, y;
        points_to_x_y(get_f_points(a, b), x, y);
        graph(1)->setPen(QPen(Qt::blue));
        graph(1)->setData(QVector<double>::fromStdVector(x),
                          QVector<double>::fromStdVector(y));
    }

    static double f(double x) { return x * x; }

    std::vector <std::pair<double, double>> get_f_points(double a, double b,
                                                         int count = 1000) {
        std::vector <std::pair<double, double>> points;
        double step = (b - a) / count;
        for (double x = a; x < b; x += step) {
            points.emplace_back(x, f(x));
        }
        return points;
    }

    void points_to_x_y(std::vector <std::pair<double, double>> points,
                       std::vector<double> &x, std::vector<double> &y) {
        for (auto point : points) {
            x.emplace_back(point.first);
            y.emplace_back(point.second);
        }
    }
};

class Slider : public QWidget {
public:
    Slider(QWidget *parent = 0)
            : QWidget(parent),
              slider(new QSlider(Qt::Horizontal, this)),
              label(new QLabel("0", this)) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(slider);
        layout->addWidget(label);
        connect(slider, &QSlider::valueChanged, label,
                static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    }

    QSlider *slider;
private:
    QLabel *label;
};

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent = 0) : QWidget(parent) {
        auto v_box = new QVBoxLayout(this);
        auto h_box = new QHBoxLayout(this);

        auto graphic = new Drawer(this);
        auto combo_box = new QComboBox(this);
        auto slider = new Slider(this);

        v_box->addWidget(graphic, 1);
        v_box->addLayout(h_box);
        h_box->addWidget(combo_box);
        h_box->addWidget(slider);

        QStringList optimizators
                = {"Дихотомия", "Золотое сечение", "Фиббоначи", "Параболы", "Брент"};
        combo_box->addItems(optimizators);
        combo_box->setFixedWidth(200);
        slider->slider->setMaximum(graphic->segments.size());
        connect(slider->slider, &QSlider::valueChanged, graphic, &Drawer::draw);
//        slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        connect(slider, &QSlider::valueChanged, label,
//                static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
//        connect(slider, &QSlider::valueChanged, label, &);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile styles("build/assets/styles.css");
    styles.open(QIODevice::ReadOnly);
    QTextStream textStream(&styles);
    QString styleSheet = textStream.readAll();
    styles.close();
    app.setStyleSheet(styleSheet);

    MainWindow window;
    window.resize(500, 500);
    window.setWindowTitle("SOSI");
    window.setWindowIcon(QIcon("build/assets/bin.png"));
    window.show();

    return app.exec();
}