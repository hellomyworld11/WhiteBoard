#ifndef COLORSELECT_H
#define COLORSELECT_H

#include <QWidget>

namespace Ui {
class colorSelect;
}

class colorSelect : public QWidget
{
    Q_OBJECT

public:
    explicit colorSelect(QWidget *parent = nullptr);
    ~colorSelect();

private:
    Ui::colorSelect *ui;
};

#endif // COLORSELECT_H
