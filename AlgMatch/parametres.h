#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QDialog>

namespace Ui {
class Parametres;
}

class Parametres : public QDialog
{
    Q_OBJECT

public:
    explicit Parametres(QWidget *parent = nullptr);
    ~Parametres();

private slots:

    void on_saveParametresButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Parametres *ui;
};

#endif // PARAMETRES_H
