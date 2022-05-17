#ifndef GMPCLOUDFILEDOWNLOADCOMPLETETIP_H
#define GMPCLOUDFILEDOWNLOADCOMPLETETIP_H

#include <QtCore/QTimer>

#include <QtWidgets/QWidget>

#include <QAbstractNativeEventFilter>
#include <QGraphicsDropShadowEffect>

class QLabel;
class QPropertyAnimation;
class QGraphicsOpacityEffect;

/*!
*@file     云文件下载成功提示框
*@brief    云文件下载成功，OpenFile信号打开已下载文件
*@author   renl-a
*@date     2017年7月6日
*@remarks
*@version 3.0
*Copyright (c) 1998-2013 Glodon Corporation
*/
class CloudFileDownLoadCompleteTip : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

signals:
    void OpenFile(const QString & filePath);

public:
    CloudFileDownLoadCompleteTip(const QString & filePath, QWidget * parent = nullptr);
    ~CloudFileDownLoadCompleteTip();

protected:
    virtual bool eventFilter(QObject *, QEvent *) override;
    virtual void enterEvent(QEvent *) override;
    virtual void leaveEvent(QEvent *) override;
    virtual void showEvent(QShowEvent *) override;

    //QAbstractNativeEventFilter
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;

private:
    void InitializeUI();
    void InitializeConnect();
    void InitializeShadow();//阴影
    void InitializeBlur();//滤镜 主要是模糊处理
    void InitalizeColorize();//窗口着色

    void ZoomIn();//缩小
    void MoveTop();//向上移动
    void FadeOut();//淡出

private:

    QString						m_FilePath;
    QTimer						m_FadeOutTimer;
    QLabel *					m_pOpenLink;
    QWidget *					m_pMoveWidget;

    QPropertyAnimation *		m_pAnimation;
    QGraphicsOpacityEffect *	m_pRedOpacity;
    QGraphicsDropShadowEffect * m_pShadow;
    QGraphicsBlurEffect *		m_pBlur;
    QGraphicsColorizeEffect *	m_pColorize;
};

#endif // GMPCLOUDFILEDOWNLOADCOMPLETETIP_H
