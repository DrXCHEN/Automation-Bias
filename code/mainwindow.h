#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"
#include "dialog4.h"
#include "dialog5.h"
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QProgressBar>
#include <vector>
#include "Graphics_view_zoom.h"
#include <QFile>
using namespace std;

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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateProgress();


    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QString currentpath;
    Dialog1 *dialog1;
    Dialog2 *dialog2;
    Dialog3 *dialog3;
    Dialog4 *dialog4;
    Dialog5 *dialog5;
    QGraphicsItem *item;
    Graphics_view_zoom* z;
    QGraphicsScene *scene;
    QProgressBar *progress;
    QTimer *progressTimer;


    QTime loadtime;
    QDateTime starttime = QDateTime::currentDateTime();
    QString strTime = starttime.toString("MM-dd-hh-mm-ss");
    QString fileName = "C:/documents/"+strTime+".txt";


    int loaded = 0;
    int randindex[50];


};
#endif // MAINWINDOW_H
