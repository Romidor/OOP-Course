#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    this->setWindowTitle("Information");
}

Info::~Info()
{
    delete ui;
}
