#pragma once

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
#include <cmath>

#include "lab/dichotomy.h"
#include "lab/optimizer.h"
#include "qcustomplot.h"

class Drawer : public QCustomPlot {
    Q_OBJECT
  public:
    Drawer(QWidget *parent = 0);
    void draw(int iteration = 0);
    void set_method(const QString &text);
    std::vector<lab::Segment> segments;
    static double square(double x) { return x * x; };
    static double my_sin(double x) { return sin(x); };
    static double f(double x) { return x * x + exp(-0.35 * x); };

  signals:
    void method_changed(int size);

  private:
    int COUNT = 777;
    void setup();
    void clear();
    void _draw(int iteration);
    void recalc_segments();
    void draw_answer(std::optional<double> ans);
    void draw_method(lab::Segment segment);
    void rescale_on_click(QCPAbstractPlottable *plottable, int _,
                          QMouseEvent *__);
    void replot_f();
    lab::Optimizers method = lab::Optimizers::DICHOTOMY;
};

class Slider : public QWidget {
    Q_OBJECT
  public:
    Slider(QWidget *parent = 0);
    QSlider *slider;
  public slots:
    void setup(int size);

  private:
    QLabel *label;
};

class MainWindow : public QWidget {
  public:
    MainWindow(QWidget *parent = 0);
};
