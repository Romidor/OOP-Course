#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "info.h"
#include "parametres.h"
#include "algomatch.h"
#include "results.h"
#include <vector>
#include <chrono>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("AlgoMatch");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_infoButton_clicked()
{
    Info info;
    info.setModal(true);
    info.exec();
}

void MainWindow::on_parametresButton_clicked()
{
    Parametres params;
    params.setModal(true);
    params.exec();
}

void MainWindow::on_startButton_clicked()
{
    Results results;
    results.setModal(true);
    results.exec();
}
