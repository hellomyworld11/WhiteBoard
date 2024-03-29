#include "colorsel.h"
//#include "ui_colorsel.h"

colorSel::colorSel(QWidget *parent) :
    QColorDialog(parent)
   // ui(new Ui::colorSel)
{
    //ui->setupUi(this);
    //颜色对话框
    setOption(ColorDialogOption::ShowAlphaChannel,false);
}

colorSel::~colorSel()
{
   // delete ui;
    emit setval(currentColor());
}
