

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
#include <Eigen/Core>
#include "gripper_driver.h"
#include <time.h>
//keyboard
#include <stdio.h>
#include <termios.h>


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

void outputPose(std::vector<double> pose){
    //cout<<"pose is ";
    for(int i=0;i<6;i++){
        if(i==5)
            cout<<pose[5];
        else
            cout<<pose[i]<<", ";
    }
    cout<<endl;
}

void moveSequence(std::vector<double> target, double velocity, double acceleration, double p_sleep,
                  RTDEControlInterface& rtde_control,RTDEReceiveInterface& rtde_receive){
    std::vector<double> actual_pose;
    actual_pose=rtde_receive.getActualTCPPose();
    for(int i=0;i<6;i++){
        actual_pose[i]=target[i];
        rtde_control.moveL(actual_pose, velocity, acceleration);
        sleep(p_sleep);
    }
}

int main(int argc, char * argv[]) try
{
    const std::string ROBOT_IP = "192.168.1.10";
    const std::chrono::milliseconds READ_TIMEOUT{ 100 };
    ///UR initial
    //Use with ExternalControl UR Cap
    //RTDEControlInterface rtde_control(ROBOT_IP,RTDEControlInterface::FLAG_USE_EXT_UR_CAP,50002);
    //Use in remote mode
    RTDEControlInterface rtde_control(ROBOT_IP);

    RTDEReceiveInterface rtde_receive(ROBOT_IP);
    cout<<"Robot start success"<<endl;
    std::vector<double> actual_pose;

    cout<<"Robot initial success"<<endl;

    ///end UR initial

    /////realsense initial
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;
    // Declare rates printer for showing streaming rates of the enabled streams.
    rs2::rates_printer printer;
    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();
    const auto window_name = "image capture";
    namedWindow(window_name, WINDOW_AUTOSIZE);
    ///// end realsense initial

    /////aruco initial
//    //DICT_4X4_1000=3
//    int dictionaryId = 3;
//    //unit meter
//    float marker_length_m = 0.015;
//    int wait_time = 10;
//
//    if (marker_length_m <= 0) {
//        std::cerr << "marker length must be a positive value in meter"
//                  << std::endl;
//        return 1;
//    }
    //realsense rgb stream also can be obtained by videoCapture(6)
//    int videoInput = 6;
//    cv::VideoCapture in_video;
//    in_video.open(videoInput);
//    if (!in_video.isOpened()) {
//        std::cerr << "failed to open video input: " << videoInput << std::endl;
//        return 1;
//    }

//    cv::Mat image, image_copy;
//    cv::Mat camera_matrix, dist_coeffs;
//    std::ostringstream vector_to_marker;
//
//    cv::Ptr<cv::aruco::Dictionary> dictionary =
//            cv::aruco::getPredefinedDictionary( \
//        cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
//
//    cv::FileStorage fs("../camera/realsense_calibration_params.yml", cv::FileStorage::READ);
//
//    fs["camera_matrix"] >> camera_matrix;
//    fs["distortion_coefficients"] >> dist_coeffs;
//
//    std::cout << "camera_matrix\n" << camera_matrix << std::endl;
//    std::cout << "\ndist coeffs\n" << dist_coeffs << std::endl;
    /////end aruco initial



    int id=0;
    while (true)
    {
        rs2::frameset data = pipe.wait_for_frames();    // Wait for next set of frames from the camera
        rs2::frame color = data.get_color_frame().apply_filter(color_map);
        const int w=color.as<rs2::video_frame>().get_width();
        const int h=color.as<rs2::video_frame>().get_height();
        Mat image(Size(w, h), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
        Mat  image_copy;
//        in_video.retrieve(image);
        image.copyTo(image_copy);
        imshow(window_name, image_copy);
        ofstream recordFile("../calibration/tcpPose.txt",ios::app);
        ofstream recordFile2("../calibration/tcpPose2.txt",ios::app);
        char key = (char)waitKey(10);
        if(key == 27) {
            recordFile.close();
            break;
        }

        if(key == 'c' ) {
            cout << "Frame captured" << endl;
            imwrite("../calibration/capture"+ to_string(id)+".jpg",image);
            id++;
            actual_pose=rtde_receive.getActualTCPPose();
            for(int i=0;i<6;i++){
                if(i==5){
                    cout<<actual_pose[5]*180/M_PI<<endl;
                    recordFile<<actual_pose[5]*180/M_PI<<endl;
                    recordFile2<<actual_pose[5]*180/M_PI<<endl;
                }
                else{
                    if(i>=0&&i<3){
                        cout<<actual_pose[i]*1000<<", ";
                        recordFile<<actual_pose[i]*1000<<", ";
                        recordFile2<<actual_pose[i]*1000<<" ";
                    }else{
                        cout<<actual_pose[i]*180/M_PI<<", ";
                        recordFile<<actual_pose[i]*180/M_PI<<", ";
                        recordFile2<<actual_pose[i]*180/M_PI<<" ";
                    }


                }
            }
            cout<<"record success"<<endl;
        }

    }

    return EXIT_SUCCESS;

}

catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
