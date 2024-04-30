#include "reverseconduct.h"

reverseConduct::reverseConduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reverseConduct)
{
    ui->setupUi(this);

    int random_pic_index =rand() % (31-24+1) + 24;
    QString pic_path =id_pic_map.value(random_pic_index);
    ui->lab_pic->setPixmap(QPixmap(pic_path));
    ui->lab_name->setText(feature[random_pic_index]);

    addCombox(this,ui->sel_indi_fea,ui->sel_spec_fea,ui->sel_spec);

    //submit
    connect(ui->btn_submit,&QPushButton::clicked,[=](){
        //qDebug() << "submit";

        //按下submit之后才把文本框里的文字读进来，currentText()
        QStringList indi_fea = ui->sel_indi_fea->currentText();
        QStringList spec_fea = ui->sel_spec_fea->currentText();
        QStringList spec = ui->sel_spec->currentText();

        vector<int> parm;
        //有了这些文字之后开始和特征数组feature里的对应下标对应起来，然后把对应的下标放进parm数组里
        if(indi_fea.size()!=0){
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

        ResFeature res;
        func(parm,random_pic_index,res);

        QString wrong_fea;
        for(int i=0;i<res.fail.size();i++){
            wrong_fea.append(feature[res.fail[i]]+" ");
        }

        QString lack_fea;
        for(int i=0;i<res.lack.size();i++){
            lack_fea.append(feature[res.lack[i]]+" ");
        }

        QString right_answer;
        for(int i=0;i<res.answer.size();i++){
            right_answer.append(feature[res.answer[i]]+" ");
        }

        QString my_answer;
        for(int i=0;i<parm.size();i++){
            my_answer.append(feature[parm[i]]+" ");
        }

        QString result =QString("%1 has features: %2\nYour choice: %3\nWrong features: %4\nLack features: %5")
                .arg(feature[random_pic_index]).arg(right_answer).arg(my_answer).arg(wrong_fea).arg(lack_fea);

        ui->text_result->setText(result);

    });
}

//重写closeEvent
void reverseConduct::closeEvent(QCloseEvent *event)//此函数在QWidget关闭时执行
{
    emit exit_signal();
}

reverseConduct::~reverseConduct()
{
    emit exit_signal();
    delete ui;
}
