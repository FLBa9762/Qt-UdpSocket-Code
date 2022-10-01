#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QUdpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    Ui::Widget *ui;
    QUdpSocket *udpSocket;//
    QString getLocalIP();//获取本机IP地址

private slots:
    void onSocketReadyRead();//读取socket传入的数据
    void on_pushButton_clicked();
};

#endif // WIDGET_H
