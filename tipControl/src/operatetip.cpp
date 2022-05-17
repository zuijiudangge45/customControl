#include <QTimer>
#include <QString>
#include <QPropertyAnimation>

#include <QLabel>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QMdiSubWindow>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QApplication>

#include "operatetip.h"

extern QMainWindow * g_pMainWindow;

static const QString c_szStyleSheet = "QWidget{background-color:%1;\
        border:1px solid %2;border-top:0;border-bottom-left-radius:3px;\
border-bottom-right-radius:3px;background-image: url();}\
";

static const char *c_szGMPOperateTip = "GMPOperateTip";
static const char *c_szSuccess = QT_TRANSLATE_NOOP("GMPOperateTip", "操作成功");
static const char *c_szWaring = QT_TRANSLATE_NOOP("GMPOperateTip", "操作失败");

/*!
*@brief 淡出提示框
*@author renl 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void OperateTip::fadeOut(QWidget * parent /*= nullptr */
                         , QString strText /*= "" */
                         , const unsigned int nShowTime /*= 4000 */
                         , const unsigned int nAnimationTime /*= 500*/)
{
    OperateTip * tipWidget = new OperateTip(parent);
    tipWidget->setAnimationMode(AM_FADEOUT);

    tipWidget->setText(strText);
    tipWidget->setStayTime(nShowTime);
    tipWidget->setAnimationdDuration(nAnimationTime);

    tipWidget->show();
}

/*!
*@brief 自定义飞出方向提示框
*@author renl 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；direction：飞出方向；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void OperateTip::flyOut(QWidget * parent /*= nullptr */
                        , QString strText /*= "" */
                        , Direction direction /*= D_TOP*/
                        , const unsigned int nShowTime /*= 4000 */
                        , const unsigned int nAnimationTime /*= 500 */)
{
    OperateTip * tipWidget = new OperateTip(parent);
    tipWidget->setAnimationMode(AM_FLYOUT);
    tipWidget->setStyleSheet(c_szStyleSheet.arg("#12B33D").arg("#2ABB51"));

    tipWidget->setText(strText);
    tipWidget->setFlyoutDirection(direction);
    tipWidget->setStayTime(nShowTime);
    tipWidget->setAnimationdDuration(nAnimationTime);

    tipWidget->show();
}

/*!
*@brief 自定义背景色提示框
*@author renl 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；color：背景色；animation：动画模式；direction：飞出方向；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void OperateTip::colorize(QWidget * parent      /*= nullptr */
                          , QString strText     /*= "" */
                          , const QColor & color/* = QColor(20, 142, 53) */
                          , AnimationMode animation           /*= AM_FLYOUT */
                          , Direction direction /*= D_TOP */
                          , const unsigned int nShowTime      /*= 4000 */
                          , const unsigned int nAnimationTime /*= 500*/)
{
    OperateTip * tipWidget = new OperateTip(parent);

    tipWidget->setText(strText);
    tipWidget->setBackgroundColor(color);
    tipWidget->setAnimationMode(animation);
    tipWidget->setFlyoutDirection(direction);
    tipWidget->setStayTime(nShowTime);
    tipWidget->setAnimationdDuration(nAnimationTime);
    tipWidget->show();
}

/*!
*@brief 警告提示框
*@author renl 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void OperateTip::waring(QWidget * parent /*= nullptr */
                        , QString strText /*= "" */
                        , const unsigned int nShowTime /*= 4000 */
                        , const unsigned int nAnimationTime /*= 500*/)
{
    OperateTip * tipWidget = new OperateTip(parent);
    tipWidget->setAnimationMode(AM_FLYOUT);
    tipWidget->setFlyoutDirection(D_TOP);

    tipWidget->setIcon(":/tip/warning.png");
    tipWidget->setStyleSheet(c_szStyleSheet.arg("#FF9830").arg("#FF9326"));
    if (strText.isEmpty())
    {
        tipWidget->setText(qApp->translate(c_szGMPOperateTip, c_szWaring));
    }
    else
    {
        tipWidget->setText(strText);
    }
    tipWidget->setStayTime(nShowTime);
    tipWidget->setAnimationdDuration(nAnimationTime);

    tipWidget->show();
}

