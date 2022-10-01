#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QUdpSocket>
#include <QLabel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;//
    QString getLocalIP();//获取本机IP地址
};

#endif // WIDGET_H
