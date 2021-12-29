#include <iostream>
#include <usb-daq-v20.h>
#include "RMAxis.h"
#include "iostream"
#include "unistd.h"
#include "thread"

using namespace std;
float adResult, adBuf[1024];
double getForce(void);
int main() {
    RMAxis* axis = RMAxis::create_rmaxis_modbus_rtu("/dev/RmDriver", 115200, 0);
//
////    thread t(sampleForce);
////    t.detach();udevadm info

    axis->go_home();
    sleep(5);
    //axis->destroy_rmaxis(axis);
    axis->push(100,8,10);
//
   //axis->move_to(10);
    //axis->move_absolute(1,10,1,1,1);
    //sleep(5);
//
    if (-1 == OpenUsbV20()) {
        printf("...... UsbV20! Open! Failed! ......\n");
    }
    while(1){
        //sleep(1);
        float pos=axis->position();
        cout<<"positon="<<pos<<endl;
        double curForce=getForce();
        cout<<"Force="<<curForce<<endl;
        sleep(1);
    }

    return 0;
}

double getForce(void) {
    double force;
    // 单次采集
    ADSingleV20(0, 0, &adResult);
    // 连续采集，一个数据包为512个数据
    // ADContinuV20(0, 0, 512, 100000, adBuf);
    // for(int i=0;i<512;i++) {
    //   adResult += adBuf[i];
    // }
    // adResult /= 512.0;
    //force = (double)(100.0/(2.7-adResult)-40.0);
    force = (double)(322.9*adResult-198.9);
    return force;
}