#include "setttings.h"
#include "ui_setttings.h"
#include <QUrl>
#include <QFile>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProcess>
#include "mainwindow.h"


setttings::setttings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setttings)
{
    ui->setupUi(this);
    ui->sound_checkBox->setChecked(true);
    connect(ui->sound_checkBox,SIGNAL(clicked()),(new MainWindow),SLOT(changeSoundState())); //bind the signal and static public slot between windows
}

setttings::~setttings()
{
    delete ui;
}

void setttings::on_sound_checkBox_clicked()
{

    //sound on or off,nothing here
}

void setttings::on_urlBtn_clicked()
{
    //link to my csdn blog
    QUrl url="http://blog.csdn.net/u012234115";
    QDesktopServices::openUrl(url);

}

void setttings::on_clearBtn_clicked()
{
    //clear the record.xml file
    QFile file("res/record.xml");
    if(file.exists())
    {
        if(!file.remove())
            QMessageBox::information(this,"error","clear the record failed!");
        else
            QMessageBox::information(this,"success","记录清除成功");

    }
}
