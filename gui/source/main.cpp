#include <QApplication>
#include <QWidget>
#include <QIcon>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QWidget window;

    window.resize(500, 500);
    window.setWindowTitle("SOSI");
    window.setWindowIcon(QIcon("bin.png"));
    window.show();

    return app.exec();
}