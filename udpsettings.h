#ifndef UDPSETTINGS_H
#define UDPSETTINGS_H

#include <QDialog>
#include "udp_updater.h"

namespace Ui {
class UDPSettings;
}

class UDPSettings : public QDialog
{
    Q_OBJECT

public:
    explicit UDPSettings(QWidget *parent = nullptr);
    ~UDPSettings();

    UDPUpdater *updater;

private slots:
    void on_btnApply_clicked();
    void on_btnCloseWindow_clicked();

private:
    Ui::UDPSettings *ui;
};

#endif // UDPSETTINGS_H
