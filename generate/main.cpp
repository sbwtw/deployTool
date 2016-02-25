
#include "generate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Generate w;
    w.show();

    return a.exec();
}
