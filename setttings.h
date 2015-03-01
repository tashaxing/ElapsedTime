#ifndef SETTTINGS_H
#define SETTTINGS_H

#include <QWidget>

namespace Ui {
class setttings;
}

class setttings : public QWidget
{
    Q_OBJECT

public:
    explicit setttings(QWidget *parent = 0);
    ~setttings();

private slots:
    void on_sound_checkBox_clicked();

    void on_urlBtn_clicked();

    void on_clearBtn_clicked();

private:
    Ui::setttings *ui;
};

#endif // SETTTINGS_H
