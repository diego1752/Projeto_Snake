#include <QApplication>
#include "windows.h"

int main(int argc,char **argv){


    QApplication app(argc,argv);
    windows win;
    win.show();
    return app.exec();
}
