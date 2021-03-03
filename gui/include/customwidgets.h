#ifndef LAB_CUSTOMWIDGETS_H
#define LAB_CUSTOMWIDGETS_H

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

#include "lab/dichotomy.h"
#include "qcustomplot.h"

class Drawer : public QCustomPlot {
    Q_OBJECT
  public:
    Drawer(QWidget *parent = 0);
    void draw(int iteration = 0);
    void set_method(const QString &text);
    std::vector<lab::Segment> segments;

  signals:
    void method_changed(int size);

  private:
    int COUNT = 777;
    void setup();
    void clear();
    void _draw(int iteration);
    void draw_answer(std::optional<double> ans);
    void draw_method(lab::Segment segment);
    void rescale_on_click(QCPAbstractPlottable *plottable, int _,
                          QMouseEvent *__);
    void replot_f();
    static double f(double x) { return x * x; }
    std::string method = "Дихотомия";
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

#endif  // LAB_CUSTOMWIDGETS_H