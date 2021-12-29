//
// Created by root on 2021/11/10.
//
#include <iostream>
#include "SCServo.h"
#include "thread"
using namespace std;
SMSBL sm;
extern int getSmP, getLSmP;
extern int setSmP, setLSmP, setES, setGraspForce;

void getSMPostion();
int writeSMPostion(int argc, char **argv,  unsigned int vel=300, unsigned int acc=0)
{
    if(argc<2){
        std::cout<< "argc error!"<<std::endl;
        return 0;
    }
    std::cout<< "serial:"<<argv[1]<<std::endl;
    if(!sm.begin(115200, argv[1])){
        std::cout<< "Failed to init smsbl motor!"<<std::endl;
        return 0;
    }
    ///thread that get RM postion
    thread getRSMPostion(getSMPostion);
    getRSMPostion.detach();

    int prePositon=0;
    unsigned int dev;
    while(1){
        dev=abs(setSmP-prePositon);
        prePositon=setLSmP;
        if(dev!=0){
            sm.WritePosEx(1, setSmP,vel, acc);//舵机(ID1)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P1=4095位置
            //std::cout<< "pos ="<<4095<<std::endl;
            usleep(dev/(50*vel)*1000+(50*vel)/(acc*100)*1000);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
        }


    }
    sm.end();
    return 1;
}

void getSMPostion(){
    //int Pos;
    //int Speed;
    //int Load;
    //int Voltage;
    //int Temper;
    //int Move;
    //int Current;
    if(sm.FeedBack(1)!=-1){
        getSmP = sm.ReadPos(-1);
        //Speed = sm.ReadSpeed(-1);
       // Load = sm.ReadLoad(-1);
        //Voltage = sm.ReadVoltage(-1);
       // Temper = sm.ReadTemper(-1);
       // Move = sm.ReadMove(-1);
       // Current = sm.ReadCurrent(-1);
        //std::cout<<"pos = "<<Pos<<" ";
       // std::cout<<"Speed = "<<Speed<<" ";
       // std::cout<<"Load = "<<Load<<" ";
       // std::cout<<"Voltage = "<<Voltage<<" ";
       // std::cout<<"Temper = "<<Temper<<" ";
        //std::cout<<"Move = "<<Move<<" ";
       // std::cout<<"Current = "<<Current<<std::endl;
        usleep(10*1000);
    }else{
        std::cout<< "read err ="<<std::endl;
        sleep(2);
    }
}
