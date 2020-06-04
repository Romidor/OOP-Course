#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>
#include "algomatch.h"

namespace Ui {
class Results;
}

class Results : public QDialog
{
    Q_OBJECT

public:
    explicit Results(QWidget *parent = nullptr);
    ~Results();

private:
    Ui::Results *ui;
    void Calculate();

    AlgoMatch::AlgoMatchContainer container;
};

#endif // RESULTS_H
