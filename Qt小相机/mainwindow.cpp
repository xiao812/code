#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <QTimer>
#include <QDebug>
#include <QDir>
#include "facedetect-dll.h"

// define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    cam = NULL;
    video = NULL;
    OPEN = true;
    // 信号和槽
    // 打开摄像头
    connect(ui->OpenCameraBtn, SIGNAL(click()), this, SLOT(on_OpenCameraBtn_clicked()));
    // 关闭摄像头
    connect(ui->CloseCameraBtn, SIGNAL(click()), this, SLOT(on_CloseCameraBtn_clicked()));
    // 保存视频
    connect(ui->SaveVideoBtn, SIGNAL(click()), this, SLOT(on_SaveVideoBtn_clicked()));
    // 播放视频
    connect(ui->OpenVideoBtn, SIGNAL(click()), this, SLOT(on_OpenVideoBtn_clicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(getFrame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OpenCameraBtn_clicked()
{
    cam.open(0);
    timer->start(50);
}

void MainWindow::getFrame()
{

    cam >> frame;
    get_face(frame);            // 人脸识别
    display_time(frame);        // 时间打标
    QImage img1 = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
    //将图片显示到QLabel上
    ui->label_2->setPixmap(QPixmap::fromImage(img1));
    waitKey(1000 / 30);
    ui->label_8->setText("show");
}
void MainWindow::on_CloseCameraBtn_clicked()
{
        ui->label_8->setText("video close");
        timer->stop();
        cam.release();
        OPEN = false;
        write.release();
        video.release();

}

void MainWindow::on_SaveVideoBtn_clicked()
{
    OPEN = true;
    if(cam.isOpened())
    {
        write.open("./video/test.avi",VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(640, 480), true);
        while(OPEN)
        {
            cam >> frame;
            get_face(frame);
            display_time(frame);
            //设置保存视频的格式为AVI，编码为MJPG
            write.write(frame);
            QImage img1 = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();//个人测试时可以试试去掉.rgbSwapped()后的效果
            //将图片显示到QLabel上
            ui->label_2->setPixmap(QPixmap::fromImage(img1));
            ui->label_8->setText(tr("Saving"));
            waitKey(1000 / 30);
        }
    }
    else
    {
        qDebug() << "cannot write" <<endl;
    }
}

void MainWindow::on_OpenVideoBtn_clicked()
{
    if(!video.isOpened())
        ui->label_8->setText(tr("play back"));
        video.open("./video/test.avi");
        while (1)
        {
             video >> frame2;
             QImage img1 = QImage((const unsigned char*)frame2.data, frame2.cols, frame2.rows, QImage::Format_RGB888).rgbSwapped();//个人测试时可以试试去掉.rgbSwapped()后的效果
             //将图片显示到QLabel上
             ui->label_3->setPixmap(QPixmap::fromImage(img1));
             if (waitKey(40) == 27)  //WaitKey的参数相当于多少ms一帧，现在是40ms一帧，1s25帧
                 break;                //按ESC就退出
        }
}

void MainWindow::on_CutPictureBtn_clicked()
{
    QString ImagePath = "./images";
    QDir dir(ImagePath);
    QStringList ImageList;
    ImageList << "*.jpg";
    dir.setNameFilters(ImageList);
    // 获取文件夹下所有图片文件数
    int sum = dir.count();
    if(!cam.isOpened())
        cam.open(0);
    cam >> cutframe;
    get_face(cutframe);
    display_time(cutframe);
    QImage img1 = QImage((const unsigned char*)cutframe.data, frame.cols, cutframe.rows, QImage::Format_RGB888).rgbSwapped();
    sum = sum + 1;
    QString s1 = "./images/" +  QString::number(sum) + ".jpg";
    img1.save(s1,"jpg",100);
    ui->horizontalScrollBar->setMaximum(sum);
    ui->horizontalScrollBar->setValue(sum);
    display_cutpictures(sum);
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    if(value == 0)
    {

    }
    int i = ui->horizontalScrollBar->value();
    if(i == 1)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));
    }
    else if (i == 2)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));

        QImage image2;
        QString s2 = "./images/2.jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_5->setPixmap(QPixmap::fromImage(resultImg2));
    }
    else if (i == 3)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));

        QImage image2;
        QString s2 = "./images/2.jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_5->setPixmap(QPixmap::fromImage(resultImg2));

        QImage image3;
        QString s3 = "./images/3.jpg";
        image3.load(s3);
        QImage resultImg3 = image3.scaled(ui->label_6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_6->setPixmap(QPixmap::fromImage(resultImg3));
    }
    else
    {
        QImage image1;
        QString s1 = "./images/" + QString::number(i - 3) + ".jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));

        QImage image2;
        QString s2 = "./images/" + QString::number(i - 2) + ".jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_5->setPixmap(QPixmap::fromImage(resultImg2));

        QImage image3;
        QString s3 = "./images/" + QString::number(i - 1) + ".jpg";
        image3.load(s3);
        QImage resultImg3 = image3.scaled(ui->label_6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_6->setPixmap(QPixmap::fromImage(resultImg3));

        QImage image4;
        QString s4 = "./images/" + QString::number(i) + ".jpg";
        image4.load(s4);
        QImage resultImg4 = image4.scaled(ui->label_7->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_7->setPixmap(QPixmap::fromImage(resultImg4));
    }
}

void MainWindow::display_cutpictures(int sum)
{
    if(sum == 1)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));
    }
    else if (sum == 2)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));

        QImage image2;
        QString s2 = "./images/2.jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_5->setPixmap(QPixmap::fromImage(resultImg2));
    }
    else if (sum == 3)
    {
        QImage image1;
        QString s1 = "./images/1.jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));

        QImage image2;
        QString s2 = "./images/2.jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_5->setPixmap(QPixmap::fromImage(resultImg2));

        QImage image3;
        QString s3 = "./images/3.jpg";
        image3.load(s3);
        QImage resultImg3 = image3.scaled(ui->label_6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_6->setPixmap(QPixmap::fromImage(resultImg3));
    }
    else
    {
        QImage image1;
        QString s1 = "./images/" + QString::number(sum - 3) + ".jpg";
        image1.load(s1);
        QImage resultImg1 = image1.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_4->setPixmap(QPixmap::fromImage(resultImg1));

        QImage image2;
        QString s2 = "./images/" + QString::number(sum - 2) + ".jpg";
        image2.load(s2);
        QImage resultImg2 = image2.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_5->setPixmap(QPixmap::fromImage(resultImg2));

        QImage image3;
        QString s3 = "./images/" + QString::number(sum - 1) + ".jpg";
        image3.load(s3);
        QImage resultImg3 = image3.scaled(ui->label_6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_6->setPixmap(QPixmap::fromImage(resultImg3));

        QImage image4;
        QString s4 = "./images/" + QString::number(sum) + ".jpg";
        image4.load(s4);
        QImage resultImg4 = image4.scaled(ui->label_7->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_7->setPixmap(QPixmap::fromImage(resultImg4));
    }
}

void MainWindow::display_time(Mat m)
{
    cv::Point p = cv::Point(300, 20);
    struct tm t;   //tm结构指针
    time_t now;  //声明time_t类型变量
    char ch[64];

    time(&now);      //获取系统日期和时间
    localtime_s(&t, &now);//获取当地日期和时间
    int len = strftime(ch, sizeof(ch), "%Y-%m-%d %H:%M:%S", &t); //年-月-日 时-分-秒
    ch[len] = '\0';
    putText(m, ch, p, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 200, 200), 1);
}

void MainWindow::get_face(Mat &frame)
{
    int * pResults = nullptr;
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    if (!pBuffer)
    {
         fprintf(stderr, "Can not alloc buffer.\n");
    }

    int doLandmark = 0;
    cvtColor(frame,gray, CV_BGR2GRAY);      // 转为灰度图
    pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
                        1.2f, 3, 48, 0, doLandmark);
    for (int i = 0; i < (pResults ? *pResults : 0); i++)
    {
        short * p = ((short*)(pResults + 1)) + 142 * i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];
        rectangle(frame, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
    }
}
