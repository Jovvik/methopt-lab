#include "lab2/drawer.h"
#include "lab2/main_window.h"
#include "lab2/slider.h"

using namespace gui2;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto v_box = new QVBoxLayout(this);
    auto h_box = new QHBoxLayout(this);

    auto graphic              = new Drawer(this);
    auto combo_box_2d_methods = new QComboBox(this),
         combo_box_1d_methods = new QComboBox(this),
         combo_box_f_choose   = new QComboBox(this);
    auto slider               = new Slider(this);

    v_box->addWidget(graphic, 1);
    v_box->addLayout(h_box);
    v_box->addWidget(slider);
    h_box->addWidget(combo_box_2d_methods, 0);
    h_box->addWidget(combo_box_1d_methods, 0);
    h_box->addWidget(combo_box_f_choose, 0);
    h_box->addLayout(new QVBoxLayout(this), 1);

    combo_box_2d_methods->setFixedWidth(200);
    combo_box_1d_methods->setFixedWidth(200);
    combo_box_f_choose->setFixedWidth(200);

    combo_box_2d_methods->addItem(QString::fromStdString("Градиентный спуск"));
    combo_box_2d_methods->addItem(QString::fromStdString("Наискорейший спуск"));
    combo_box_2d_methods->addItem(
        QString::fromStdString("Сопряжённые градиенты"));

    //    connect(slider, &Slider::valueChanged, graphic, &Drawer::draw);
    //    connect(graphic, SIGNAL(method_changed(int)), slider,
    //    SLOT(setup(int))); connect(combo_box, &QComboBox::currentTextChanged,
    //    graphic,
    //            &Drawer::set_method);
    graphic->set_method_2d(
        QString::fromStdString(lab2::n_optimizers_table.begin()->first));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(500, 500);
    window.setWindowTitle("Оптимизация");
    window.show();

    return QApplication::exec();
}
