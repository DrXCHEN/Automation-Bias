#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextBrowser>
#include <QTextStream>
#include <QDebug>
#include <dirent.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <QCoreApplication>
#include <string>
#include <QTime>

int status=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    currentpath = QCoreApplication::applicationDirPath();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

    if(loaded<=0)
    {
        string path;
  //      path = currentpath.toStdString();
  //      path = path+"/reading/";
        path = "C:/documents/";



        srand((unsigned int)time(0));
        for (int i=0; i<50;++i) randindex[i]=i+1;
        random_shuffle (randindex,randindex+9);
        random_shuffle (randindex+10,randindex+49);
//        for (int i=10; i<50;++i)
//        {
//            if(randindex[i]==37)
//            {
//                randindex[i] = randindex[10];
//            }
//            if(randindex[i]==47)
//            {
//                randindex[i] = randindex[49];
//            }
//        }
//        randindex[10]=37;
//        randindex[49]=47;

        dialog1 = new Dialog1(this);
        dialog1->show();
        int w = ui->graphicsView->width();
        int h = ui->graphicsView->height();

     //   string imgname = path+"pic"+std::to_string(randindex[loaded]+1)+"_1.png";
        string imgname = path+"pic"+std::to_string(randindex[loaded])+"_1.png";
        QPixmap pix;
        qDebug()<<QString::fromStdString(imgname);
        pix.load(QString::fromStdString(imgname));
        QGraphicsScene* scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        scene->addPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->graphicsView->show();


        Graphics_view_zoom* z = new Graphics_view_zoom(ui->graphicsView);
        z->set_modifiers(Qt::NoModifier);

     //   string filename = path+"info"+std::to_string(randindex[loaded]+1)+".txt";
        string filename = path+"info"+std::to_string(randindex[loaded])+".txt";
        qDebug()<<QString::fromStdString(filename);
        QFile file(QString::fromStdString(filename));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        QTextStream in(&file);
      //  qDebug()<<(in.readLine());
        ui->textBrowser->setText(in.readLine());
//        ui->textBrowser_3->setText(in.readLine());
        ui->textBrowser_4->setText(QString::number(loaded+1));
        ui->textBrowser->show();

        loaded = loaded+1;


        QFile logfile(fileName);
        if(!logfile.exists())
                  {
                     bool res2 = logfile.open(QIODevice::Append | QIODevice::Text );
                      qDebug() << "新建文件是否成功" << res2;
                   }
        else
                  {
                      qDebug() <<"文件存在" ;
                  }
        QTextStream out(&logfile);
        out<<"Operation: "<<"MSec"<<" "<<"ImageIndex"<<"\n";
        out<<"Load: "<<"0"<<" "<<randindex[loaded-1]<<"\n";
        loadtime = QTime::currentTime();
        logfile.close();

     }
     else
     {
        dialog1 = new Dialog1(this);
        dialog1->show();
     }


}



static bool isFastClick(QObject *target, int delayTimeMil)
{
    qlonglong lastTick = (target->property("tick").toLongLong());
    qlonglong tick = GetTickCount();
    target->setProperty("tick", tick);
    if (tick - lastTick > delayTimeMil)
    {
        return true;
    }
    return false;
}



void MainWindow::on_pushButton_2_clicked()
{

    if(loaded<=0)
    {
        dialog2 = new Dialog2(this);
        dialog2->show();
    }
    else
    {

        bool res =isFastClick(ui->pushButton_2,1000); //前面加上具体的按钮名称，后面是需要延时的时长
        if(res == false)                           //目前是1000ms
        {
            return;
        }

        QFile logfile(fileName);
        if(!logfile.exists())
                  {
                     bool res2 = logfile.open(QIODevice::Append | QIODevice::Text );
                      qDebug() << "新建文件是否成功" << res2;
                   }
        else
                  {
                      qDebug() <<"文件存在" ;
                  }
        QTime currenttime = QTime::currentTime();
        if (!logfile.open(QIODevice::Append | QIODevice::Text))
            return;
        int elapsed = loadtime.msecsTo(currenttime);
        QTextStream out(&logfile);
        out<<"Analysis: "<<elapsed<<" "<<randindex[loaded-1]<<"\n";
        logfile.close();

        status=1;
        ui->progressBar->setValue(0);
        progressTimer = new QTimer(this);
        progressTimer->start(100);
        connect(progressTimer,SIGNAL(timeout()),this,SLOT(updateProgress()));

    }
}

