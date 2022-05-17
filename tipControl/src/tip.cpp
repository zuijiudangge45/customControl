#include "cloudfiledownloadcompletetip.h"

#include "tip.h"
#include "operatetip.h"

#include <QColorDialog>

Q_DECLARE_METATYPE(OperateTip::AnimationMode)
Q_DECLARE_METATYPE(OperateTip::Direction)

tip::tip(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_color = Qt::cyan;
    ui.pushButton_color->setStyleSheet(QString("background:%1;border:0 solid red;").arg(m_color.name()));

    ui.comboBox_animation->clear();
    ui.comboBox_direction->clear();

    ui.comboBox_animation->addItem(QStringLiteral("淡出"), OperateTip::AM_FADEOUT);
    ui.comboBox_animation->addItem(QStringLiteral("飞出"), OperateTip::AM_FLYOUT);
    ui.comboBox_animation->addItem(QStringLiteral("最小化"), OperateTip::AM_ZOOMIN);

    ui.comboBox_direction->addItem(QStringLiteral("左"), OperateTip::D_LEFT);
    ui.comboBox_direction->addItem(QStringLiteral("上"), OperateTip::D_TOP);
    ui.comboBox_direction->addItem(QStringLiteral("右"), OperateTip::D_RIGHT);
    ui.comboBox_direction->addItem(QStringLiteral("下"), OperateTip::D_BOTTOM);

    ui.comboBox_animation->setCurrentIndex(1);

    connect(ui.comboBox_animation, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, [this](int index){
        ui.comboBox_direction->setVisible(index == 1);
    });
}

tip::~tip()
{

}

void tip::on_pushButton_clicked()
{
    CloudFileDownLoadCompleteTip * tipWidget = new CloudFileDownLoadCompleteTip(QStringLiteral("测试，测试，测试，测试，测试，测试，测试，测试，测试，测试，测试"), this);

    tipWidget->move(40, 40);
    tipWidget->show();
}

void tip::on_pushButton_red_clicked()
{
    OperateTip::colorize(this, QStringLiteral("测"), Qt::red, OperateTip::AM_ZOOMIN, OperateTip::D_NULL, 3000, 10000);
}

void tip::on_pushButton_green_clicked()
{
    OperateTip::colorize(this, QStringLiteral("测试，测试，测试"), Qt::green, OperateTip::AM_FADEOUT, OperateTip::D_NULL, 10000, 1000);
}

void tip::on_pushButton_color_clicked()
{
    QColorDialog colorDlg(m_color);

    if (colorDlg.exec() == QColorDialog::Accepted)
    {
        m_color = colorDlg.selectedColor();
    }

    ui.pushButton_color->setStyleSheet(QString("background-color:%1;border:0 solid red;").arg(m_color.name()));
}

void tip::on_pushButton_ok_clicked()
{
    int stayTime = ui.spinBox_staytime->value();
    int duration = ui.spinBox_animationDuration->value();
    OperateTip::AnimationMode animation = (OperateTip::AnimationMode)ui.comboBox_animation->itemData(ui.comboBox_animation->currentIndex()).toInt();
    OperateTip::Direction direction = (OperateTip::Direction)ui.comboBox_direction->itemData(ui.comboBox_direction->currentIndex()).toInt();
    OperateTip::colorize(this, QStringLiteral("测试，测试"), m_color, animation, direction, stayTime, duration);
}

void tip::on_pushButton_left_clicked()
{
    OperateTip::flyOut(this, QStringLiteral("测试，测试"), OperateTip::D_LEFT, 1000, 1000);
}

void tip::on_pushButton_top_clicked()
{
    OperateTip::flyOut(this, QStringLiteral("测试，测试"), OperateTip::D_TOP, 1000, 1000);
}

void tip::on_pushButton_right_clicked()
{
    OperateTip::flyOut(this, QStringLiteral("测试，测试"), OperateTip::D_RIGHT, 1000, 1000);
}

void tip::on_pushButton_bottom_clicked()
{
    OperateTip::flyOut(this, QStringLiteral("测试，测试"), OperateTip::D_BOTTOM, 1000, 1000);
}

void tip::on_pushButton_success_clicked()
{
    OperateTip::success(this, QStringLiteral(""), 1000, 1000);
}

void tip::on_pushButton_warning_clicked()
{
    OperateTip::waring(this, QStringLiteral("测试，测试"), 1000, 1000);
}

