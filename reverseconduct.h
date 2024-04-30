#pragma once

#ifndef REVERSECONDUCT_H
#define REVERSECONDUCT_H

#include <QWidget>
#include "ui_reverseconduct.h"
#include "QFile"
#include "QMessageBox"
#include "QDebug"
#include "judge.h"
#include "util.h"
#include <stdlib.h>
#include "QString"

namespace Ui {
class reverseConduct;
}

class reverseConduct : public QWidget
{
    Q_OBJECT

public:
    explicit reverseConduct(QWidget *parent = nullptr);
    ~reverseConduct();
    //重写closeEvent()
    void closeEvent(QCloseEvent* event);

signals:
    void exit_signal();

private:
    Ui::reverseConduct *ui;
};

#endif // REVERSECONDUCT_H
