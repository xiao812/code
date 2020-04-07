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

private slots:
    void on_OpenCamerBtn_clicked();
    void on_CloseCamerBtn_clicked();
    void on_SaveVideoBtn_clicked();
    void on_OpenVideoBtn_clicked();
    void getFrame();
    void on_CutImageBtn_clicked();

private:
    Ui::MainWindow *ui;
    Mat frame;
    Mat gray;
    Mat cutframe;
    QTimer *timer;
    VideoCapture cam;
    VideoWriter write;
    bool OPEN;
};
#endif // MAINWINDOW_H
