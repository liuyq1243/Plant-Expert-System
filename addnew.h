#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>
#include "ui_addnew.h"
#include "judge.h"
#include "QFile"
#include "QMessageBox"
#include "QPushButton"
#include "QDebug"
#include "util.h"


namespace Ui {
class addNew;
}

class addNew : public QDialog
{
    Q_OBJECT

public:
    explicit addNew(QWidget *parent = nullptr);
    ~addNew();

signals:
    void rules_add();

private:
    Ui::addNew *ui;
};

#endif // ADDNEW_H
