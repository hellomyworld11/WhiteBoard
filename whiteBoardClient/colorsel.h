#ifndef COLORSEL_H
#define COLORSEL_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class colorSel;
}

class colorSel : public QColorDialog
{
    Q_OBJECT

public:
    explicit colorSel(QWidget *parent = nullptr);
    ~colorSel();
signals:
    void setval(QColor color);
private:
    //Ui::colorSel *ui;
};

#endif // COLORSEL_H
