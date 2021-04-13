#pragma once

#include "lab1/optimizer.h"
#include "qcustomplot.h"

class Drawer : public QCustomPlot {
    Q_OBJECT
  public:
    Drawer(QWidget *parent = 0);
    void draw(int iteration = 0);
    void set_method(const QString &text);

  signals:
    void method_changed(int size);

  private:
    const int COUNT = 777;
    lab1::Optimizers method;
    std::vector<lab1::Segment> segments;

    void rescale_on_click(QCPAbstractPlottable *plottable, int, QMouseEvent *);
    void replot_function_and_set(const std::function<double(double)> &func,
                                 double start, double end, int graph_index);
    void draw_answer(std::optional<double> ans);
    void draw_method(lab1::Segment segment);
    void _draw(int iteration);
    void recalc_segments();
    void replot_f();
    void setup();
    void clear();
};

class Slider : public QWidget {
    Q_OBJECT
  public:
    Slider(QWidget *parent = 0);
  public slots:
    void setup(int size);
  signals:
    void valueChanged(int iteration);

  private:
    QSlider *slider;
    QLabel *label;
};

class MainWindow : public QWidget {
  public:
    MainWindow(QWidget *parent = 0);
};
