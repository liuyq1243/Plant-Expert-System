#pragma once

#ifndef UTIL_H
#define UTIL_H

#include "QVector"
#include "QFile"
#include "QDebug"
#include "QMessageBox"
#include "multiselectcombobox.h"
#include "QMap"

extern QVector<QString> feature;
extern QMap<int,QString> id_pic_map;

void addCombox(QWidget* widget,MultiSelectComboBox* sel_indi_fea,MultiSelectComboBox* sel_spec_fea,MultiSelectComboBox* sel_spec);

#endif // UTIL_H
