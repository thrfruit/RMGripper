

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
    cout<<"pose is ";
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
    std::vector<double> actual_pose,target{-0.380068, 0.139046, 0.501654, 1.71829, -1.81746, -0.554882};
    actual_pose=rtde_receive.getActualTCPPose();
    for(int i=0;i<6;i++){
        actual_pose[i]=target[i];
        rtde_control.moveL(actual_pose, 0.2, 0.2);
        sleep(0.2);
    }
    actual_pose=rtde_receive.getActualTCPPose();
    outputPose(actual_pose);
    cout<<"Robot initial success"<<endl;

    ///end UR initial

    ///CRG-Gripper initial
    std::string Gripper_IP = "192.168.1.23";
    int portIndex = 0;
    CRGGripper crg_handle(Gripper_IP, portIndex);
    //crg_handle.home();
    //sleep(2);
    //plugin is suit to 42
    //crg_handle.go(40,60);
    std::cout<<crg_handle.read_pos()<<std::endl;
    cout<<"Gripper initial success"<<endl;
    bool g_flag= false;
    ///end CRG-Gripper initial


    /////realsense initial
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;
    // Declare rates printer for showing streaming rates of the enabled streams.
    rs2::rates_printer printer;
    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();
    const auto window_name = "Pose estimation";
    namedWindow(window_name, WINDOW_AUTOSIZE);
   ///// end realsense initial

   /////aruco initial
    //DICT_4X4_1000=3
    int dictionaryId = 3;
    //unit meter
    float marker_length_m = 0.015;
    int wait_time = 10;

    if (marker_length_m <= 0) {
        std::cerr << "marker length must be a positive value in meter"
                  << std::endl;
        return 1;
    }
    //realsense rgb stream also can be obtained by videoCapture(6)
    //int videoInput = 6;
    //cv::VideoCapture in_video;
    //in_video.open(videoInput);
//    if (!in_video.isOpened()) {
//        std::cerr << "failed to open video input: " << videoInput << std::endl;
//        return 1;
//    }

    cv::Mat image, image_copy;
    cv::Mat camera_matrix, dist_coeffs;
    std::ostringstream vector_to_marker;

    cv::Ptr<cv::aruco::Dictionary> dictionary =
            cv::aruco::getPredefinedDictionary( \
        cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

    cv::FileStorage fs("../camera/realsense_calibration_params.yml", cv::FileStorage::READ);

    fs["camera_matrix"] >> camera_matrix;
    fs["distortion_coefficients"] >> dist_coeffs;

    std::cout << "camera_matrix\n" << camera_matrix << std::endl;
    std::cout << "\ndist coeffs\n" << dist_coeffs << std::endl;
   /////end aruco initial

   ////keyboard initial
    termios tms_old, tms_new;

    tcgetattr(0, &tms_old);

    tms_new = tms_old;
    tms_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &tms_new);
    ////end keyboard initial

//    while (waitKey(1) < 0 && getWindowProperty(window_name, WND_PROP_AUTOSIZE) >= 0)
    while (true)
    {
        rs2::frameset data = pipe.wait_for_frames();    // Wait for next set of frames from the camera
        rs2::frame color = data.get_color_frame().apply_filter(color_map);
        //rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
        //const int w = depth.as<rs2::video_frame>().get_width();
        //const int h = depth.as<rs2::video_frame>().get_height();
        const int w=color.as<rs2::video_frame>().get_width();
        const int h=color.as<rs2::video_frame>().get_height();
        // The show method, when applied on frameset, break it to frames and upload each frame into a gl textures
        // Each texture is displayed on different viewport according to it's stream unique id
        Mat image(Size(w, h), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);

        //imshow(window_name,image);
        image.copyTo(image_copy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        // if at least one marker detected
        if (ids.size() > 0)
        {
            cv::aruco::drawDetectedMarkers(image_copy, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, marker_length_m,
                                                 camera_matrix, dist_coeffs, rvecs, tvecs);
            for(int i=0; i < ids.size(); i++){
                std::cout <<"id="<<ids[i]
                          <<"\tTranslation: " << tvecs[i]
                          << "\tRotation: " << rvecs[i]
                          << std::endl;
            }


            // Draw axis for each marker
            for(int i=0; i < ids.size(); i++)
            {
                cv::aruco::drawAxis(image_copy, camera_matrix, dist_coeffs,
                                    rvecs[i], tvecs[i], 0.1);

                // This section is going to print the data for all the detected
                // markers. If you have more than a single marker, it is
                // recommended to change the below section so that either you
                // only print the data for a specific marker, or you print the
                // data for each marker separately.
                vector_to_marker.str(std::string());
                vector_to_marker << std::setprecision(4)
                                 << "x: " << std::setw(8) << tvecs[0](0);
                cv::putText(image_copy, vector_to_marker.str(),
                            cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                            cv::Scalar(0, 252, 124), 1, CV_AVX);

                vector_to_marker.str(std::string());
                vector_to_marker << std::setprecision(4)
                                 << "y: " << std::setw(8) << tvecs[0](1);
                cv::putText(image_copy, vector_to_marker.str(),
                            cv::Point(10, 50), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                            cv::Scalar(0, 252, 124), 1, CV_AVX);

                vector_to_marker.str(std::string());
                vector_to_marker << std::setprecision(4)
                                 << "z: " << std::setw(8) << tvecs[0](2);
                cv::putText(image_copy, vector_to_marker.str(),
                            cv::Point(10, 70), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                            cv::Scalar(0, 252, 124), 1, CV_AVX);
            }
        }
        imshow(window_name, image_copy);
        char key = (char)cv::waitKey(wait_time);
        if (key == 27)
            break;

        //press G to control the grip and release of CRG-gripper
//        unsigned char ch = getchar();
//        if(ch='g'&&(!g_flag)){
//            crg_handle.go(38,60);
//            g_flag=true;
//        }
//        if(ch='g'&&g_flag){
//            crg_handle.home();
//            g_flag= false;
//        }
//        if(ch='e'){
//            break;
//        }
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
