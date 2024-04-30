#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int total_rules = 15;

    ui->setupUi(this);

    addCombox(this,ui->sel_indi_fea,ui->sel_spec_fea,ui->sel_spec);

    //底部状态栏
//    QLabel* totalRules_status = new QLabel(this);
//    totalRules_status->setText("Total rules: "+QString::number(total_rules,10));
//    ui->statusbar->addWidget(totalRules_status);

    //Add new rule
    connect(ui->btn_addNewRule,&QPushButton::clicked,[=](){
//        if(addDialog==NULL){
//            addDialog = new addNew();
//        }
        addNew* addDialog = new addNew();

        addDialog->setModal(true);
        addDialog->setWindowTitle("Add new rule");
        addDialog->show();
    });

    //then
    connect(ui->btn_then,&QPushButton::clicked,[=](){
        //显示结果
        QStringList indi_fea = ui->sel_indi_fea->currentText();
        QStringList spec_fea = ui->sel_spec_fea->currentText();
        QStringList spec = ui->sel_spec->currentText();

        vector<int> parm;
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

        vector<int> ret = judge(parm);

        //输出
        QString result = "";
        for(int i=0;i<ret.size();i++){
//            result.append(QString::fromLocal8Bit((feature[ret[i]]+" ").c_str()));
            result.append(feature[ret[i]]+" ");
        }

        ui->result->setText(result);
    });

    //reverseConduct
    connect(ui->ben_reverseCon,&QPushButton::clicked,[=](){
//       if(reverseScene==NULL){
//            reverseScene = new reverseConduct();
//       }
       reverseConduct* reverseScene =new reverseConduct();

//       this->hide();

//       reverseScene->setAttribute(Qt::WA_DeleteOnClose, true);
       reverseScene->show();
    });

    //reverse关闭 mainScene show
//    connect(reverseScene,SIGNAL(exit_signal()),this,SLOT(reverse_exit_slot()));

    //total rules num add
}

void MainWindow::rules_add_slot(int total_rules){
    QLabel* totalRules_status = new QLabel(this);
    totalRules_status->setText("Total rules: "+QString::number(total_rules,10));
    ui->statusbar->addWidget(totalRules_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

