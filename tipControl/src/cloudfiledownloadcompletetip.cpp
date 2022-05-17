#include <QtCore/QPropertyAnimation>

#include <QtGui/QShowEvent>

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QApplication>
#include "cloudfiledownloadcompletetip.h"

static const char* tipSuccess = "云工程\"%1\"下载成功";

#define DurationTime 1000

CloudFileDownLoadCompleteTip::CloudFileDownLoadCompleteTip(const QString & filePath, QWidget * parent)
    : QWidget(parent)
    , m_FilePath(filePath)
{
    m_pOpenLink = nullptr;
    m_pAnimation = nullptr;
    m_pRedOpacity = nullptr;
    //setMaximumWidth(400);
    //setFixedHeight(30);
    resize(400, 30);

    setWindowFlags(Qt::FramelessWindowHint /*| Qt::Tool| Qt::Window | Qt::SubWindow*/);
    setFocusPolicy(Qt::NoFocus);
    //setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_DeleteOnClose);

    InitializeUI();
    InitializeConnect();
    //InitializeShadow();
    //InitializeBlur();
    InitalizeColorize();

    m_FadeOutTimer.start(DurationTime);

// 	if (QWidget *parentWidget = this->parentWidget())
// 	{
// 		QPoint pos((parentWidget->width() - width()) / 2, 0);
// 		move(parentWidget->mapToGlobal(pos));
// 	}

    qApp->installNativeEventFilter(this);
}

CloudFileDownLoadCompleteTip::~CloudFileDownLoadCompleteTip()
{

}

bool CloudFileDownLoadCompleteTip::eventFilter(QObject * watched, QEvent * event)
{
    if (m_pOpenLink == watched)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            emit OpenFile(m_FilePath);
            close();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void CloudFileDownLoadCompleteTip::enterEvent(QEvent * e)
{
    if (m_FadeOutTimer.isActive())
    {
        m_FadeOutTimer.stop();
    }

    if (m_pAnimation->state() != QAbstractAnimation::Stopped)
    {
        if (m_pRedOpacity)
        {
            m_pRedOpacity->setOpacity(1);
        }
        setWindowOpacity(1);
        m_pAnimation->stop();
    }

    QWidget::enterEvent(e);
}

void CloudFileDownLoadCompleteTip::leaveEvent(QEvent * e)
{
    if (!m_FadeOutTimer.isActive())
    {
        m_FadeOutTimer.start(DurationTime);
    }

    QWidget::leaveEvent(e);
}

void CloudFileDownLoadCompleteTip::showEvent(QShowEvent * event)
{
// 	if (QWidget *parentWidget = this->parentWidget())
// 	{
// 		QPoint pos((parentWidget->width() - width()) / 2, 0);
// 		move(parentWidget->mapToGlobal(pos));
// 	}

    QWidget::showEvent(event);
}

bool CloudFileDownLoadCompleteTip::nativeEventFilter(const QByteArray &eventType	, void *message, long *)
{
// 	if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
// 	{
// 		MSG * pMsg = reinterpret_cast<MSG *>(message);
//
// 		if (pMsg->message == WM_MOVE || pMsg->message == WM_SIZE)
// 		{
// 			if (QWidget *parentWidget = this->parentWidget())
// 			{
// 				QPoint pos((parentWidget->width() - width()) / 2, 0);
// 				move(parentWidget->mapToGlobal(pos));
// 			}
// 		}
// 	}

    return false;
}

void CloudFileDownLoadCompleteTip::InitializeUI()
{
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(20, 0, 10, 0);
    mainLayout->setSpacing(15);

    QPushButton * iconBtn = new QPushButton;
    QLabel * text = new QLabel;
    m_pOpenLink = new QLabel;
    QPushButton * closeBtn = new QPushButton;

    m_pOpenLink->setObjectName(QStringLiteral("SuccessTip"));
    iconBtn->setFixedSize(32, 32);
    text->setMaximumWidth(260);
    m_pOpenLink->setFixedSize(47, 20);
    closeBtn->setFixedSize(15, 15);

    iconBtn->setStyleSheet("border-image:url(:/tip/DownClose.png);");

    QString strContent = text->fontMetrics().elidedText(QFile(m_FilePath).fileName(), Qt::ElideRight, text->width() - 118);

    QString strTip = QString("%1").arg(QStringLiteral("云工程\"%1\"下载成功!")).arg(strContent);
    text->setText(strTip);

    m_pOpenLink->installEventFilter(this);
    m_pOpenLink->setText(QStringLiteral("open immediately"));
    m_pOpenLink->setCursor(Qt::PointingHandCursor);

    mainLayout->addWidget(iconBtn, 0, Qt::AlignCenter);
    mainLayout->addWidget(text, 1);
    mainLayout->addWidget(m_pOpenLink, 0, Qt::AlignCenter);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignCenter);

    QWidget * bgWidget = new QWidget;
    bgWidget->setLayout(mainLayout);
    bgWidget->setStyleSheet("QWidget{background:#777777;}"
        "QLabel{color:#ffffff;}"
        "QLabel#SuccessTip{border:0 solid red;border-bottom:1 solid #ffffff;text-align:center;padding-left:-3px;}"
        "QLabel#SuccessTip:hover{color:red;border-bottom:1 solid red;}");

    QHBoxLayout * bgLayout = new QHBoxLayout;
    bgLayout->setSpacing(0);
    bgLayout->setMargin(0);

    bgLayout->addWidget(bgWidget);
    m_pMoveWidget = bgWidget;

    setLayout(bgLayout);
}

