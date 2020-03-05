#include "noisegenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NoiseGenerator gui;
    gui.show();

    return a.exec();
}
