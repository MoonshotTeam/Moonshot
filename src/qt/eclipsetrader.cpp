#include "eclipsetrader.h"
#include "ui_eclipsetrader.h"

EclipseTrader::EclipseTrader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EclipseTrader)
{
    ui->setupUi(this);
}

EclipseTrader::~EclipseTrader()
{
    delete ui;
}
