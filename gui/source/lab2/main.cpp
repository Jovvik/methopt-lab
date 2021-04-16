#include "lab2/drawer.h"
#include "lab2/main_window.h"
#include "lab2/slider.h"

using namespace gui2;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto v_box = new QVBoxLayout(this);
    auto h_box = new QHBoxLayout(this);

    auto graphic      = new Drawer(this);
    auto combo_box_2d = new QComboBox(this), combo_box_1d = new QComboBox(this),
         combo_box_f   = new QComboBox(this);
    auto slider        = new Slider(this);
    auto input         = new QLineEdit(this);
    auto label_epsilon = new QLabel(this);

    v_box->addWidget(graphic, 1);
    v_box->addLayout(h_box);
    v_box->addWidget(slider);
    h_box->addWidget(combo_box_2d, 0);
    h_box->addWidget(combo_box_1d, 0);
    h_box->addWidget(combo_box_f, 0);
    h_box->addWidget(input, 0);
    h_box->addWidget(label_epsilon, 0);
    h_box->addLayout(new QVBoxLayout(this), 1);

    combo_box_2d->setFixedWidth(200);
    combo_box_1d->setFixedWidth(200);
    combo_box_f->setFixedWidth(200);
    input->setFixedWidth(80);
    label_epsilon->setFixedWidth(80);

    for (auto [name, _] : lab2::n_optimizers_table) {
        combo_box_2d->addItem(QString::fromStdString(name));
    }
    for (auto [name, _] : lab1::optimizers_table) {
        if (name != "Параболы") {
            combo_box_1d->addItem(QString::fromStdString(name));
        }
    }
    for (auto [name, _] : lab2::functions_table) {
        combo_box_f->addItem(QString::fromStdString(name));
    }

    connect(graphic, SIGNAL(pepsilon_changed(double)), label_epsilon,
            SLOT(setNum(double)));
    connect(slider, &Slider::valueChanged, graphic, &Drawer::set_count_to_draw);
    connect(input, &QLineEdit::textChanged, graphic, &Drawer::set_pepsilon);
    connect(input, &QLineEdit::returnPressed, graphic, &Drawer::change);
    connect(input, &QLineEdit::returnPressed, input, &QLineEdit::clear);
    connect(combo_box_2d, &QComboBox::currentTextChanged, graphic,
            &Drawer::set_method_2d);
    connect(combo_box_1d, &QComboBox::currentTextChanged, graphic,
            &Drawer::set_method_1d);
    connect(combo_box_f, &QComboBox::currentTextChanged, graphic,
            &Drawer::set_func);
    connect(graphic, SIGNAL(method_changed(int)), slider, SLOT(setup(int)));
    graphic->set_method_2d(
        QString::fromStdString(lab2::n_optimizers_table.begin()->first));
    graphic->set_method_1d(
        QString::fromStdString(lab1::optimizers_table.begin()->first));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(500, 500);
    window.setWindowTitle("Оптимизация");
    window.show();

    return QApplication::exec();
}
