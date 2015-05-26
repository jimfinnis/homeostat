/**
 * @file h2.cpp
 * @brief  Brief description of file.
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <limits.h>
#include <float.h>

#include <random>

#define EPSILON 0.000001

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(-1,1);

inline float randfloat(){
    return dis(gen);
}

int unitct;

struct Unit {
    double output;
    double lastOutput;
    double *weights; // -1 to 1
    int idx;
    Unit(int i){
        weights = new double[unitct];
        idx=-1;
        randomise(); // first time *all* randomise
        idx=i;
        output=0.5;
        lastOutput=output;
    }
    ~Unit(){
        delete [] weights;
    }
    
    void randomise(){
        for(int i=0;i<unitct;i++){
            // my own weight does not randomize after first
//            if(i!=idx)
                weights[i]=randfloat();
        }
    }
    
    bool isInRange(){
        double q = (output-0.5)*2.0;
        return fabs(q)<0.7;
    }
    
    bool isSettled(){
        return fabs(lastOutput-output)<EPSILON && isInRange();
    }
    
    void update(bool check);
};

double connstr = 1;
double visc = 0.9;
Unit *units[10];

void Unit::update(bool check){
    double newval=0.5;
    lastOutput = output;
    
    for(int i=0;i<unitct;i++){
        newval -= units[i]->output * weights[i] * connstr;
    }
    
    double smooth = (1.0-visc)*0.1;
    output = (1.0-smooth)*output + smooth*newval;
    
    if(output>1)output=1;
    if(output<0)output=0;
    
    if(check && !isInRange())
        randomise();
    
}
              
void update(bool check){
    for(int i=0;i<unitct;i++)
        units[i]->update(check);
}

int run(int u,double c){
    
    connstr = c;
    
    unitct=u;
    
    int i,count=0;
    for(i=0;i<unitct;i++)
        units[i] = new Unit(i);
    
    for(i=0;;i++){
        update((i%1000)==0);
        
        bool allsettled=true;
        for(int i=0;i<unitct;i++){
            //printf("%f%s",units[i]->output,i==3?"\n":",");
            if(!units[i]->isSettled())
                allsettled=false;
            
        }
        if(allsettled){
            count++;
            for(int i=0;i<unitct;i++){
                units[i]->randomise();
            }
            if(count==20)break;
        }
    }
    for(int j=0;j<unitct;j++)
        delete units[j];
    return i;
}    


// varying conn strength

int main(int argc,char *argv[]){
    printf("conn,count\n");
    int units = atoi(argv[1]);
    for(double d=0.1;d<10;d+=0.01){
        long q=0;
        for(int i=0;i<5;i++){
            q+=run(units,d);
        }
        printf("%f,%ld\n",d,q/5);
    }
}

/* varying units
int main(int argc,char *argv[]){
    printf("conn,count\n");
    for(int d=2;d<10;d++){
        for(int i=0;i<10;i++){
            long q=run(d,1);
            printf("%d,%ld\n",d,q);
        }
    }
}

*/
