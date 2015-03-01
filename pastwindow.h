#ifndef PASTWINDOW_H
#define PASTWINDOW_H

#include <QWidget>

namespace Ui {
class pastwindow;
}

class pastwindow : public QWidget
{
    Q_OBJECT

public:
    explicit pastwindow(QWidget *parent = 0);
    ~pastwindow();

private slots:
    void on_pdfwriterBtn_clicked();


private:
    Ui::pastwindow *ui;

};

#endif // PASTWINDOW_H
