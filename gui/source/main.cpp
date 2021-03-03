#include "customwidgets.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto v_box = new QVBoxLayout(this);
    auto h_box = new QHBoxLayout(this);

    auto graphic = new Drawer(this);
    auto combo_box = new QComboBox(this);
    auto slider = new Slider(this);

    v_box->addWidget(graphic, 1);
    v_box->addLayout(h_box);
    h_box->addWidget(combo_box);
    h_box->addWidget(slider);

    for (auto [name, enum_name] : lab::optimizers_table) {
        combo_box->addItem(QString::fromStdString(name));
    }
    combo_box->setFixedWidth(200);
    connect(slider->slider, &QSlider::valueChanged, graphic, &Drawer::draw);
    connect(combo_box, &QComboBox::currentTextChanged, graphic,
            &Drawer::set_method);
    connect(graphic, SIGNAL(method_changed(int)), slider, SLOT(setup(int)));
    graphic->set_method(QString::fromStdString("Брент"));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile styles("build/assets/styles.css");
    styles.open(QIODevice::ReadOnly);
    QTextStream textStream(&styles);
    QString styleSheet = textStream.readAll();
    styles.close();
    app.setStyleSheet(styleSheet);

    MainWindow window;
    window.resize(500, 500);
    window.setWindowTitle("SOSI");
    window.setWindowIcon(QIcon("build/assets/bin.png"));
    window.show();

    return app.exec();
}