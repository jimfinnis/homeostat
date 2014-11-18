#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow *MainWindow::inst = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    inst = this;
    ui->setupUi(this);
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer2,SIGNAL(timeout()),this,SLOT(tick2()));
    connect(ui->randButton,SIGNAL(clicked()),this,SLOT(randomize()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(resetGraphs()));
    ui->plotAB->setUnits(0,1);
    ui->plotAC->setUnits(0,2);
    ui->plotAD->setUnits(0,3);

    timer.start(20);
    timer2.start(2000);
    okToRandomize=false;
    changes = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}



static float convertInputDial(int v){
    float f = (float)v;
    return f/100.0f;
}



static int convertOutputDial(float f){
    f *= 100.0f;
    return (int)f;
}

static float convertInputSlider(int v){
    float f = (float)v;
    return f/1000.0f;
}

static int convertOutputSlider(float f){
    f *= 1000.0f;
    return (int)f;
}

void MainWindow::setModelFromWidgets()
{
    units[0].automatic = ui->automatic1->isChecked();
    units[0].inputs[0] = convertInputDial(ui->dialA1->value());
    units[0].inputs[1] = convertInputDial(ui->dialB1->value());
    units[0].inputs[2] = convertInputDial(ui->dialC1->value());
    units[0].inputs[3] = convertInputDial(ui->dialD1->value());
    units[0].output = convertInputSlider(ui->slider1->value());

    units[1].automatic = ui->automatic2->isChecked();
    units[1].inputs[0] = convertInputDial(ui->dialA2->value());
    units[1].inputs[1] = convertInputDial(ui->dialB2->value());
    units[1].inputs[2] = convertInputDial(ui->dialC2->value());
    units[1].inputs[3] = convertInputDial(ui->dialD2->value());
    units[1].output = convertInputSlider(ui->slider2->value());

    units[2].automatic = ui->automatic3->isChecked();
    units[2].inputs[0] = convertInputDial(ui->dialA3->value());
    units[2].inputs[1] = convertInputDial(ui->dialB3->value());
    units[2].inputs[2] = convertInputDial(ui->dialC3->value());
    units[2].inputs[3] = convertInputDial(ui->dialD3->value());
    units[2].output = convertInputSlider(ui->slider3->value());

    units[3].automatic = ui->automatic4->isChecked();
    units[3].inputs[0] = convertInputDial(ui->dialA4->value());
    units[3].inputs[1] = convertInputDial(ui->dialB4->value());
    units[3].inputs[2] = convertInputDial(ui->dialC4->value());
    units[3].inputs[3] = convertInputDial(ui->dialD4->value());
    units[3].output = convertInputSlider(ui->slider4->value());
}

void MainWindow::setWidgetsFromModel()
{
    ui->automatic1->setChecked(units[0].automatic);
    ui->dialA1->setValue(convertOutputDial(units[0].inputs[0]));
    ui->dialB1->setValue(convertOutputDial(units[0].inputs[1]));
    ui->dialC1->setValue(convertOutputDial(units[0].inputs[2]));
    ui->dialD1->setValue(convertOutputDial(units[0].inputs[3]));
    ui->slider1->setValue(convertOutputSlider(units[0].output));

    ui->automatic2->setChecked(units[1].automatic);
    ui->dialA2->setValue(convertOutputDial(units[1].inputs[0]));
    ui->dialB2->setValue(convertOutputDial(units[1].inputs[1]));
    ui->dialC2->setValue(convertOutputDial(units[1].inputs[2]));
    ui->dialD2->setValue(convertOutputDial(units[1].inputs[3]));
    ui->slider2->setValue(convertOutputSlider(units[1].output));

    ui->automatic3->setChecked(units[2].automatic);
    ui->dialA3->setValue(convertOutputDial(units[2].inputs[0]));
    ui->dialB3->setValue(convertOutputDial(units[2].inputs[1]));
    ui->dialC3->setValue(convertOutputDial(units[2].inputs[2]));
    ui->dialD3->setValue(convertOutputDial(units[2].inputs[3]));
    ui->slider3->setValue(convertOutputSlider(units[2].output));

    ui->automatic4->setChecked(units[3].automatic);
    ui->dialA4->setValue(convertOutputDial(units[3].inputs[0]));
    ui->dialB4->setValue(convertOutputDial(units[3].inputs[1]));
    ui->dialC4->setValue(convertOutputDial(units[3].inputs[2]));
    ui->dialD4->setValue(convertOutputDial(units[3].inputs[3]));
    ui->slider4->setValue(convertOutputSlider(units[3].output));
}

bool MainWindow::outOfRange(int n){
    float f = (units[n].output-0.5f)*2.0f;
    return fabsf(f)>0.7f;
}

#define STRENGTH 1.0f
void MainWindow::processUnit(int n){

    float newval = 0.5f; // target value

    for(int i=0;i<4;i++){
        newval -= units[n].inputs[i]*units[i].output;
    }

    units[n].output = 0.99f*units[n].output + 0.01f*newval;

}

inline float randfloat(){
    int i = rand()%14301;
    float f = ((float)i)/14301.0f;
    return (f*2.0f)-1.0f;
}


void MainWindow::tick()
{
    bool r = ui->running->isChecked();
    setModelFromWidgets();

    if(r){
        for(int i=0;i<4;i++)
            processUnit(i);
    }

    if(forceRand ||okToRandomize){
        for(int i=0;i<4;i++){
            if(forceRand || r && units[i].automatic && outOfRange(i)){
                changes++;
                for(int j=0;j<4;j++){
                    if(i!=j) // self-feedback has no uniselector
                        units[i].inputs[j]=randfloat();
                }
            }
        }
        okToRandomize=false;
        forceRand=false;

    }

    ui->plotAB->repaint();
    ui->plotAC->repaint();
    ui->plotAD->repaint();

    setWidgetsFromModel();
}

void MainWindow::tick2(){
    okToRandomize = true;
}

void MainWindow::resetGraphs()
{
    ui->plotAB->reset();
    ui->plotAC->reset();
    ui->plotAD->reset();
}

void MainWindow::randomize()
{
    forceRand=true;
}





