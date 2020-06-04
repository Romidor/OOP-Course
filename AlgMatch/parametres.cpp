#include "parametres.h"
#include "ui_parametres.h"
#include "algomatch.h"
#include <fstream>

Parametres::Parametres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametres)
{
    ui->setupUi(this);
    this->setWindowTitle("Configuration");
    AlgoMatch::Configs &inst = AlgoMatch::Configs::GetInstance();
    ui->sizeOfArray_spinBox->setValue(inst.volume);
    ui->accuracy_slider->setValue(inst.accuracy);
    ui->lowBorder_spinBox->setValue(inst.lowerValue);
    ui->highBorder_spinBox->setValue(inst.highestValue);
    if (inst.algorithms[0] == '0')
        ui->linearSerarch_checkBox->setChecked(false);
    else ui->linearSerarch_checkBox->setChecked(true);
    if (inst.algorithms[1] == '0')
        ui->blockSearch_checkBox->setChecked(false);
    else ui->blockSearch_checkBox->setChecked(true);
    if (inst.algorithms[2] == '0')
        ui->binarySearch_checkBox->setChecked(false);
    else ui->binarySearch_checkBox->setChecked(true);
}

Parametres::~Parametres()
{
    delete ui;
}

void Parametres::on_saveParametresButton_clicked()
{
    AlgoMatch::Configs &configs = AlgoMatch::Configs::GetInstance();
    configs.volume = ui->sizeOfArray_spinBox->value();
    configs.accuracy = ui->accuracy_slider->value();
    configs.lowerValue = ui->lowBorder_spinBox->value();
    configs.highestValue = ui->highBorder_spinBox->value();
    std::string alg = "";
    if (ui->linearSerarch_checkBox->isChecked()) {
        alg += "1";
    }
    else {
        alg += "0";
    }
    if (ui->blockSearch_checkBox->isChecked()) {
        alg += "1";
    }
    else {
        alg += "0";
    }
    if (ui->binarySearch_checkBox->isChecked()) {
        alg += "1";
    }
    else {
        alg += "0";
    }
    configs.algorithms = alg;

    configs.Save();
}
