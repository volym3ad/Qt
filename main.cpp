#include <QApplication>

#include "mwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MWindow mWindow;
    mWindow.show();

    return app.exec();
}


