#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "addnew.h"
#include "QFile"
#include "QDebug"
#include "QMessageBox"
#include "QLabel"
#include "reverseconduct.h"
#include "judge.h"
#include "util.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void reverse_exit_slot(){
        this->show();
    }
    void rules_add_slot(int total_rules);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
