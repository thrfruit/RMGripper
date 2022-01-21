#include <iostream>
#include <fstream>
#include<stdio.h>
#include<string>
#include <thread>
#include "Serial.h"


using namespace std;


/*McuData Recieve_data = {
        'f',
        0,
};*/


SendData Send_data = {
        .linemotor=0,
        .rotate=0,
        .rotatespeed=0
};

Serial serial(115200);                  // 串口对象

int main(int argc, char *argv[]) {
    bool start=false;

    Send_data.linemotor=0;
  // thread communication(uart, &serial);   // 开启串口线程
    int16_t X=0;
    int16_t Y=0; 
    int16_t Z=0; 

    cout<<endl;
    while ( cin>>X>>Y>>Z)
    {  
        Send_data.linemotor=X;
        Send_data.rotate=Y;
        Send_data.rotatespeed=Z;
        uart(&serial);
         cout<<X<<"    "<<Y<< "  "<<Z<<endl;
        usleep(100);
        usleep(1000);
        uart(&serial);
          cout<<"send success"<<endl;
           usleep(1000);
         uart(&serial);
             usleep(1000);
         uart(&serial);
           usleep(1000);
        uart(&serial);
           usleep(1000);
         uart(&serial);
             usleep(1000);
         uart(&serial);

    }
    return 0;
}





