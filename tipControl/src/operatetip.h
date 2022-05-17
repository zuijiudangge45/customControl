#ifndef GMPOPERATETIP_H
#define GMPOPERATETIP_H

#include <QFrame>
#include <QGraphicsOpacityEffect>
#include <QTimer>

class QTimer;
class QString;
class QLabel;
class QHBoxLayout;
class QPropertyAnimation;

/*!
*@file
*@brief    用户操作反馈信息框，提示用户操作成功或失败等状态
*@author   renl
*@date     2017年8月7日
*@remarks  该类提供了多个静态便利方法，可以直接调用
*/

class OperateTip : public QWidget
{
    Q_OBJECT

public:
    enum AnimationMode
    {
        AM_NULL,
        AM_FADEOUT,//淡出
        AM_FLYOUT,//飞出
        AM_ZOOMIN,//最小化
    };

    enum Direction
    {
        D_NULL,
        D_LEFT,
        D_TOP,
        D_RIGHT,
        D_BOTTOM,
    };

public:

    static void fadeOut(QWidget * parent = nullptr
        , QString strText = ""
        , const unsigned int nShowTime = 4000
        , const unsigned int nAnimationTime = 500);

    static void flyOut(QWidget * parent = nullptr
        , QString strText = ""
        , Direction direction = D_TOP
        , const unsigned int nShowTime = 4000
        , const unsigned int nAnimationTime = 500);

    static void colorize(QWidget * parent = nullptr
        , QString strText = ""
        , const QColor & color = QColor(20, 142, 53)
        , AnimationMode animation = AM_FLYOUT
        , Direction direction = D_TOP
        , const unsigned int nShowTime = 4000
        , const unsigned int nAnimationTime = 500);

    static void waring(QWidget * parent = nullptr
        , QString strText = ""
        , const unsigned int nShowTime = 4000
        , const unsigned int nAnimationTime = 500);

    static void success(QWidget * parent = nullptr
        , QString strText = ""
        , const unsigned int nShowTime = 4000
        , const unsigned int nAnimationTime = 500);

public:
    OperateTip(QWidget *parent = 0);
    ~OperateTip();

public:
    void setText(const QString & text);
    void setIcon(const QString & icon);

    void setBackgroundColor(const QColor & color);

    void setAnimationMode(AnimationMode mode);
    void setFlyoutDirection(Direction direction);

    void setShadowEnable(bool enable);

    void setAnimationdDuration(int duration);
    void setStayTime(int time);

protected:
    virtual bool event(QEvent *) override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void layoutUI(QHBoxLayout *);

private:
    void initializeUI();
    void initializeConnect();

    void zoomIn();//缩小
    void moveOut();//移出
    void fade();//淡出

private:
    AnimationMode				m_eMode;
    Direction					m_eDirection;
    int							m_DurationTime; //动画持续时长
    int							m_iStayDuration;//窗口停留时长
    QTimer						m_StayTimer;

    QLabel *					m_pMessageIcon;
    QLabel *					m_pMessage;
    QWidget *					m_pMoveWidget;

    QPropertyAnimation *		m_pAnimation;
    QGraphicsOpacityEffect *	m_pOpacity;
    QGraphicsDropShadowEffect * m_pShadow;
};

#endif // GMPOPERATETIP_H

