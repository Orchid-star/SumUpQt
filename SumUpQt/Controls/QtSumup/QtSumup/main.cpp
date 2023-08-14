#include "stdafx.h"
#include "qt_sumup.h"
#include "main_window.h"
#include "ch_main_window.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QScreen>
#include <QTextCodec>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_sumup w;
    w.showMaximized();
    return a.exec();
}
