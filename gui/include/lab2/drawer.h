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
        //        void draw(int iteration = 0);
        void set_method_2d(const QString &text);
        void set_method_1d(const QString &text);
        void set_func(const QString &text);

      signals:
        void method_changed(int size);

      private:
        const int COUNT             = 200;
        const int LINE_COUNT        = 5;
        double pepsilon             = 1e-4;
        lab2::Vector starting_point = lab2::Vector({10, 10});
        std::vector<lab2::Vector> optimize_points;
        std::vector<QCPCurve *> curves;
        lab2::NOptimizers method_2d = lab2::NOptimizers::GRADIENT_DESCENT;
        lab1::Optimizers method_1d  = lab1::Optimizers::BRENT;
        lab2::Function2D func       = lab2::Function2D::paraboloid_2d();

        static void rescale_on_click(QCPAbstractPlottable *plottable, int,
                                     QMouseEvent *);
        //        void replot_function_and_set(lab2::Function2D func, double
        //        start,
        //                                     double end, int graph_index);
        //        void draw_answer(std::optional<double> ans);
        //        void draw_method(lab1::Segment segment);
        //        void _draw(int iteration);
        void recalc_optimize_points();
        void replot_f();
        void change();
        void setup();
    };
}  // namespace gui2