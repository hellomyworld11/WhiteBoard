#include "colorselect.h"
#include "ui_colorSelect.h"

colorSelect::colorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::colorSelect)
{
    ui->setupUi(this);
}

colorSelect::~colorSelect()
{
    delete ui;
}
