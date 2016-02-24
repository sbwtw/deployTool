#include "deploy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Deploy w;
    w.show();

    return a.exec();
}
