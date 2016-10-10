#ifndef ECLIPSETRADER_H
#define ECLIPSETRADER_H

#include <QWidget>

namespace Ui {
class EclipseTrader;
}

class EclipseTrader : public QWidget
{
    Q_OBJECT

public:
    explicit EclipseTrader(QWidget *parent = 0);
    ~EclipseTrader();

private:
    Ui::EclipseTrader *ui;
};

#endif // ECLIPSETRADER_H
