#include "pastwindow.h"
#include "ui_pastwindow.h"
#include <QMessageBox>
#include <QtXml>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>

pastwindow::pastwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pastwindow)
{
    ui->setupUi(this);

    //initialize table
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers<<"date"<<"morning"<<"afternoon"<<"evening";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //fill the table width
    //ui->tableWidget->resizeColumnsToContents();  //this doesn't work,don't know why

    ui->tableWidget->setColumnWidth(0,100); //set the column width
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);

    ui->tableWidget->setStyleSheet("selection-background-color:#a020f0"); //set the selected color

    //parse xml and insert to table


    QFile file("res/record.xml");
    //if the file doesn't exist then create is, such as the first time use or app injured
    if(!file.exists())
    {
        QMessageBox::information(this,"error","there is no record yet!");
        return;
    }
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
    QDomElement elem=root.firstChildElement();
    int row=0,col=0;
    while(!elem.isNull())
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount()); //add row
//        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QDomElement e=elem.firstChildElement();
        while(!e.isNull())
        {
            ui->tableWidget->setItem(0,col,new QTableWidgetItem(e.text()));//it seems the ui tablewidget will do it automatically,so use 0

            e=e.nextSiblingElement();        

            col++;
        }
        elem=elem.nextSiblingElement();
        row++;

    }


    //set the row color,this time the row and col is valid
    //every 7 rows for one color
    bool row_flag=false;
    for(row=0;row<ui->tableWidget->rowCount();row++)
    {
        if(!(row%7)&&row!=0)
            row_flag=!row_flag;
        for(col=0;col<ui->tableWidget->columnCount();col++)
        {
            if(!row_flag)
                ui->tableWidget->item(row,col)->setBackgroundColor(QColor(255,240,245));
            else
                ui->tableWidget->item(row,col)->setBackgroundColor(QColor(193,255,193));

            ui->tableWidget->item(row,col)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter); //set the item text alignment
        }
    }




}

pastwindow::~pastwindow()
{
    delete ui;
}

//export the PDF file
void pastwindow::on_pdfwriterBtn_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
//    printer.setResolution(QPrinter::HighResolution); //纯文字输出不要设置这一项
    printer.setPageSize(QPrinter::A4);  //默认A4，可不设置
    QString filepath=QFileDialog::getSaveFileName(this,"export pdf","D:/时光记录.pdf","*.pdf");
    if(!filepath.isEmpty())
    {
        if(QFileInfo(filepath).suffix().isEmpty())
        {
            filepath.append(".pdf");
        }
    }
    printer.setOutputFileName(filepath);

    QPainter painter;
    painter.begin(&printer);

    //get the text for write
    QFile file("res/record.xml");
    if(!file.exists())
    {
        QMessageBox::information(this,"error","there is no record yet!");
        return;
    }
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
    QDomElement elem=root.firstChildElement();
    int px=10,py=10; //init the position
    painter.setPen(Qt::green);
    painter.drawText(px,py,"时光记录");
    py+=20;
    painter.drawText(px,py,"========================================");
    painter.setPen(Qt::black);
    py+=30;
    while(!elem.isNull())
    {
        QDomElement e=elem.firstChildElement();
        while(!e.isNull())
        {
            painter.drawText(px,py,e.tagName()+":"+e.text());
            e=e.nextSiblingElement();
            py+=20;
            if(py>1000)
            {
                printer.newPage();
                py=40;
            }
        }
        elem=elem.nextSiblingElement();
        painter.setPen(Qt::red);
        painter.drawText(px,py,"----------------------------------------");
        py+=20;
        painter.setPen(Qt::black);
    }
    painter.end();
}
