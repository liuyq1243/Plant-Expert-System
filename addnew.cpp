#include "addnew.h"

addNew::addNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNew)
{
    ui->setupUi(this);

    addCombox(this,ui->sel_indi_fea,ui->sel_spec_fea,ui->sel_spec);

    //btn_ok
    connect(ui->btn_ok,&QPushButton::clicked,[=](){
        QStringList indi_fea = ui->sel_indi_fea->currentText();
        QStringList spec_fea = ui->sel_spec_fea->currentText();
        QStringList spec = ui->sel_spec->currentText();
        QString newIndi = "";

        QVector<int> parm;
        //有了这些文字之后开始和特征数组feature里的对应下标对应起来，然后把对应的下标放进parm数组里
        if(indi_fea.size()!=0){
            //QStringList用了currenttext()之后是直接读取整行文本，需要再进行分隔。
            //然后再用at函数返回值是一个QString类型值，这个值用split分割后范围Qlist值。
            //比如说indi_fea调用currentText后得到 "有刺;可食用" ，md，这一看就是你这不知道用法啊，这有at肯定有直接分隔的。
            //然后at得到"有刺;可食用"的QString类型，用一个split分成QList("有刺", "可食用")。
            //底下两个文本框同理
            //用到vector.size()的地方的迭代器就改成报warning的那个类型就行了
            QString temp = indi_fea.at(0);
            QList indiFea_list = temp.split(';');
            for (int it=0;it<indiFea_list.size(); it++){
                for(int i=0; i<feature.size(); ++i){
                   if(indiFea_list[it]==feature[i]){
                        parm.push_back(i);
                   }
                }
            }
        }
        if(spec_fea.size()!=0){
            QString temp = spec_fea.at(0);
            QList specFea_list = temp.split(';');
//            qDebug() << "spec_fea: " << temp;
//            qDebug() << "specFea_list: " << specFea_list;
            for (int it=0;it<specFea_list.size(); it++){
                for(int i=0; i<feature.size(); ++i){
                   if(specFea_list[it]==feature[i]){
                        parm.push_back(i);
                   }
                }
            }
        }
        if(spec.size()!=0){
            QString temp = spec.at(0);
//            qDebug() << "spec: " << temp;
            QList spec_list = temp.split(';');
//            qDebug() << "spec_list: " << spec_list;
            for (int it=0;it<spec_list.size(); it++){
                for(int i=0; i<feature.size(); ++i){
                   if(spec_list[it]==feature[i]){
                        parm.push_back(i);
                   }
                }
            }
        }

        vector<int> new_par;
        for(int i=0;i<parm.size();i++){
            new_par.push_back(parm[i]);
        }

        newIndi = ui->input_indi->text();
        feature.push_back(newIndi);
        add_edge(new_par,feature.indexOf(newIndi));


        QMessageBox msgBox;
        msgBox.setWindowTitle("Attention");
        msgBox.setText("Add successfully!");
        msgBox.exec();
        this->close();
    });

    //btn_cancel
    connect(ui->btn_cancel,&QPushButton::clicked,[=](){
        this->close();
    });

}

addNew::~addNew()
{
    delete ui;
}
