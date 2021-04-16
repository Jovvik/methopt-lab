#include "lab2/drawer.h"
#include "lab2/main_window.h"
#include "lab2/slider.h"

using namespace gui2;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto v_box       = new QVBoxLayout(this);
    auto v_box_check = new QVBoxLayout(this);
    auto h_box       = new QHBoxLayout(this);
    auto h_box_check = new QHBoxLayout(this);

    auto graphic      = new Drawer(this);
    auto combo_box_2d = new QComboBox(this), combo_box_1d = new QComboBox(this),
         combo_box_f              = new QComboBox(this);
    auto check_box_level_lines    = new QCheckBox("Hide level lines", this),
         check_box_optimize_lines = new QCheckBox("Hide opt lines", this);
    auto slider                   = new Slider(this);
    auto input_epsilon            = new QLineEdit(this);
    auto input_x                  = new QLineEdit(this);
    auto input_y                  = new QLineEdit(this);
    auto label_epsilon            = new QLabel(this);
    auto label_x_y                = new QLabel(this);

    v_box->addLayout(h_box_check);
    v_box->addLayout(h_box);
    v_box->addWidget(slider);
    h_box_check->addWidget(graphic);
    h_box_check->addLayout(v_box_check);
    h_box->addWidget(combo_box_2d, 0);
    h_box->addWidget(combo_box_1d, 0);
    h_box->addWidget(combo_box_f, 0);
    h_box->addWidget(input_epsilon, 0);
    h_box->addWidget(label_epsilon, 0);
    h_box->addWidget(input_x, 0);
    h_box->addWidget(input_y, 0);
    h_box->addWidget(label_x_y, 0);
    h_box->addLayout(new QVBoxLayout(this), 1);
    v_box_check->setSpacing(20);
    v_box_check->addWidget(check_box_level_lines, 0);
    v_box_check->addWidget(check_box_optimize_lines, 0);
    v_box_check->addLayout(new QHBoxLayout(this), 1);

    graphic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    combo_box_2d->setFixedWidth(190);
    combo_box_1d->setFixedWidth(140);
    combo_box_f->setFixedWidth(210);
    input_epsilon->setFixedWidth(50);
    input_x->setFixedWidth(50);
    input_y->setFixedWidth(50);

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

    connect(check_box_level_lines, &QCheckBox::stateChanged, graphic,
            &Drawer::change_draw_level_lines);
    connect(check_box_optimize_lines, &QCheckBox::stateChanged, graphic,
            &Drawer::change_draw_optimize_lines);
    connect(graphic, SIGNAL(pepsilon_changed(QString)), label_epsilon,
            SLOT(setText(const QString &)));
    connect(graphic, SIGNAL(x_y_changed(QString)), label_x_y,
            SLOT(setText(const QString &)));
    connect(slider, &Slider::valueChanged, graphic, &Drawer::set_count_to_draw);
    connect(input_epsilon, &QLineEdit::textChanged, graphic,
            &Drawer::set_pepsilon);
    connect(input_epsilon, &QLineEdit::returnPressed, graphic, &Drawer::change);
    connect(input_epsilon, &QLineEdit::returnPressed, input_epsilon,
            &QLineEdit::clear);
    connect(input_x, &QLineEdit::textChanged, graphic, &Drawer::set_x);
    connect(input_x, &QLineEdit::returnPressed, graphic, &Drawer::change);
    connect(input_x, &QLineEdit::returnPressed, input_x, &QLineEdit::clear);
    connect(input_y, &QLineEdit::textChanged, graphic, &Drawer::set_y);
    connect(input_y, &QLineEdit::returnPressed, graphic, &Drawer::change);
    connect(input_y, &QLineEdit::returnPressed, input_y, &QLineEdit::clear);
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
