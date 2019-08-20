#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QThread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);


    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));

    bool ok = tcpServer->listen(QHostAddress::Any, 9999);

    timer.setInterval(1);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_btnSend_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
        tcpClient.append(currentClient);
//        ui->cbxConnection->addItem(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1])\
//                                              .arg(currentClient->peerPort()));
        connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
        connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));


        printf("NewConnectionSlot\n");
        fflush(0);
        timer.start(1);

}

void MainWindow::disconnectedSlot()
{

}

void MainWindow::ReadData()
{
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();
        if(buffer.isEmpty())    continue;

        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr("[%1:%2]:").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                     .arg(tcpClient[i]->peerPort());

//                // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
//                if(IP_Port != IP_Port_Pre)
//                    ui->edtRecv->append(IP_Port);

//                ui->edtRecv->append(buffer);

        //更新ip_port
        IP_Port_Pre = IP_Port;
    }

}

void MainWindow::on_btnConnect_clicked()
{

    udpThread.start();
//    ushort dat=0x55aa;
//    uint count=0;
//    ushort buff[1024]={0};
//    printf("preing %d\n");
//    fflush(0);
//    for(int i=0;i<1024*2;i++)
//        buff[i]=dat;
//    printf("done %d\n");
//    fflush(0);
//    while(1)
//    {
//        qus.writeDatagram((char*)buff,1024*2, QHostAddress("127.0.0.1"), 8899);
//        count++;
//        if((count%50)==0)
//        {
//            printf("sending %d\n",count);
//            fflush(0);
//            QThread::msleep(10);
//        }
//        //while(qus.waitForBytesWritten()==false);
//        if(count>=999999)
//            break;
//    }


}

void MainWindow::on_btnSend_clicked()
{
    static float phase=0;

    float val = sin(phase);
    phase+=0.1;
    if(phase>=360)
        phase=0;
    currentClient->write((char*)&val,4);
//    printf("send %f ",val);
//    fflush(0);
}

void MainWindow::on_btnClear_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    on_btnConnect_clicked();
}
