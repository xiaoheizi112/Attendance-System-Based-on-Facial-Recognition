#ifndef SELETWIN_H
#define SELETWIN_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class SeletWin;
}

class SeletWin : public QWidget
{
    Q_OBJECT

public:
    explicit SeletWin(QWidget *parent = nullptr);
    ~SeletWin();

private slots:
    void on_selectBtn_clicked();

private:
    Ui::SeletWin *ui;
    QSqlTableModel *model;
};

#endif // SELETWIN_H
