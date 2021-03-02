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

class Drawer : public QWidget {
  public:
    Drawer(QWidget *parent = 0) {
        plot_setup();
        auto optimizer = lab::Dichotomy(1e-5);
        optimizer.optimize(f, 1e-4, -2, 3);
        segments = optimizer.get_segments();
    }

    void draw(int iteration) {
        auto [a, b, _] = segments[iteration];
        std::vector<double> f_x, f_y;
        points_to_x_y(get_f_points(-2, 3), f_x, f_y);
        plot->addGraph();
        plot->graph(0)->setPen(QPen(Qt::blue));
        plot->graph(0)->setData(QVector<double>(f_x.begin(), f_x.end()),
                                QVector<double>(f_y.begin(), f_y.end()));
        plot->addGraph();
        plot->graph(1)->setPen(QPen(Qt::red));
        plot->graph(1)->setData({a, b}, {f(a), f(b)});
        plot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
        plot->graph(1)->addData(a, f(a));
        plot->graph(1)->addData(b, f(b));
        plot->rescaleAxes();
    }

  private:
    QCustomPlot *plot;

    void plot_setup() {
        plot = new QCustomPlot(this);
        auto grid = new QGridLayout(this);
        grid->addWidget(plot);
        plot->setInteraction(QCP::iRangeDrag, true);
        plot->setInteraction(QCP::iRangeZoom, true);
    }

    static double f(double x) { return x * x; }

    std::vector<std::pair<double, double>> get_f_points(double a, double b,
                                                        int count = 1000) {
        std::vector<std::pair<double, double>> points;
        double step = (b - a) / count;
        for (double x = a; x < b; x += step) {
            points.emplace_back(x, f(x));
        }
        return points;
    }

    void points_to_x_y(std::vector<std::pair<double, double>> points,
                       std::vector<double> &x, std::vector<double> &y) {
        for (auto point : points) {
            x.push_back(point.first);
            y.push_back(point.second);
        }
    }

    std::vector<lab::Segment> segments;
};

class MainWindow : public QWidget {
  public:
    MainWindow(QWidget *parent = 0);
};

double f(double x) { return x * x; }

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto v_box = new QVBoxLayout(this);
    auto h_box = new QHBoxLayout(this);

    auto graphic = new Drawer(this);
    auto combo_box = new QComboBox(this);
    auto slider = new QSlider(Qt::Horizontal, this);
    auto label = new QLabel("0", this);

    v_box->addWidget(graphic, 1);
    v_box->addLayout(h_box);
    h_box->addWidget(combo_box);
    h_box->addWidget(slider);
    h_box->addWidget(label);

    graphic->draw(10);
    graphic->setStyleSheet("background: yellow");
    QStringList optimizators
        = {"Дихотомия", "Золотое сечение", "Фиббоначи", "Параболы", "Брент"};
    combo_box->addItems(optimizators);
    combo_box->setFixedWidth(200);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(slider, &QSlider::valueChanged, label,
            static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
}

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