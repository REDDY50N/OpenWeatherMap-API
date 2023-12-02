//
// Created by polar on 02.12.23.
//

#include "SysTray.h"

SysTray::SysTray(int &argc, char **argv) : QApplication(argc, argv) {
    qDebug() << "SysTray was created!";
}


int SysTray::runLoop() {
    qDebug() << "Run loop";
    QSystemTrayIcon ico( QPixmap(start_icon), this );
    QMenu menu( nullptr );

    QAction *action;

    action = menu.addAction("Open Current in Browser" );
    connect(action, SIGNAL(triggered()), this, SLOT(openCurrentInBrowser()) );

    action = menu.addAction("Load Database" );
    connect(action, SIGNAL(triggered()), this, SLOT(loadDataBase()) );

    ico.setContextMenu( &menu );
    ico.show();

    setQuitOnLastWindowClosed( false );

    return true;
}





