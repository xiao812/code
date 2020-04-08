#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDir>
#include <QString>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString ImagePath = "./images";
    QDir dir(ImagePath);

    QStringList ImageList;
    ImageList << "*.jpg";
    dir.setNameFilters(ImageList);
    sum = dir.count();
    ui->horizontalScrollBar->setMaximum(sum);
    QString str1;
    str1 = QString::number(ui->horizontalScrollBar->value()) + " / " + QString::number(sum);
    ui->label_4->setText(str1);
    ui->horizontalScrollBar->setValue(sum);
    if(sum == 1)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg = image1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));
    }
    else if(sum == 2)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg = image1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));


        QImage image2;
        QString s2 = "./images/2.jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_2->setPixmap(QPixmap::fromImage(resultImg2));
    }
    else
    {
        QImage image1;
        QString s1 = "./images/" + QString::number(sum-2) + ".jpg";
        qDebug() << "test2 " << s1 << endl;
        image1.load(s1);
        QImage resultImg = image1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));


        QImage image2;
        QString s2 = "./images/" + QString::number(sum-1) + ".jpg";
        qDebug() << "test2 " << s2 << endl;
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_2->setPixmap(QPixmap::fromImage(resultImg2));

        QImage image3;
        QString s3 = "./images/" + QString::number(sum) + ".jpg";
        qDebug() << "test2 " << s3 << endl;
        image3.load(s3);
        QImage resultImg3 = image3.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_3->setPixmap(QPixmap::fromImage(resultImg3));
    }

}


void Widget::on_horizontalScrollBar_valueChanged(int value)
{
    QString ImagePath = "./images";
    QDir dir(ImagePath);

    QStringList ImageList;
    ImageList << "*.jpg";
    dir.setNameFilters(ImageList);
    sum = dir.count();
    ui->horizontalScrollBar->setMaximum(sum);
    QString str1;
    str1 = QString::number(ui->horizontalScrollBar->value()) + " / " + QString::number(sum);
    ui->label_4->setText(str1);
    int i = ui->horizontalScrollBar->value();
    if(i == 1)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg = image1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));
    }
    else if(i == 2)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg = image1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));
        QImage image2;
        QString s2 = "./images/2.jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_2->setPixmap(QPixmap::fromImage(resultImg2));
    }
    else
    {
        QImage image1;
        QString s1 = "./images/" + QString::number(i-2) + ".jpg";
        qDebug() << s1 << endl;
        image1.load(s1);
        QImage resultImg = image1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));
        QImage image2;
        QString s2 = "./images/" + QString::number(i-1) + ".jpg";
        qDebug() << s2 << endl;
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_2->setPixmap(QPixmap::fromImage(resultImg2));
        QImage image3;
        QString s3 = "./images/" + QString::number(i) + ".jpg";
        qDebug() << s3 << endl;
        image3.load(s3);
        QImage resultImg3 = image3.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_3->setPixmap(QPixmap::fromImage(resultImg3));
    }

}
