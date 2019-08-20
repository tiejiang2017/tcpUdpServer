#ifndef UDPSENDTHREAD_H
#define UDPSENDTHREAD_H

#include <QObject>
#include<QThread>
#include<QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include<QTimer>
class udpSendThread : public QThread
{
    Q_OBJECT
public:
    explicit udpSendThread(QObject *parent = nullptr);


    void run();
signals:

public slots:
};

#endif // UDPSENDTHREAD_H
