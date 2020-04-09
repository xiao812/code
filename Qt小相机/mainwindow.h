#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display_cutpictures(int );
    void display_time(Mat );
    void get_face(Mat &frame);

private slots:
    void on_OpenCameraBtn_clicked();
    void on_CloseCameraBtn_clicked();
    void on_SaveVideoBtn_clicked();
    void on_OpenVideoBtn_clicked();
    void on_CutPictureBtn_clicked();
    void on_horizontalScrollBar_valueChanged(int value);
    void getFrame();

private:
    Ui::MainWindow *ui;
    Mat frame;
    Mat frame2;
    Mat gray;
    Mat cutframe;
    QTimer *timer;
    VideoCapture cam;
    VideoCapture video;
    VideoWriter write;
    bool OPEN;
};
#endif // MAINWINDOW_H
