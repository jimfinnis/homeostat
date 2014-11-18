#ifndef PLOT2D_H
#define PLOT2D_H

#include <QWidget>
#include <QImage>


class Plot2D : public QWidget
{
    Q_OBJECT
public:
    explicit Plot2D(QWidget *parent = 0);
    void setUnits(int x,int y){
        xunit = x;
        yunit = y;
    }
    void reset();

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
private:
    int xunit,yunit;
    QImage *buf;
};

#endif // PLOT2D_H
