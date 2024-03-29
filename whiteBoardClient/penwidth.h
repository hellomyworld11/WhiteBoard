#ifndef PENWIDTH_H
#define PENWIDTH_H

#include <QDialog>

namespace Ui {
class PenWidth;
}

//笔粗 对话框
class PenWidth : public QDialog
{
    Q_OBJECT
public:
    explicit PenWidth(int width = 10, QWidget *parent = nullptr);
    ~PenWidth();
signals:
    void setval(int ival);
private slots:
    void on_horizontalSlider_valueChanged(int value);
private:
    Ui::PenWidth *ui;
    int dWidth;
};

#endif // PENWIDTH_H
