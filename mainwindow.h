#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

struct Unit {
    float output;
    float inputs[4];

    bool automatic;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow *getInstance(){
        return inst;
    }
    Unit units[4];
    bool forceRand;
    int changes;


private:
    Ui::MainWindow *ui;
    QTimer timer,timer2;
    static MainWindow *inst;

    void setModelFromWidgets();
    void setWidgetsFromModel();
    void processUnit(int n);
    bool outOfRange(int n);
    bool okToRandomize;

private slots:
    void tick();
    void tick2();
    void resetGraphs();
    void randomize();
};


#endif // MAINWINDOW_H