void MainWindow::updateProgress()
{
    int nCurrentValue = ui->progressBar->value();
    nCurrentValue = nCurrentValue+16;
    if (nCurrentValue >= 100)
    {
        ui->progressBar->setValue(100);
        progressTimer->stop();


        int w = ui->graphicsView->width();
        int h = ui->graphicsView->height();

        string path;
    //    path = currentpath.toStdString();
    //    path = path+"/reading/";
        path = "C:/documents/";

    //    string imgname = path+"pic"+std::to_string(randindex[loaded-1]+1)+"_2.png";
        string imgname = path+"pic"+std::to_string(randindex[loaded-1])+"_2.png";
        QPixmap pix;
        pix.load(QString::fromStdString(imgname));

        QGraphicsScene* scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        scene->addPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->graphicsView->show();

     //   string filename = path+"info"+std::to_string(randindex[loaded-1]+1)+".txt";
        string filename = path+"info"+std::to_string(randindex[loaded-1])+".txt";
        qDebug()<<QString::fromStdString(filename);
        QFile file(QString::fromStdString(filename));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        QTextStream in(&file);
        ui->textBrowser->setText(in.readLine());
        qDebug()<<(in.readLine());
//        ui->textBrowser_3->setText(in.readLine());
        ui->textBrowser_2->setText(in.readAll());
        ui->textBrowser->show();

    }
    ui->progressBar->setValue(nCurrentValue);

}

void MainWindow::on_pushButton_3_clicked()
{
    if(loaded<=0)
    {
        dialog2 = new Dialog2(this);
        dialog2->show();
    }
    else
    {

        string path;
    //    path = currentpath.toStdString();
    //    path = path+"/reading/";
        path = "C:/documents/";

        ui->textBrowser->document()->clear();

        if(loaded<50)
        {
            QFile logfile(fileName);
            if(!logfile.exists())
                      {
                         bool res2 = logfile.open(QIODevice::Append | QIODevice::Text );
                          qDebug() << "新建文件是否成功" << res2;
                       }
            else
                      {
                          qDebug() <<"文件存在" ;
                      }
            QTime currenttime = QTime::currentTime();
            if (!logfile.open(QIODevice::Append | QIODevice::Text))
                return;
            int elapsed = loadtime.msecsTo(currenttime);
            QTextStream out(&logfile);
            out<<"Next: "<<elapsed<<" "<<randindex[loaded-1]<<"\n";
            logfile.close();


            status=0;
            int w = ui->graphicsView->width();
            int h = ui->graphicsView->height();

            qDebug()<<loaded;
       //     string imgname = path+"pic"+std::to_string(randindex[loaded]+1)+"_1.png";
            string imgname = path+"pic"+std::to_string(randindex[loaded])+"_1.png";
            QPixmap pix;
            qDebug()<<QString::fromStdString(imgname);
            pix.load(QString::fromStdString(imgname));
            QGraphicsScene* scene = new QGraphicsScene(this);
            ui->graphicsView->setScene(scene);
            scene->addPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            ui->graphicsView->show();

        //    string filename = path+"info"+std::to_string(randindex[loaded]+1)+".txt";
            string filename = path+"info"+std::to_string(randindex[loaded])+".txt";
            qDebug()<<QString::fromStdString(filename);
            QFile file(QString::fromStdString(filename));
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"Can't open the file!"<<endl;
            }
            QTextStream in(&file);

            ui->textBrowser->setText(in.readLine());
            qDebug()<<(in.readLine());
//            ui->textBrowser_3->setText(in.readLine());
            ui->textBrowser_2->setText("");
            ui->textBrowser_4->setText(QString::number(loaded+1));
//            ui->textBrowser_4->setText(QString::number(randindex[loaded]));
            ui->textBrowser->show();

            ui->progressBar->setValue(0);


            loaded = loaded+1;

        }
        else
        {
            dialog3 = new Dialog3(this);
            dialog3->show();
        }

    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(loaded<=0)
    {
        dialog2 = new Dialog2(this);
        dialog2->show();
    }
    if(loaded==1)
    {
        dialog4 = new Dialog4(this);
        dialog4->show();
    }
    if(loaded>1)
    {
        QFile logfile(fileName);
        if(!logfile.exists())
                  {
                     bool res2 = logfile.open(QIODevice::Append | QIODevice::Text );
                      qDebug() << "新建文件是否成功" << res2;
                   }
        else
                  {
                      qDebug() <<"文件存在" ;
                  }
        QTime currenttime = QTime::currentTime();
        if (!logfile.open(QIODevice::Append | QIODevice::Text))
            return;
        int elapsed = loadtime.msecsTo(currenttime);
        QTextStream out(&logfile);
        out<<"Previous: "<<elapsed<<" "<<randindex[loaded-1]<<"\n";
        logfile.close();


        status=0;
        loaded=loaded-1;
        string path;
    //    path = currentpath.toStdString();
    //    path = path+"/reading/";
        path = "C:/documents/";
        ui->textBrowser->document()->clear();
        int w = ui->graphicsView->width();
        int h = ui->graphicsView->height();

        qDebug()<<loaded;
     //   string imgname = path+"pic"+std::to_string(randindex[loaded-1]+1)+"_1.png";
        string imgname = path+"pic"+std::to_string(randindex[loaded-1])+"_1.png";
        QPixmap pix;
        qDebug()<<QString::fromStdString(imgname);
        pix.load(QString::fromStdString(imgname));
        QGraphicsScene* scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        scene->addPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->graphicsView->show();

     //   string filename = path+"info"+std::to_string(randindex[loaded-1]+1)+".txt";
        string filename = path+"info"+std::to_string(randindex[loaded-1])+".txt";
        qDebug()<<QString::fromStdString(filename);
        QFile file(QString::fromStdString(filename));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        QTextStream in(&file);
        ui->textBrowser->setText(in.readLine());
        qDebug()<<(in.readLine());
//        ui->textBrowser_3->setText(in.readLine());
        ui->textBrowser_2->setText("");
        ui->textBrowser_4->setText(QString::number(loaded));
        ui->textBrowser->show();

        ui->progressBar->setValue(0);

    }


}

