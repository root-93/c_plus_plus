#include "trayicon.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QObject::tr("main", "Tray Icon"));
    a.setQuitOnLastWindowClosed(false);
    TrayIcon w;
    w.show();
    return a.exec();
}