/*!
*@brief 成功提示框
*@author renl 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void OperateTip::success(QWidget * parent /*= nullptr */
                         , QString strText /*= "" */
                         , const unsigned int nShowTime /*= 4000 */
                         , const unsigned int nAnimationTime /*= 500*/)
{
    OperateTip * tipWidget = new OperateTip(parent);
    tipWidget->setStyleSheet(c_szStyleSheet.arg("#12B33D").arg("#2ABB51"));
    tipWidget->setAnimationMode(AM_FLYOUT);
    tipWidget->setFlyoutDirection(D_TOP);
    if (strText.isEmpty())
    {
        tipWidget->setText(qApp->translate(c_szGMPOperateTip, c_szSuccess));
    }
    else
    {
        tipWidget->setText(strText);
    }
    tipWidget->setStayTime(nShowTime);
    tipWidget->setAnimationdDuration(nAnimationTime);

    tipWidget->show();
}

OperateTip::OperateTip(QWidget * parent)
    : QWidget(parent)
    , m_eMode(AM_FLYOUT)
    , m_eDirection(D_TOP)
    , m_DurationTime(500)
    , m_iStayDuration(4000)
    , m_pMessageIcon(nullptr)
    , m_pMessage(nullptr)
    , m_pMoveWidget(nullptr)
    , m_pAnimation(nullptr)
    , m_pOpacity(nullptr)
    , m_pShadow(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_QuitOnClose, false);

    initializeUI();
    initializeConnect();

    setShadowEnable(true);

    m_pMoveWidget->setMinimumWidth(130);

    m_StayTimer.setSingleShot(true);
}

OperateTip::~OperateTip()
{
    m_pMessageIcon = nullptr;
    m_pMessage = nullptr;
    m_pMoveWidget = nullptr;
    m_pAnimation = nullptr;
    m_pOpacity = nullptr;
    m_pShadow = nullptr;
}

