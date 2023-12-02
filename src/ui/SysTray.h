//
// Created by polar on 02.12.23.
//

#ifndef OWM_API_SYSTRAY_H
#define OWM_API_SYSTRAY_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QInputDialog>
#include <QSettings>
#include <QDir>
#include <QtGlobal>
#include <qwindowdefs_win.h>
#include <QDebug>

static const char * start_icon[]={
        "16 16 9 1",
        ".	c None",
        "m	c #000000",
        "z	c #000090",
        "+	c #707070",
        "@	c #6090FF",
        "o	c #ADADAD",
        "$	c #5CFF0C",
        "%	c #CCDDFF",
        "&	c #DDFFCC",
        "................",
        ".....mmm........",
        "...mm$$$mmmmm...",
        "..moo$&$ooooom..",
        "..mom$$$mmmmom..",
        "..mommmmzz@mom..",
        "..momz@@%%%mom..",
        ".mmmmmmmmmmmmmm.",
        ".moooo+oo+oooom.",
        ".mmmmmmmmmmmmmm.",
        "..m++++++++++m..",
        "..m++++++++++m..",
        "..m++++++++++m..",
        "...mmmmmmmmmm...",
        "................",
        "................"
};




class SysShell : QObject {
    Q_OBJECT
private:
    SysShell(); // no instantiation outside of this class
public:
    SysShell(const SysShell&) = delete;
    SysShell& operator=(const SysShell &) = delete;
    SysShell(SysShell &&) = delete;
    SysShell & operator=(SysShell &&) = delete;

    // the singleton instance
    static auto& getInstance(){
        static SysShell sysShell;
        return sysShell;
    }

public slots:
    void powerOff() { qDebug() << "Poweroff"; };
};

class UsbStickNotifier {

};


class SysTray : QApplication {
    Q_OBJECT

public:

    SysTray(int &argc, char **argv);
    int runLoop();


private slots:
    void openCurrentInBrowser() { };
    void loadDataBase() { };


signals:
    void dataBaseLoaded( const QString& FileName );
};





#endif //OWM_API_SYSTRAY_H
