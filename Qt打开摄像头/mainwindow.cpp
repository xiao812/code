#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <QTimer>
#include "facedetect-dll.h"

// define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    cam = NULL;
    OPEN = true;
    /* 信号和槽 */
    connect(ui->OpenVideoBtn, SIGNAL(click()), this, SLOT(on_OpenCamerBtn_clicked()));      // 打开摄像头按钮
    connect(ui->SaveVideoBtn, SIGNAL(click()), this, SLOT(on_SaveVideoBtn_clicked()));      // 保存视频按钮
    connect(ui->CloseCamerBtn, SIGNAL(click()), this, SLOT(on_CloseCamerBtn_clicked()));    // 关闭摄像头按钮
    connect(ui->OpenVideoBtn, SIGNAL(click()), this, SLOT(on_OpenVideoBtn_clicked()));      // 打开视频按钮
    connect(timer, SIGNAL(timeout()), this, SLOT(getFrame()));
    connect(ui->CutImageBtn, SIGNAL(click()), this, SLOT(on_CutImageBtn_clicked()));        // 截图按钮
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OpenCamerBtn_clicked()
{
    cam.open(0);
    timer->start(50);
}

void MainWindow::getFrame()
{
    int * pResults = nullptr;
    //pBuffer is used in the detection functions.
    //If you call functions in multiple threads, please create one buffer for each thread!
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    if (!pBuffer)
    {
        fprintf(stderr, "Can not alloc buffer.\n");
    }

    int doLandmark = 0;
    cam >> frame;
    cvtColor(frame,gray, CV_BGR2GRAY);      // 转为灰度图
    pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
                1.2f, 3, 48, 0, doLandmark);

    printf("%d faces detected.\n", (pResults ? *pResults : 0));
    for (int i = 0; i < (pResults ? *pResults : 0); i++)
    {
          short * p = ((short*)(pResults + 1)) + 142 * i;
          int x = p[0];
          int y = p[1];
          int w = p[2];
          int h = p[3];
          int neighbors = p[4];
          int angle = p[5];

          printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
          rectangle(frame, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
          if (doLandmark)
          {
              for (int j = 0; j < 68; j++)
                  circle(frame, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
           }
     }
    QImage img1 = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();//个人测试时可以试试去掉.rgbSwapped()后的效果
    //将图片显示到QLabel上
    ui->label->setPixmap(QPixmap::fromImage(img1));
    waitKey(1000 / 30);
}
void MainWindow::on_CloseCamerBtn_clicked()
{
    timer->stop();
    cam.release();
    OPEN = false;
    write.release();
}

void MainWindow::on_SaveVideoBtn_clicked()
{
    if(!cam.isOpened())
        cam.open(0);
        //VideoWriter write("D:\\test.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(640, 480), true);
     write.open("D:\\test.avi",VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(640, 480), true);
     while(OPEN)
     {
         cam >> frame;
         //设置保存视频的格式为AVI，编码为MJPG
         write.write(frame);
         QImage img1 = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();//个人测试时可以试试去掉.rgbSwapped()后的效果
         //将图片显示到QLabel上
         ui->label->setPixmap(QPixmap::fromImage(img1));
         waitKey(1000 / 30);
    }
}

void MainWindow::on_OpenVideoBtn_clicked()
{
    VideoCapture video;
    Mat frame2;
    video.open("D:\\test.avi");
    while (video.isOpened())
    {
         video >> frame2;
         QImage img1 = QImage((const unsigned char*)frame2.data, frame2.cols, frame2.rows, QImage::Format_RGB888).rgbSwapped();//个人测试时可以试试去掉.rgbSwapped()后的效果
         //将图片显示到QLabel上
         ui->label->setPixmap(QPixmap::fromImage(img1));
         if (waitKey(40) == 27)  //WaitKey的参数相当于多少ms一帧，现在是40ms一帧，1s25帧
               break;                //按ESC就退出
    }
    video.release();
}

void MainWindow::on_CutImageBtn_clicked()
{
    cam >> cutframe;
    QImage img1 = QImage((const unsigned char*)cutframe.data, frame.cols, cutframe.rows, QImage::Format_RGB888).rgbSwapped();//个人测试时可以试试去掉.rgbSwapped()后的效果
    /*
    //将图片显示到QLabel上
    double width = img1.width();
    double height = img1.height();
    double radio = 0.0;
    if (width / 240 >= height / 160)
        radio = width / 240;
    else
        radio = height /160;
    double new_width = width / radio;
    double new_height = height / radio;
    QImage new_img1 = img1.scaled(new_width, new_height);
    */
    QImage resultImg = img1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(QPixmap::fromImage(resultImg));
}
