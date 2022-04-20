#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {
    // Mat testImage = imread("../photos/flowers01.jpeg");
    

    //basic manipulation
    // imshow("Window1", testImage);
    // waitKey();

    // std::cout << "Value at 0.0: " << (int)testImage.at<uchar>(0,0) << std::endl;


    // Mat testImage_roi = testImage(Range(0,2), Range(0,4));
    // std::cout << "ROI: " << std::endl << testImage_roi << std::endl;

    // imshow("Window1", testImage_roi);
    // waitKey();

    // testImage(Range(0,20), Range (0,60)).setTo(0);
    // imshow("Window1", testImage);
    // waitKey();

    // auto result = imwrite("../photos/test.jpg", testImage);

    // std::cout << "Image size = " << testImage.size() << std::endl;
    // std::cout << "Image channels = " << testImage.channels() << std::endl;

    // Mat imgChannels[3];
    // split(testImage, imgChannels);

    // imshow("Win1", imgChannels[0]);
    // waitKey();

    // imshow("Win1", imgChannels[1]);
    // waitKey();

    // imshow("Win1", imgChannels[2]);
    // waitKey();

    // testImage(Range(0,100), Range(0,100)).setTo(Scalar(0,0,0));
    // imshow("Win1", testImage);
    // waitKey();

    Mat image = imread("../photos/flowers01.jpeg");

    imshow("Win1", image);
    waitKey();

    Mat image_copy = image.clone();
    Mat emptyMatrix = Mat(100, 200, CV_8UC3, Scalar(0,0,0));

    imshow("Win2", emptyMatrix);
    waitKey();

    emptyMatrix.setTo(Scalar(255,255,255));
    imshow("Win2", emptyMatrix);
    waitKey();

    return 0;
}