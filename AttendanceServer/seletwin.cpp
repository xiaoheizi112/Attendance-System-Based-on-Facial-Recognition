#include "seletwin.h"
#include "ui_seletwin.h"

/**
 * @brief 构造函数
 * @param parent 父窗口指针
 * 功能：
 * - 初始化查询窗口的UI界面
 * - 创建数据库表模型
 * - 设置窗口的基本属性
 */
SeletWin::SeletWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SeletWin)
{
    ui->setupUi(this);
    model = new QSqlTableModel(); // 创建数据库表模型，用于数据查询和显示
}

SeletWin::~SeletWin()
{
    delete ui; // 释放UI资源
}

/**
 * @brief 查询按钮点击事件处理函数
 * 功能：
 * - 根据用户选择的单选按钮确定要查询的数据表（员工表或考勤表）
 * - 设置数据库模型的表格
 * - 执行查询操作
 * - 将查询结果显示在表格视图中
 * 触发时机：
 * - 当用户点击查询按钮时调用
 */
void SeletWin::on_selectBtn_clicked()
{
    if(ui->empRb->isChecked()){
        model->setTable("employee");//设置为员工表
    }
    if(ui->attRb->isChecked()){
        model->setTable("attendance");//设置为考勤表
    }

    //设置过滤器（目前注释掉，可根据需要启用）
    //model->setFilter("name = '张三'");
    
    //执行查询
    model->select();
    
    //将查询结果设置到表格视图中显示
    ui->tableView->setModel(model);
}

