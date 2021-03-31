#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("D:/qt/course work/coursework/Icons/paint.png"));
    MainWindow w;
    w.setWindowTitle("Course work");
    w.show();
    return app.exec();
}
