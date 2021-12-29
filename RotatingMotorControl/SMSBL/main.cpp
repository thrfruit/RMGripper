/*
以下例子在SMS40BL中测试通过，舵机出厂速度单位为0.732rpm，舵机机运行速度V=80
如果使用的出厂速度单位是0.0146rpm，则速度改为V=4000，延时公式T=[(P1-P0)/V]*1000+[V/(A*100)]*1000
*/

#include <iostream>
#include <string>
#include "SCServo.h"
#include "thread"
using namespace std;
SMSBL sm;

void writePosition();
void getPosition();

int main(int argc, char **argv)
{
    /*
	if(argc<2){
        std::cout<< "argc error!"<<std::endl;
        return 0;
	}
     */
    const char * port="/dev/ttyUSB0";
    std::cout<< "serial:"<<port<<std::endl;
    if(!sm.begin(115200, port)){
        std::cout<< "Failed to init smsbl motor!"<<std::endl;
        return 0;
    }

//    thread t(getPosition);
//    t.detach();

    writePosition();



    sm.end();
    return 1;
}

void writePosition(){
    int setSmP;
    string po;
    while(1){

        std::cout<<"input position"<<endl;
        std::cin>>po;
        setSmP = std::stoi(po);

        sm.WritePosEx(1, setSmP,300, 0);//舵机(ID1)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P1=4095位置

        usleep(100/(50*300)*1000+(50*300)/1000);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000



    }

}


void getPosition(){
    while(1){
        int Pos;
        int Speed;
        int Load;
        int Voltage;
        int Temper;
        int Move;
        int Current;
        if(sm.FeedBack(1)!=-1){
            Pos = sm.ReadPos(-1);
            Speed = sm.ReadSpeed(-1);
            Load = sm.ReadLoad(-1);
            Voltage = sm.ReadVoltage(-1);
            Temper = sm.ReadTemper(-1);
            Move = sm.ReadMove(-1);
            Current = sm.ReadCurrent(-1);
            std::cout<<"pos = "<<Pos<<" ";
            std::cout<<"Speed = "<<Speed<<" ";
            std::cout<<"Load = "<<Load<<" ";
            std::cout<<"Voltage = "<<Voltage<<" ";
            std::cout<<"Temper = "<<Temper<<" ";
            std::cout<<"Move = "<<Move<<" ";
            std::cout<<"Current = "<<Current<<std::endl;
            usleep(10*1000);
        }else{
            std::cout<< "read err ="<<std::endl;
            sleep(2);
        }
    }
}