#include "Serial.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{

    Serial arduino = Serial("/dev/ttyUSB3", 115200);

    string input = "";
    char output[512] = "";

    while(true)
    {
        cout << "input> ";
        //`cin` tokenizes on whitespace, use getline instead
        getline(cin, input);

        ssize_t w_bytes = arduino.Write(input.c_str(), input.size());
        // sleep long enough that the Arduino has enough time to respond
        usleep(20000);
        ssize_t r_bytes = arduino.Read(output, sizeof(output));
        // size_t r_bytes = arduino.ReadBlocking(output, 4);

        cout << "wrote " << w_bytes << "> " << input << endl;
        cout << "read " << r_bytes << "> " << output << endl;
    }

    return 0;
}
