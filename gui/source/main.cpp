#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QFrame>
#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDir>
#include <QSizePolicy>
#include <QSlider>
#include <QLabel>

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent = 0);
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    auto main_h_box = new QHBoxLayout(this);
    auto left_part = new QFrame(this);
    auto right_part = new QFrame(this);
    left_part->setMinimumWidth(200);
    main_h_box->addWidget(left_part, 1);
    main_h_box->addWidget(right_part);

    auto left_part_v_box = new QVBoxLayout(left_part);
    auto graphic = new QFrame(left_part);
    graphic->setObjectName("graphicFrame");
    left_part_v_box->addWidget(graphic, 1);
    auto left_part_h_box = new QHBoxLayout(left_part);
    auto slider = new QSlider(Qt::Horizontal, left_part);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    left_part_h_box->addWidget(slider);
    auto label = new QLabel("0", left_part);
    left_part_h_box->addWidget(label);
    left_part_v_box->addLayout(left_part_h_box);

    QStringList optimizators = {"hui", "mocha", "govno"};
    auto right_combo_box = new QComboBox(right_part);
    right_combo_box->addItems(optimizators);
    right_combo_box->setFixedWidth(200);
    auto right_part_v_box = new QVBoxLayout(right_part);
    right_part_v_box->addWidget(right_combo_box);
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