/*!
*@brief 设置文本内容
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/

void OperateTip::setText(const QString & text)
{
    if (m_pMessage)
    {
        m_pMessage->setText(text);
    }
}

/*!
*@brief 设置图标
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setIcon(const QString & icon)
{
    if (m_pMessageIcon)
    {
        m_pMessageIcon->setPixmap(QPixmap(icon));
    }
}

/*!
*@brief 设置背景色
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setBackgroundColor(const QColor & color)
{
    QColor border = color;
    border.setAlpha(255 * 0.1);
    QString strBorderRgba = QString("rgba(%1,%2,%3,%4)").arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha());
    setStyleSheet(c_szStyleSheet.arg(color.name()).arg(strBorderRgba));
}

/*!
*@brief 消失动画模式
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setAnimationMode(AnimationMode mode)
{
    if (m_eMode == mode)
    {
        return;
    }

    m_eMode = mode;
}

/*!
*@brief 消失动画为飞出时有效 设置飞出方向
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setFlyoutDirection(Direction direction)
{
    if (m_eDirection == direction)
    {
        return;
    }

    m_eDirection = direction;
}

/*!
*@brief 设置是否启用提示框阴影
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setShadowEnable(bool enable)
{
    if (!m_pShadow)
    {
        m_pShadow = new QGraphicsDropShadowEffect(this);
        m_pShadow->setColor(QColor(0, 0, 0, 70));
        m_pShadow->setBlurRadius(10);
        m_pShadow->setOffset(4, 4);
    }

    setGraphicsEffect(enable ? m_pShadow : nullptr);
}

/*!
*@brief 设置提示框消失动画时长
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setAnimationdDuration(int duration)
{
    m_DurationTime = duration;
}

/*!
*@brief 设置提示框停留时长
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::setStayTime(int time)
{
    m_iStayDuration = time;
}

/*!
*@brief  重写窗口事件函数，当窗口显示时启动定时器
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
bool OperateTip::event(QEvent * e)
{
    if (e->type() == QEvent::Show)
    {
        adjustSize();
        int nposx = qrand() % (parentWidget()->rect().width() - this->rect().width());
        int nposy = qrand() % (parentWidget()->rect().height() - this->rect().height() );

        move(nposx, nposy);

        m_StayTimer.start(m_iStayDuration);
    }

    return QWidget::event(e);
}

void OperateTip::paintEvent(QPaintEvent *)
{

}

/*!
*@brief 提示框内部布局，可重写
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::layoutUI(QHBoxLayout * layout)
{
    m_pMessageIcon = new QLabel(this);
    QPixmap pixmap(":/tip/success.png");
    m_pMessageIcon->setPixmap(pixmap);
    m_pMessageIcon->setStyleSheet("border:0px solid #FFFFFF;");

    m_pMessage = new QLabel("", this);
    m_pMessage->setStyleSheet("border:0px solid #FFFFFF;\
                               color: #FFFFFF;\
                               font-size: 14px;\
                               font-family:'Microsoft YaHei';\
                              ");

    layout->addWidget(m_pMessageIcon);
    layout->addWidget(m_pMessage);
}

/*!
*@brief 初始化主界面布局
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::initializeUI()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setContentsMargins(10, 4, 11, 6);
    pLayout->setSpacing(10);

    layoutUI(pLayout);

    QWidget * bgWidget = new QWidget;
    bgWidget->setLayout(pLayout);
    QHBoxLayout * bgLayout = new QHBoxLayout;
    bgLayout->setSpacing(0);
    bgLayout->setMargin(0);

    bgLayout->addWidget(bgWidget);
    m_pMoveWidget = bgWidget;

    setLayout(bgLayout);
}

/*!
*@brief 初始化动画，并添加定时器槽函数
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::initializeConnect()
{
    m_pAnimation = new QPropertyAnimation(this);
    m_pAnimation->setTargetObject(this);

    connect(m_pAnimation, &QPropertyAnimation::finished, this, &OperateTip::close);

    connect(&m_StayTimer, &QTimer::timeout, this, [this]{
        m_pAnimation->setDuration(m_DurationTime);
        switch (m_eMode)
        {
        case AM_FADEOUT:
            fade();
            break;
        case AM_FLYOUT:
            moveOut();
            break;
        case AM_ZOOMIN:
            zoomIn();
            break;
        default:
            ;
        }

        m_pAnimation->start();
    });
}

/*!
*@brief 提示框缩小动画
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::zoomIn()
{
    m_pAnimation->setPropertyName("geometry");

    QRect startRect = rect();
    startRect.moveTo(pos());
    QRect stopRect = QRect(startRect.center(), QSize(0, 0));

    m_pAnimation->setStartValue(startRect);
    m_pAnimation->setEndValue(stopRect);
}

/*!
*@brief 提示框飞出动画
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::moveOut()
{
    m_pAnimation->setTargetObject(m_pMoveWidget);
    m_pAnimation->setPropertyName("pos");

    m_pAnimation->setStartValue(QPoint());
    switch (m_eDirection)
    {
    case D_LEFT:
        m_pAnimation->setEndValue(QPoint(-width(), 0));
        break;
    case D_TOP:
        m_pAnimation->setEndValue(QPoint(0, -height()));
        break;
    case D_RIGHT:
        m_pAnimation->setEndValue(QPoint(width(), 0));
        break;
    case D_BOTTOM:
        m_pAnimation->setEndValue(QPoint(0, height()));
        break;
    default:
        ;
    }
}

/*!
*@brief 提示框淡出动画
*@author renl 2017年8月7日
*@param[in]
*@return       void
*/
void OperateTip::fade()
{
    m_pOpacity = new QGraphicsOpacityEffect(this);
    m_pOpacity->setOpacity(1);

    setGraphicsEffect(m_pOpacity);

    m_pAnimation->setTargetObject(m_pOpacity);
    m_pAnimation->setPropertyName("opacity");

    m_pAnimation->setStartValue(1);
    m_pAnimation->setEndValue(0);
}


