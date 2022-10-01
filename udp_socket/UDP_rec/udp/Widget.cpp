#include "Widget.h"
#include "ui_Widget.h"
#include    <QtNetwork>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString localIP=getLocalIP();//本机IP
    this->setWindowTitle(this->windowTitle()+"----本机IP："+localIP);

    udpSocket=new QUdpSocket(this);//用于与连接的客户端通讯的QTcpSocket
    connect(udpSocket,SIGNAL(readyRead()),
            this,SLOT(onSocketReadyRead()));

//    udpSocket=new QUdpSocket(this);//用于与连接的客户端通讯的QTcpSocket
//    connect(udpSocket,SIGNAL(readyRead()),
//            this,SLOT(onSocketReadyRead()));
}

Widget::~Widget()
{
    udpSocket->abort();
    delete udpSocket;
    delete ui;
}

QString Widget::getLocalIP()
{
    QString hostName=QHostInfo::localHostName();//本地主机名
    QHostInfo   hostInfo=QHostInfo::fromName(hostName);
    QString   localIP="";

    QList<QHostAddress> addList=hostInfo.addresses();//

    if (!addList.isEmpty())
    for (int i=0;i<addList.count();i++)
    {
        QHostAddress aHost=addList.at(i);
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())
        {
            localIP=aHost.toString();
            break;
        }
    }
    return localIP;
}

void Widget::onSocketReadyRead()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());  //数据格式统一

        QHostAddress peerAddr;
        quint16 peerPort;
        udpSocket->readDatagram(datagram.data(),
                                datagram.size(),&peerAddr,&peerPort);   //接收数据
        QString str=datagram.data();    //数据转换为QT的ui界面使用的QString类型

        QString peer="[From "+peerAddr.toString()+":"
                +QString::number(peerPort)+"] ";

        ui->plainTextEdit->appendPlainText(peer+str);
    }
}

void Widget::on_pushButton_clicked()
{
    quint16 port = ui->spinBox->value(); //本机UDP端口
    if (udpSocket->bind(port)) //绑定端口成功
    {
        ui->plainTextEdit->appendPlainText("**成功绑定端口");
        ui->plainTextEdit->appendPlainText("**绑定端口：" +
                QString::number(udpSocket->localPort()));    }
}
