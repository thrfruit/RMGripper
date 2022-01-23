#define _USE_MATH_DEFINES
#include <math.h>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <fstream>              // File IO
#include <iostream>             // Terminal IO
#include <sstream>              // Stringstreams
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <chrono>
#include <thread>

#include <Eigen/Dense>
#include "gripper_driver.h"


namespace {
    const char* about = "Pose estimation of ArUco marker images";
    const char* keys  =
            "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
            "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
            "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, "
            "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, "
            "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
            "{h        |false | Print help }"
            "{l        |      | Actual marker length in meter }"
            "{v        |<none>| Custom video source, otherwise '0' }"
            "{h        |false | Print help }"
            "{l        |      | Actual marker length in meter }"
            "{v        |<none>| Custom video source, otherwise '0' }"
    ;
}
using namespace cv;
using namespace std;
using namespace rs2;
using namespace ur_rtde;
using namespace std::chrono;
using namespace urcl;
using namespace Eigen;

Matrix<double,4,4> qiciMatrix(vector<double> pose){
    Matrix<double,3,3> Rx,Ry,Rz,R;
    Matrix<double,3,4> temp;
    Matrix<double,3,1> loc;
    Matrix<double,1,4> unit;
    Matrix<double,4,4> qici;

    Rx<<1,0,0,
        0,cos(pose[3]),-sin(pose[3]),
        0,sin(pose[3]),cos(pose[3]);

    Ry<<cos(pose[4]),0,sin(pose[4]),
        0,1,0,
        -sin(pose[4]),0,cos(pose[4]);

    Rz<<cos(pose[5]),-sin(pose[5]),0,
        sin(pose[5]),cos(pose[5]),0,
        0,0,1;
    R=Rx*Ry*Rz;
    loc<<pose[0],pose[1],pose[2];
    unit<<0,0,0,1;
    temp<<R,loc;
    qici<<temp,unit;
    return qici;

}

int main(int argc, char * argv[])
{
//    Matrix<double,4,4> qi;
//    vector<double> pose{-0.246877, 0.124364, 0.478462, 1.73669, -1.74552, -0.933895, 85.199997};
//    qi= qiciMatrix(pose);
//    //cout<<qi<<endl;
//
//    Matrix<double,4,1> Plugin{0.0108953, -0.00793857, 0.454078,1};
////    //Matrix<double,4,1> Tpose{2,0,2,1};
//    Matrix<double,4,1> target;
////    //
////    Matrix<double,4,4> Trans_P2T;
//    Matrix<double,4,4> Trans_C2B;
////    vector<double> move_cmd(6,0);
////    Trans_P2T<< 1,0,0,0,
////                0,1,0,-0.2e3,
////                0,0,1,0,
////                0,0,0,1;
////    //camera robot relative matrix unit mm
////    Trans_C2B<< 0.9999999624190277, -0.0001066348446981288, 0.0002525687096498024, -106.0174954363054,
////            0.000106657987661869, 0.9999999901150465, -9.161867098192249e-05, 48.28408966345854,
////            -0.0002525589374104208, 9.164560600912135e-05, 0.9999999639075323, 6.855075595857189e-310,
////            0, 0, 0, 1;
//    Trans_C2B<< 0.9999999624190277, -0.0001066348446981288, 0.0002525687096498024, -0.1060174954363054,
//            0.000106657987661869, 0.9999999901150465, -9.161867098192249e-05, 0.04828408966345854,
//            -0.0002525589374104208, 9.164560600912135e-05, 0.9999999639075323, 0.006855075595857189e-310,
//            0, 0, 0, 1;
//    target=qi*Trans_C2B*Plugin;
//    cout<<target<<endl;

    //
//    target=Trans_P2T*Trans_C2B*Plugin;
//    for(int i=0;i<3;i++){
//        move_cmd[i]=target(i)*0.001;
//    }
//
//    //Matrix<double,4,4> Trans_P2T{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
//    cout<<"Cross result:\n"<<target<<endl;
//    for(auto c:move_cmd)
//        cout<<c<<", ";
//    Matrix<double,3,1> TPose{-0.638078, 0.151019, 0.465055};
//    Matrix<double,3,1> R1{-0.147244, 0.270347, 0.59502};
//    for(int i=0;i<3;i++){
//        cout<<R1(i)-TPose(i)<<", ";
//    }

//    ofstream recordFile("../calibration/img_sequence.txt",ios::app);
//    for(int i=0;i<40;i++){
//        recordFile<<"capture"+ to_string(i)+".jpg"<<endl;
//    }



    ifstream ifile("../calibration/tcpPose.txt",ios::in);
    ofstream recordFile("../calibration/pose.txt",ios::app);
    if(!ifile){
        cout << "未找到机器人姿态数据文件！！！" << endl;
    }
    string strr;
    istringstream ostr;
    string s;
    while(getline(ifile,strr)){
        ostr.clear();
        ostr.str(strr);
        for(int i=0;i<6;i++){
            ostr>>s;
            if(i!=5){
                s[-1]=' ';
            }
            double j= stod(s);
            if(i>=0&&i<3){
                cout<<j*1000<<" ";
                recordFile<<j*1000<<" ";
            }else if(i==5){
                cout<<j*180/M_PI<<endl;
                recordFile<<j*180/M_PI<<endl;
            }else{
                cout<<j*180/M_PI<<" ";
                recordFile<<j*180/M_PI<<" ";
            }
        }


    }
    return 0;

}

