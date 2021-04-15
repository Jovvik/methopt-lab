//#include "lab1/customwidgets.h"
//
//using namespace gui1;
//
//MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
//    auto v_box = new QVBoxLayout(this);
//    auto h_box = new QHBoxLayout(this);
//
//    auto graphic = new Drawer(this);
//    auto combo_box = new QComboBox(this);
//    auto slider = new Slider(this);
//
//    v_box->addWidget(graphic, 1);
//    v_box->addLayout(h_box);
//    h_box->addWidget(combo_box);
//    h_box->addWidget(slider);
//
//    for (auto [name, enum_name] : lab1::optimizers_table) {
//        combo_box->addItem(QString::fromStdString(name));
//    }
//    combo_box->setFixedWidth(200);
//    connect(slider, &Slider::valueChanged, graphic, &Drawer::draw);
//    connect(graphic, SIGNAL(method_changed(int)), slider, SLOT(setup(int)));
//    connect(combo_box, &QComboBox::currentTextChanged, graphic,
//            &Drawer::set_method);
//    graphic->set_method(
//        QString::fromStdString(lab1::optimizers_table.begin()->first));
//}
//
//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//
//    MainWindow window;
//    window.resize(500, 500);
//    window.setWindowTitle("Оптимизация");
//    window.show();
//
//    return app.exec();
//}
