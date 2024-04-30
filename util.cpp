#include "util.h"

QVector<QString> feature = {
        "有刺", "水生", "喜阳", "药用", "木本", "可食用", "有白色粉末", "叶片针状", "结果实","黄色花",//区别个体的特征
        //0      1       2      3       4       5           6          7         8        9

        "种子有果皮", "种子无果皮", "无茎叶", "无根", "有托叶", "吸引菜粉蝶", "十字形花冠", "缺水环境",//区别种类的特征
        //  10           11         12      13      14          15          16          17

        "被子植物", "裸子植物", "藻类植物", "蔷薇科", "十字花科", "仙人掌科", //种类
        //  18          19          20         21         22         23

        "玫瑰", "荷花", "仙人球", "水棉", "苹果树", "油菜", "海带", "松树" };//个体
        //24      25       26        27       28      29      30     31

QString pic_base_path = ":/pic/res/pic/";
//图片路径与个体下标绑定
QMap<int,QString> id_pic_map = {{24,pic_base_path+"rose.jpg"},{25,pic_base_path+"lotus.jpg"},{26,pic_base_path+"cactus.jpg"},{27,pic_base_path+"spirogyra.jpg"},
                                {28,pic_base_path+"appleTree.jpg"},{29,pic_base_path+"rape.jpg"},{30,pic_base_path+"kelp.jpg"},{31,pic_base_path+"pineTree.jpg"}};

void addCombox(QWidget* widget,MultiSelectComboBox* sel_indi_fea,MultiSelectComboBox* sel_spec_fea,MultiSelectComboBox* sel_spec){
    //读取规则库
    QFile db(":/res/res/db.txt");
    if(!db.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(widget,"错误信息","无法打开规则库文件，规则读取失败");
        qDebug() << ("打开文件失败");
    }
    QTextStream txtInput(&db);
    QString lineStr;
    QStringList itemList;

    //个体特征
    lineStr = txtInput.readLine();
    itemList = lineStr.split(" ");
    sel_indi_fea->addItems(itemList);

    //种类特征
    lineStr = txtInput.readLine();
    itemList = lineStr.split(" ");
    sel_spec_fea->addItems(itemList);

    //种类
    lineStr = txtInput.readLine();
    itemList = lineStr.split(" ");
    sel_spec->addItems(itemList);

    db.close();
}
