//
// Created by polar on 02.12.23.
//

#include "ExperimentalSysTray.h"

#ifndef QT_NO_SYSTEMTRAYICON
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>


ExperimentalSysTray::ExperimentalSysTray()
{
    createIconGroupBox();
    createMessageGroupBox();

    iconLabel->setMinimumWidth(durationLabel->sizeHint().width());

    createActions();

    createTrayIcon();

    createTabBar();

    connect(showMessageButton, &QAbstractButton::clicked, this, &ExperimentalSysTray::showMessage);
    connect(showIconCheckBox, &QAbstractButton::toggled, trayIcon, &QSystemTrayIcon::setVisible);
    connect(iconComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ExperimentalSysTray::setIcon);
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &ExperimentalSysTray::messageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &ExperimentalSysTray::iconActivated);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);

    iconComboBox->setCurrentIndex(1);
    trayIcon->show();

    setWindowTitle(tr("Open Weather Map"));
    resize(600, 480);
}
//! [0]

//! [1]
void ExperimentalSysTray::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}
//! [1]

//! [2]
void ExperimentalSysTray::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_MACOS
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}
//! [2]

//! [3]
void ExperimentalSysTray::setIcon(int index)
{
    QIcon icon = iconComboBox->itemIcon(index);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip(iconComboBox->itemText(index));
}
//! [3]

//! [4]
void ExperimentalSysTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
            break;
        case QSystemTrayIcon::MiddleClick:
            showMessage();
            break;
        default:
            ;
    }
}
//! [4]

//! [5]
void ExperimentalSysTray::showMessage()
{
    showIconCheckBox->setChecked(true);
    int selectedIcon = typeComboBox->itemData(typeComboBox->currentIndex()).toInt();
    QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(selectedIcon);

    if (selectedIcon == -1) { // custom icon
        QIcon icon(iconComboBox->itemIcon(iconComboBox->currentIndex()));
        trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), icon,
                              durationSpinBox->value() * 1000);
    } else {
        trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), msgIcon,
                              durationSpinBox->value() * 1000);
    }
}
//! [5]

//! [6]
void ExperimentalSysTray::messageClicked()
{
    QMessageBox::information(nullptr, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}
//! [6]

void ExperimentalSysTray::createIconGroupBox()
{
    iconGroupBox = new QGroupBox(tr("Weather  createIconGroupBox"));

    iconLabel = new QLabel("Icon:");

    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/heart.png"), tr("Heart"));

    iconComboBox->addItem(QIcon(":/icons/rain.svg"), tr("Rainy"));
    iconComboBox->addItem(QIcon(":/icons/sunny.svg"), tr("Sunny"));

    showIconCheckBox = new QCheckBox(tr("Show icon"));
    showIconCheckBox->setChecked(true);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);
}

void ExperimentalSysTray::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox(tr("Balloon Message"));

    typeLabel = new QLabel(tr("Type:"));

    typeComboBox = new QComboBox;
    typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
    typeComboBox->addItem(style()->standardIcon(
                                  QStyle::SP_MessageBoxInformation), tr("Information"),
                          QSystemTrayIcon::Information);
    typeComboBox->addItem(style()->standardIcon(
                                  QStyle::SP_MessageBoxWarning), tr("Warning"),
                          QSystemTrayIcon::Warning);
    typeComboBox->addItem(style()->standardIcon(
                                  QStyle::SP_MessageBoxCritical), tr("Critical"),
                          QSystemTrayIcon::Critical);
    typeComboBox->addItem(QIcon(), tr("Custom icon"),
                          -1);
    typeComboBox->setCurrentIndex(1);

    durationLabel = new QLabel(tr("Duration:"));

    durationSpinBox = new QSpinBox;
    durationSpinBox->setRange(5, 60);
    durationSpinBox->setSuffix(" s");
    durationSpinBox->setValue(15);

    durationWarningLabel = new QLabel(tr("(some systems might ignore this "
                                         "hint)"));
    durationWarningLabel->setIndent(10);

    titleLabel = new QLabel(tr("Title:"));

    titleEdit = new QLineEdit(tr("Cannot connect to network"));

    bodyLabel = new QLabel(tr("Body:"));

    bodyEdit = new QTextEdit;
    bodyEdit->setPlainText(tr("Don't believe me. Honestly, I don't have a "
                              "clue.\nClick this balloon for details."));

    showMessageButton = new QPushButton(tr("Show Message"));
    showMessageButton->setDefault(true);

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(typeLabel, 0, 0);
    messageLayout->addWidget(typeComboBox, 0, 1, 1, 2);
    messageLayout->addWidget(durationLabel, 1, 0);
    messageLayout->addWidget(durationSpinBox, 1, 1);
    messageLayout->addWidget(durationWarningLabel, 1, 2, 1, 3);
    messageLayout->addWidget(titleLabel, 2, 0);
    messageLayout->addWidget(titleEdit, 2, 1, 1, 4);
    messageLayout->addWidget(bodyLabel, 3, 0);
    messageLayout->addWidget(bodyEdit, 3, 1, 2, 4);
    messageLayout->addWidget(showMessageButton, 5, 4);
    messageLayout->setColumnStretch(3, 1);
    messageLayout->setRowStretch(4, 1);
    messageGroupBox->setLayout(messageLayout);
}

