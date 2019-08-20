#include "udpsendthread.h"



std::time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
    return timestamp;
}


udpSendThread::udpSendThread(QObject *parent) : QThread(parent)
{

}

void udpSendThread::run()
{
    char buff[1024*1024]={0};//1024*1024 = 1048576
    QUdpSocket qus;

//    for(int i=0;i<1048576;i++)
//    {

//    }

    memset(buff,1,1048576);
    std::time_t t_start = getTimeStamp();
    int size=0;
    uint64_t s=0;
    while(1)
    {


        uint ret = qus.writeDatagram((char*)buff,1024*40, QHostAddress("127.0.0.1"), 8899);
        if(ret!=1024*40)
            printf("writeDatagram error\n");
        size++;
        s = size*1024*40;
        if(size%(4) == 0)
        {
//            QThread::msleep(2);
            QThread::usleep(1600);
            printf("size %lf\n",(double)s/(double)(1024*1024));
            fflush(0);
        }
        //if(size == 1024*100)

        if(s>=1048576*1024)
            break;
    }
    std::time_t t_end = getTimeStamp();
    double t = t_end-t_start;
    double speed = (double)(s)/((t/1000.0)*(1024*1024));
    printf("send:%uBytes,%ld -> %ld,t:%f,speed:%lfMB/s\n",s,t_start,t_end,t,speed);
    fflush(NULL);
}
