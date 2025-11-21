#include "seletwin.h"
#include "ui_seletwin.h"

SeletWin::SeletWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SeletWin)
{
    ui->setupUi(this);
    model = new QSqlTableModel();
}

SeletWin::~SeletWin()
{
    delete ui;
}

void SeletWin::on_selectBtn_clicked()
{
    if(ui->empRb->isChecked()){
        model->setTable("employee");//员工表
    }
    if(ui->attRb->isChecked()){
        model->setTable("attendance");//考勤表
    }

    //设置过滤器
    //model->setFilter("name = '张三'");
    //查询
    model->select();
    ui->tableView->setModel(model);
}