void MainWindow::on_pushButton_5_clicked()
{
    if(loaded<=0)
    {
        dialog2 = new Dialog2(this);
        dialog2->show();
    }
    else
    {
        if(status==0)
        {
            dialog5 = new Dialog5(this);
            dialog5->show();
        }
        else
        {
            QFile logfile(fileName);
            if(!logfile.exists())
                      {
                         bool res2 = logfile.open(QIODevice::Append | QIODevice::Text );
                          qDebug() << "新建文件是否成功" << res2;
                       }
            else
                      {
                          qDebug() <<"文件存在" ;
                      }
            QTime currenttime = QTime::currentTime();
            if (!logfile.open(QIODevice::Append | QIODevice::Text))
                return;
            int elapsed = loadtime.msecsTo(currenttime);
            QTextStream out(&logfile);
            out<<"Toggle Heatmap: "<<elapsed<<" "<<randindex[loaded-1]<<"\n";
            logfile.close();


            if(status==1)
            {
               int w = ui->graphicsView->width();
               int h = ui->graphicsView->height();

               string path;
            //  path = currentpath.toStdString();
             //  path = path+"/reading/";
               path = "C:/documents/";

               string imgname = path+"pic"+std::to_string(randindex[loaded-1])+"_1.png";

               if(loaded>49)
               {
               //    imgname = path+"pic"+std::to_string(randindex[49]+1)+"_1.png";
                   imgname = path+"pic"+std::to_string(randindex[49])+"_1.png";
               }
           //    qDebug()<< QString::number(loaded);
               QPixmap pix;
               pix.load(QString::fromStdString(imgname));

               QGraphicsScene* scene = new QGraphicsScene(this);
               ui->graphicsView->setScene(scene);
               scene->addPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
               ui->graphicsView->show();
            }
            if(status==2)
            {
               int w = ui->graphicsView->width();
               int h = ui->graphicsView->height();

               string path;
           //    path = currentpath.toStdString();
           //    path = path+"/reading/";
               path = "C:/documents/";
               string imgname = path+"pic"+std::to_string(randindex[loaded-1])+"_2.png";
               if(loaded>49)
               {
               //    imgname = path+"pic"+std::to_string(randindex[49]+1)+"_2.png";
                   imgname = path+"pic"+std::to_string(randindex[49])+"_2.png";
               }
           //    qDebug()<< QString::number(loaded);
               QPixmap pix;
               pix.load(QString::fromStdString(imgname));

               QGraphicsScene* scene = new QGraphicsScene(this);
               ui->graphicsView->setScene(scene);
               scene->addPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
               ui->graphicsView->show();
            }
            status=3-status;
        }


    }

}