void CloudFileDownLoadCompleteTip::InitializeConnect()
{
    m_pAnimation = new QPropertyAnimation(this);
    m_pAnimation->setTargetObject(this);

    connect(m_pAnimation, &QPropertyAnimation::finished, this, &CloudFileDownLoadCompleteTip::close);

    m_pAnimation->setDuration(5000);

    m_pAnimation->setEasingCurve(QEasingCurve::Linear);

    connect(&m_FadeOutTimer, &QTimer::timeout, this, [this]{
        m_FadeOutTimer.stop();

        //ZoomIn();
        MoveTop();
        //FadeOut();

        m_pAnimation->start();
    });
}

void CloudFileDownLoadCompleteTip::InitializeShadow()
{
    m_pShadow = new QGraphicsDropShadowEffect(this);
    m_pShadow->setColor(Qt::lightGray);
    m_pShadow->setBlurRadius(25);
    m_pShadow->setOffset(5, 5);

    setGraphicsEffect(m_pShadow);
}

void CloudFileDownLoadCompleteTip::InitializeBlur()
{
    m_pBlur = new QGraphicsBlurEffect;
    m_pBlur->setBlurRadius(10);

    setGraphicsEffect(m_pBlur);
}

void CloudFileDownLoadCompleteTip::InitalizeColorize()
{
    m_pColorize = new QGraphicsColorizeEffect;
    m_pColorize->setStrength(1);
    m_pColorize->setColor(QColor(0 , 0, 192));

    setGraphicsEffect(m_pColorize);
}

void CloudFileDownLoadCompleteTip::ZoomIn()
{
    m_pAnimation->setPropertyName("geometry");

    QRect startRect = rect();
    startRect.moveTo(pos());
    QRect stopRect = QRect(startRect.center(), QSize(0, 0));

    m_pAnimation->setStartValue(startRect);
    m_pAnimation->setEndValue(stopRect);
}

void CloudFileDownLoadCompleteTip::MoveTop()
{
    m_pAnimation->setTargetObject(m_pMoveWidget);
    m_pAnimation->setPropertyName("pos");

    m_pAnimation->setStartValue(QPoint());
    m_pAnimation->setEndValue(QPoint(0, -height()));
}

void CloudFileDownLoadCompleteTip::FadeOut()
{
    m_pRedOpacity = new QGraphicsOpacityEffect(this);
    m_pRedOpacity->setOpacity(1);

    setGraphicsEffect(m_pRedOpacity);

    m_pAnimation->setTargetObject(m_pRedOpacity);
    m_pAnimation->setPropertyName("opacity");

    m_pAnimation->setStartValue(1);
    m_pAnimation->setEndValue(0);
}
