#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <cstring>
#include<stdio.h>
#include <unistd.h>
#include <stdint.h>

class Serial {
private:
    int fd;
    int nSpeed;
    char nEvent;
    int nBits;
    int nStop;

    int set_opt(int fd, int nSpeed, char nEvent, int nBits, int nStop);

public:
    Serial(int nSpeed = 115200, char nEvent = 'N', int nBits = 8, int nStop = 1);
    ~Serial();

    bool InitPort(int nSpeed = 115200, char  nEvent = 'N', int nBits = 8, int nStop = 1);
//    int GetBytesInCOM() const ;
    bool WriteData(const unsigned char* pData, unsigned int length);
    bool ReadData(unsigned char* buffer, unsigned int length);
};


//void sendTarget(Serial *serial);
void uart(Serial *pSerial);


struct SendData {
  
    int16_t  linemotor;
    int16_t  rotate;
    int16_t  rotatespeed;
};


// 单片机端回传数据结构体
struct McuData {
    char    ready_flag;   //ready:t  not ready:f;
    int16_t    Height;
};

extern McuData Recieve_data;
extern SendData Send_data;

