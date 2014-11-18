#include "plot2d.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPaintEvent>

Plot2D::Plot2D(QWidget *parent) :
    QWidget(parent)
{
    buf=NULL;
}

static unsigned long cols[]={
    0xffffffff,
    0xff,
    0xff00,
    0xffff,
    0xff0000,
    0xff00ff,
    0xffff00
};
#define NUMCOLS 7

void Plot2D::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    MainWindow *m = MainWindow::getInstance();

    if(!buf){
        buf = new QImage(width(),height(),QImage::Format_RGB32);
        buf->fill(0);
    }

    float valx = m->units[xunit].output;
    float valy = m->units[yunit].output;

    valx = valx*(float)(width()-4)+2;
    valy = valy*(float)(height()-4)+2;

    buf->setPixel(QPoint(valx,valy),cols[m->changes % NUMCOLS]);

    QRect dirty = e->rect();
    p.drawImage(dirty,*buf,dirty);

}

void Plot2D::reset()
{
    if(buf){
        buf->fill(0);
    }
}
