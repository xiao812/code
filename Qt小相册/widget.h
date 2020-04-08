#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void displayImage(int value);

private slots:
    void on_pushButton_clicked();


    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::Widget *ui;
    int sum;        //总共截图数量
};
#endif // WIDGET_H
