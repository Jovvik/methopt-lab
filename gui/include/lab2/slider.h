#pragma once

#include "qcustomplot.h"

namespace gui2 {
    class Slider : public QWidget {
        Q_OBJECT
      public:
        explicit Slider(QWidget *parent = 0);
      public slots:
        void setup(int size);
      signals:
        void valueChanged(int iteration);

      private:
        QSlider *slider;
        QLabel *label;
    };
}  // namespace gui2