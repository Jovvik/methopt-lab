#pragma once

#include "lab1/optimizer.h"
#include "lab2/function_2d.h"
#include "lab2/n_optimizer.h"
#include "qcustomplot.h"

namespace gui2 {
    class Drawer : public QCustomPlot {
        Q_OBJECT
      public:
        explicit Drawer(QWidget *parent = 0);
        void set_count_to_draw(int iteration = 0);
        void set_method_2d(const QString &text);
        void set_method_1d(const QString &text);
        void set_func(const QString &text);
        void set_pepsilon(const QString &text);
        void set_x(const QString &text);
        void set_y(const QString &text);
        void change_draw_level_lines();
        void change_draw_optimize_lines();
        void change();

      signals:
        void method_changed(int size);
        void x_y_changed(QString x_y_expression);
        void pepsilon_changed(QString epsilon_expression);

      private:
        const int COUNT             = 500;
        const int LINE_COUNT        = 5;
        const int LINE_STEP         = 5;
        const int FIRST_LINE        = 4;
        int optimize_points_to_draw = 0;
        double pepsilon             = 1e-2;
        bool draw_level_lines = true, draw_optimize_lines = true;
        lab2::Vector starting_point = lab2::Vector({5, 5});
        std::vector<lab2::Vector> optimize_points;
        std::vector<QCPCurve *> curves;
        lab2::NOptimizers method_2d = lab2::NOptimizers::GRADIENT_DESCENT;
        lab1::Optimizers method_1d  = lab1::Optimizers::BRENT;
        lab2::Function2D func = lab2::Function2D(&lab2::Functions::paraboloid);

        static void rescale_on_click(QCPAbstractPlottable *plottable, int,
                                     QMouseEvent *);
        void recalc_optimize_points();
        void before_replot();
        void replot_lines();
        void replot_f();
        void setup();
    };
}  // namespace gui2