#ifndef SELETWIN_H
#define SELETWIN_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class SeletWin;
}

/**
 * @brief SeletWin 类
 * 功能：数据查询窗口类，用于查询员工信息和考勤记录
 * 主要功能包括：
 * - 切换查询员工表或考勤表
 * - 显示查询结果在表格视图中
 */
class SeletWin : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     * 功能：初始化查询窗口，创建UI界面和数据模型
     */
    explicit SeletWin(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     * 功能：释放UI资源和其他动态分配的资源
     */
    ~SeletWin();

private slots:
    /**
     * @brief 查询按钮点击事件
     * 功能：根据用户选择查询员工表或考勤表，并在表格视图中显示结果
     * 触发时机：当用户点击查询按钮时调用
     */
    void on_selectBtn_clicked();

private:
    Ui::SeletWin *ui;         // UI界面指针
    QSqlTableModel *model;    // 数据库表模型，用于管理查询结果
};


#endif // SELETWIN_H
