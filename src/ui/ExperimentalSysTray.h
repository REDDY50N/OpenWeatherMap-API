//
// Created by polar on 02.12.23.
//

#ifndef OWM_API_EXPERIMENTALSYSTRAY_H
#define OWM_API_EXPERIMENTALSYSTRAY_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

#include "SettingsWidget.h"

enum class WeatherStatus {
    sunny,
    rainy
};

enum class SysTrayTag {
    Settings,
    LoadDataBase,
};


class ExperimentalSysTray : public QDialog {
    Q_OBJECT

public:
    ExperimentalSysTray();

    void setVisible(bool visible) override;

    //connect(this, SIGNAL(weatherChanged(WeatherStatus)), this, SLOT(updateTemperatureToolTip));


protected:
    void closeEvent(QCloseEvent *event) override;


signals:
    void weatherChanged(WeatherStatus newStatus); // if weather status changed; change icon


public slots:

    /// just for testing (just show a Message Box)
    void showSettingsTest() {
        QMessageBox::information(nullptr, "Info", "TODO: Einstellungen anzeigen");
    }

    void showSettings() {
        settingsWidget->show();
    }


private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();

    // add owm fuctionality
    void updateWeatherAndTemperature();
    void updateWeatherIcon();
    void updateTemperatureToolTip();
    void setWeatherIcon(WeatherStatus status);


private:

    // TabBar
    void createTabBar();
    QTabWidget *tabWidget;

    /// create functions for SysTray
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();

    /// create widgets for SysTray
    QGroupBox *iconGroupBox;
    QLabel *iconLabel;
    QComboBox *iconComboBox;
    QCheckBox *showIconCheckBox;

    /// create message box for SysTray
    QGroupBox *messageGroupBox;
    QLabel *typeLabel;
    QLabel *durationLabel;
    QLabel *durationWarningLabel;
    QLabel *titleLabel;
    QLabel *bodyLabel;
    QComboBox *typeComboBox;
    QSpinBox *durationSpinBox;
    QLineEdit *titleEdit;
    QTextEdit *bodyEdit;
    QPushButton *showMessageButton;

    /// create actions for SysTray
    QAction *settingsAction;
    QAction *loadDataBaseAction;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    /// create icon and menu for SysTray
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    /// Settings Widgets (Testing: Just show a message dialog now)
    SettingsWidget* settingsWidget;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif

