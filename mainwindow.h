#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_backBtn_clicked();

    void on_settingBtn_clicked();

    void on_recordBtn_clicked();



    void on_morningEdit_textChanged();

    void on_afternoonEdit_textChanged();

    void on_eveningEdit_textChanged();

public slots:
    static void changeSoundState();  //slots to change sound state,set to static for global use


private:
    Ui::MainWindow *ui;
    QHash<int,QString> weekday_hash; //hash for weekday from int to string
    static bool is_sound; //the sound effect state,set to static for global use
};

#endif // MAINWINDOW_H
