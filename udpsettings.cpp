#include "udpsettings.h"
#include "ui_udpsettings.h"

UDPSettings::UDPSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDPSettings)
{
    ui->setupUi(this);

    setWindowTitle("UDP Settings");
}

UDPSettings::~UDPSettings()
{
    delete ui;
}

void UDPSettings::on_btnApply_clicked()
{
    updater->changeIPandPort(ui->leIPAddress->text().toStdString(), ui->lePort->text().toStdString());
    ui->lblIPSet->setText(ui->leIPAddress->text());
    ui->lblPortSet->setText(ui->lePort->text());
    ui->leIPAddress->setText("");
    ui->lePort->setText("");
}


void UDPSettings::on_btnCloseWindow_clicked()
{
    this->hide();
}

