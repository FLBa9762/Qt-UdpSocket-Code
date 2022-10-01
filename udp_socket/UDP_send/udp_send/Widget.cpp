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


void Widget::on_pushButton_clicked()
{
    QString targetIP=ui->lineEdit->text();
    QHostAddress targetAddr(targetIP);  //目标IP

    quint16 targetPort = ui->spinBox->value();  //目标端口号
    QString msg = ui->plainTextEdit->toPlainText(); //发送内容
    QByteArray str = msg.toUtf8();

    udpSocket->writeDatagram(str, targetAddr, targetPort);  //发送函数

    ui->window->appendPlainText("[send]" + msg);   //信息栏显示

    ui->plainTextEdit->clear();
    ui->plainTextEdit->setFocus();
}