/// create Action and Signal/Slot connection
void ExperimentalSysTray::createActions()
{
    settingsAction = new QAction("Settings", this);
    //connect(settingsAction, &QAction::triggered, this, SLOT(showSettings()) ); ///  TODO: show settings window / tab
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));

    loadDataBaseAction = new QAction(tr("Data"), this);
    connect(loadDataBaseAction, &QAction::triggered, this, &QWidget::hide);

    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

/// Create Actions for the SysTray (Right Click)
void ExperimentalSysTray::createTrayIcon()
{
    trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(settingsAction);
    trayIconMenu->addAction(loadDataBaseAction);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void ExperimentalSysTray::updateTemperatureToolTip() {
    double temp = 20.4;
}

void ExperimentalSysTray::updateWeatherIcon() {

    enum class weather_status {
        sunny,
        rainy
    };

    weather_status current_weather = weather_status::sunny;

    switch (current_weather) {
        case weather_status::sunny:
            qDebug() << "Sunny";
            break;
        case weather_status::rainy:
            qDebug() << "Sunny";
            break;
        default:
            qDebug() << "unkown";
            break;
    }
}

void ExperimentalSysTray::setWeatherIcon(WeatherStatus status) {

    QIcon icon;
    switch (status) {
        case WeatherStatus::sunny:
            icon.addFile(":/icons/rain.svg"); // Pfade entsprechend anpassen
            break;
        case WeatherStatus::rainy:
            icon.addFile(":/icons/rain.svg");
            break;
            // Weitere Wetterzustände hinzufügen, falls benötigt
        default:
            icon.addFile(":/icons/sunny.svg"); // Standard-Icon
            break;
    }
    trayIcon->setIcon(icon);

}

//========================================
// WEATHER TEMP DISPLAY ()
//========================================
void ExperimentalSysTray::updateWeatherAndTemperature() {
    updateTemperatureToolTip();
    updateWeatherIcon();
}


//========================================
// TAB-BAR
//========================================
void ExperimentalSysTray::createTabBar() {
// Erstelle eine TabBar und füge Tabs hinzu
    tabWidget = new QTabWidget(this);

    QWidget* tabDashboard = new QWidget();
    tabDashboard->setLayout(new QVBoxLayout());
    tabDashboard->layout()->addWidget(new QLabel("Dashboard Tab Content"));
    tabWidget->addTab(tabDashboard, "Dashboard");

    QWidget* tabDataBase = new QWidget();
    tabDataBase->setLayout(new QVBoxLayout());
    tabDataBase->layout()->addWidget(new QLabel("Dashboard Tab Content"));
    tabWidget->addTab(tabDataBase, "Dashboard");

    QWidget* tabSettings = new QWidget();
    tabSettings->setLayout(new QVBoxLayout());
    tabSettings->layout()->addWidget(new QLabel("Settings Tab Content"));
    tabWidget->addTab(tabSettings, "Settings");

    // Füge die TabBar zum Layout hinzu
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

#endif