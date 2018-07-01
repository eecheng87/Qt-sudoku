#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>//header for table
#include <QObject>
#include<QTableWidgetItem>
#include <QMainWindow>
#include<QTableWidget>
#include<QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initTable();

//for my timer
    QTimer * timer;
    qint32  counter;

private slots://default is private
    void on_solve_button_clicked();

    void on_generate_button_clicked();

    void on_clean_button_clicked();

    void on_check_button_clicked();

//for my timer
    void setTimer();
    void TimeHandler();
    void pause();
    void resume();
    void reset();


    void on_set_button_clicked();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
