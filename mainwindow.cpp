#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QFile>
#include <QtXml>
#include <QSound>
#include "pastwindow.h"
#include "setttings.h"

bool MainWindow::is_sound=true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //define the weekday hash
    weekday_hash[1]="Monday";
    weekday_hash[2]="Tuesday";
    weekday_hash[3]="Wednesday";
    weekday_hash[4]="Thursday";
    weekday_hash[5]="Friday";
    weekday_hash[6]="Saturday";
    weekday_hash[7]="Sunday";
    //show the current day of week
    ui->dayofweekLabel->setText(weekday_hash[QDate::currentDate().dayOfWeek()]);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//show past records
void MainWindow::on_backBtn_clicked()
{
    //every time open the window,make sure the data is new
    pastwindow *pastDlg=new pastwindow;
    pastDlg->setAttribute(Qt::WA_DeleteOnClose); //free memory when closed
    pastDlg->show();


}

//show settings
void MainWindow::on_settingBtn_clicked()
{
    //open the setting dlg
    setttings *settngDlg=new setttings;
    settngDlg->show();
}

//record
void MainWindow::on_recordBtn_clicked()
{
    //if there is empty editbox,return
    if(ui->morningEdit->toPlainText().isEmpty()
            ||ui->afternoonEdit->toPlainText().isEmpty()
            ||ui->eveningEdit->toPlainText().isEmpty())
    {
        QMessageBox::information(this,"啊哦~","请把记录填完>_<");
        return;
    }

    QFile file("res/record.xml");

    //if the file doesn't exist then create is, such the first time use or app injured
    if(!file.exists())
    {
        if(!file.open(QFile::WriteOnly|QFile::Truncate))
        {
            QMessageBox::information(this,"error","failed to write record");
            return;
        }
        QDomDocument doc;
        QDomProcessingInstruction instruction;
        instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
        doc.appendChild(instruction);

        //create just the root node
        QDomElement root=doc.createElement("Record");
        doc.appendChild(root);

        //write file
        QTextStream out_stream(&file);
        doc.save(out_stream,4);
        file.close();
    }

    //else then continue to add record content
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this,"error","failed to read record");
        return;
    }

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement();
    QDomElement day_record=doc.createElement("day_record");

    //create date, morning, afternoon, evening
    QDomElement date=doc.createElement("date");
    QDomText text;
    text=doc.createTextNode(QDate::currentDate().toString());
    date.appendChild(text);
    day_record.appendChild(date);

    QDomElement morning_content=doc.createElement("morning");
    text=doc.createTextNode(ui->morningEdit->toPlainText());
    morning_content.appendChild(text);
    day_record.appendChild(morning_content);

    QDomElement afternoon_content=doc.createElement("afternoon");
    text=doc.createTextNode(ui->afternoonEdit->toPlainText());
    afternoon_content.appendChild(text);
    day_record.appendChild(afternoon_content);

    QDomElement evening_content=doc.createElement("evening");
    text=doc.createTextNode(ui->eveningEdit->toPlainText());
    evening_content.appendChild(text);
    day_record.appendChild(evening_content);

    root.appendChild(day_record); //add day record

    //write file
    if(!file.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::information(this,"error","failed to write record");
        return;
    }

    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();

    //do something when record successfully
    ui->recordBtn->setText("record success");

    if(is_sound)
        QSound::play("res/success.wav"); //play sound if allowed,the sound res must put in file system,not the resource file

}

//when the edit changed,the button text recover
void MainWindow::on_morningEdit_textChanged()
{
    ui->recordBtn->setText("记录");
}

void MainWindow::on_afternoonEdit_textChanged()
{
    ui->recordBtn->setText("记录");
}

void MainWindow::on_eveningEdit_textChanged()
{
    ui->recordBtn->setText("记录");
}

void MainWindow::changeSoundState()
{
    is_sound=!is_sound; //change the sound state
}
