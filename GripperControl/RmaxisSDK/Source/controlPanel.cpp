//
// Created by root on 2021/11/10.
//

#include "lib/controlPanel.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int setSmP = 0, setLSmP = 0, setES = 0, setGraspForce = 0;
int getSmP = 0, getLSmP = 0;
void controlPanel()
{
    //VideoCapture cap(0);
    //Mat img;
   // Mat imgHSV, mask, imgColor;
    //int setSmP = 0, setLSmP = 0, setES = 0, setGraspForce = 0;
    //int getSmP = 0, getLSmP = 0;
    
    namedWindow("Trackbars", (640, 200)); // Create Window
    createTrackbar("Setting SM Positon", "Trackbars", &setSmP, 360);
    createTrackbar("Current SM Positon", "Trackbars", &getSmP, 360);
    createTrackbar("Setting Linear SM Postion", "Trackbars", &setLSmP, 50);
    createTrackbar("Current Linear SM Positon", "Trackbars", &getLSmP, 50);
    createTrackbar("Setting Electromagnet Status", "Trackbars", &setES, 1);
    createTrackbar("Setting Grasp Force", "Trackbars", &setGraspForce, 450);

    while (true) {

        //cap.read(img);
       // cvtColor(img, imgHSV, COLOR_BGR2HSV);

       // Scalar lower(hmin, smin, vmin);
       // Scalar upper(hmax, smax, vmax);

        //inRange(imgHSV, lower, upper, mask);
// hmin, smin, vmin, hmax, smax, vmax;
       // cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
      //  imshow("Image", img);
      //  imshow("Mask", mask);
        waitKey(1);
    }
}

