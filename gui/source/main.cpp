#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDir>
#include <QSizePolicy>
#include <QSlider>
#include <QLabel>
#include <QVector>
#include <QPen>
#include "qcustomplot.h"
#include "lab/dichotomy.h"

class Drawer : public QWidget {
public:
    Drawer(QWidget *parent = 0) {
        plot_setup();
        auto optimizer = lab::Dichotomy(1e-5);
        optimizer.optimize(f, 1e-4, -2, 3);
        segments = optimizer.get_segments();
    }

    void draw(int iteration) {
        auto[a, b, points] = segments[iteration];
        std::vector<double> x, y, x_f, y_f;
        points_to_x_y(points, x, y);
        points_to_x_y(get_f_points(a, b), x_f, y_f);
        plot->addGraph();
        plot->graph(0)->setPen(QPen(Qt::blue));
        plot->graph(0)->setData(QVector<double>::fromStdVector(x_f), QVector<double>::fromStdVector(y_f));
        plot->addGraph();
        plot->graph(1)->setPen(QPen(Qt::red));
        plot->graph(1)->setData(QVector<double>::fromStdVector(x), QVector<double>::fromStdVector(y));
        plot->graph(1)->rescaleAxes();
    }

private:
    QCustomPlot *plot;

    void plot_setup(){
        plot = new QCustomPlot(this);
        auto grid = new QGridLayout(this);
        grid->addWidget(plot);
        plot->setInteraction(QCP::iRangeDrag, true);
        plot->setInteraction(QCP::iRangeZoom, true);
    }

    static double f(double x) {
        return x * x;
    }

    std::vector <std::pair<double, double>> get_f_points(double a, double b, int count = 30) {
        std::vector <std::pair<double, double>> points;
        double step = (b - a) / count;
        for (double x = a; x < b; x += step) {
            points.emplace_back(x, f(x));
        }
        return points;
    }

    void points_to_x_y(std::vector <std::pair<double, double>> points, std::vector<double> &x, std::vector<double> &y) {
        for (auto point:points) {
            x.push_back(point.first);
            y.push_back(point.second);
        }
    }

    std::vector <lab::Segment> segments;
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
    QStringList optimizators = {"Дихотомия", "Золотое сечение", "Фиббоначи", "Параболы", "Брент"};
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