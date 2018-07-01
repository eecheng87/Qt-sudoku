#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku_solver.h"
#include "sudoku_generator.h"
#include <Qt> //use for color
#include <QColor> // for color
#include <QLabel>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //sudoku_solver SOLVER;//declare a object of class sudoku_solver
    ui->setupUi(this);
    initTable();//generate sudoku table


    ui->label->setFont(QFont("Helvetica",20,QFont::Bold));
    ui->label->adjustSize();


    connect(ui->solve_button,SIGNAL(clicked()),this,SLOT(on_solve_button_clicked()));
    //when click button->solve problem
    connect(ui->generate_button,SIGNAL(clicked()),this,SLOT(on_generate_button_clicked()));
    //when click button->generate new puzzle
    connect(ui->check_button,SIGNAL(clicked()),this,SLOT(on_check_button_clicked()));
    //when click button->check the answer,and output the result
    connect(ui->clean_button,SIGNAL(clicked()),this,SLOT(on_clean_button_clicked()));
    //when click button->clean the whole cell become zero
    connect(ui->set_button,SIGNAL(clicked()),this,SLOT(on_set_button_clicked()));
    //let custom question more readable

    //my timer button , including pause, resume, start
    connect(ui->start_button,SIGNAL(clicked()),this,SLOT(setTimer()));
    connect(ui->pause_button,SIGNAL(clicked()),this,SLOT(pause()));
    connect(ui->resume_button,SIGNAL(clicked()),this,SLOT(resume()));
}
void MainWindow::initTable()
{
//set num of row and col, also hide horizontal and vertical title
//    ui->tableWidget -> setColumnCount(col);
 //   ui->tableWidget -> setRowCount(row);
    ui->tableWidget -> horizontalHeader() -> hide();
    ui->tableWidget -> verticalHeader() -> hide();
//set the size of each cell
    for(int i = 0 ; i < 9 ; ++i){
        ui->tableWidget->setColumnWidth(i,40);
        ui->tableWidget->setRowHeight(i,40);
    }
    //default all zero
    QString tmp = "0";
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(tmp));
        }

   // ui->tableWidget->addLine(0,0,80,80,Qpen(QT::green));
}
MainWindow::~MainWindow()
{
    delete ui;
}

int sudoku_solver::table_num[9][9]; //declare global variable, important!!
void MainWindow::on_solve_button_clicked(){

    // try to read data in sudoku table and store int my c++ variable
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            QTableWidgetItem *data = ui->tableWidget->item(i,j);
            sudoku_solver::table_num[i][j] = data->text().toInt(); //convert Qstring to c++ int

        }


    if(sudoku_solver::solve(sudoku_solver::table_num)){
        //try to write answer to qtablewidgetitem
        for(int i = 0 ; i<9 ; ++i)
            for(int j = 0 ; j<9 ; ++j){
                QString tmp = QString::number(sudoku_solver::table_num[i][j]);//convert c++ int to qstring
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(tmp));//convert qstring to item and write in
                 }
    }
    else
        qDebug()<<"fail";

    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            //set the cell which isn't zero become other color
            if(sudoku_generator::test_table[i][j]!=0)
                ui->tableWidget->item(i,j)->setBackground(Qt::darkGray);
            else
                ui->tableWidget->item(i,j)->setBackground(Qt::white);
        }
}

int sudoku_generator::test_table[9][9];
void MainWindow::on_generate_button_clicked()
{
    sudoku_generator::generate();
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){

            QString tmp = QString::number(sudoku_generator::test_table[i][j]);
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(tmp));
            //change cell's color if have non zero text
            if(sudoku_generator::test_table[i][j]!=0)
                ui->tableWidget->item(i,j)->setBackground(Qt::darkGray);
            else
                ui->tableWidget->item(i,j)->setBackground(Qt::white);
        }

}

//reset table for all zero
void MainWindow::on_clean_button_clicked()
{
    QString tmp = "0";
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(tmp));
        }
}

void MainWindow::on_check_button_clicked()
{
    // try to read data in sudoku table and store int my c++ variable
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            QTableWidgetItem *data = ui->tableWidget->item(i,j);
            sudoku_solver::table_num[i][j] = data->text().toInt(); //convert Qstring to c++ int
        }
    //expect table_num store full data and all correct
    //following try to check the answer whether correct
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            if(!sudoku_solver::all_safe(i,j,sudoku_solver::table_num)){
                ui->label->setText("Wrong answer,try again!");
                return;
            }
        }
    ui->label->setText("You Win!!");
    return;
}

void MainWindow::setTimer(){
       counter = 0;
       timer = new QTimer(this);
       connect(timer,SIGNAL(timeout()), this ,SLOT(TimeHandler()));
       timer->start(1000);  // 100 nanoseconds or 1 second interval
}
void MainWindow::TimeHandler(){
       counter++;
       ui->mytimer->setText(QString("Time: %1 seconds").arg(counter));
}
void MainWindow::pause() {
    int remaining = timer->remainingTime();
    timer->stop();
    timer->setInterval(remaining);
}

void MainWindow::resume() {
    timer->start(1000);
}
void MainWindow::reset(){

    counter=0;

}


void MainWindow::on_set_button_clicked()
{   int flag[9][9];
    for(int i = 0 ; i<9 ; ++i)
        for(int j = 0 ; j<9 ; ++j){
            QTableWidgetItem *data = ui->tableWidget->item(i,j);
            flag[i][j] = data->text().toInt(); //convert Qstring to c++ int
            if(flag[i][j]!=0)
                ui->tableWidget->item(i,j)->setBackground(Qt::darkGray);
            else
                ui->tableWidget->item(i,j)->setBackground(Qt::white);

        }
}
