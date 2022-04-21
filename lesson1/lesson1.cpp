#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {

    //--------------SECTION1
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

    //----------------SECTION2

    // Mat image = imread("../images/boy.jpg");

    // imshow("Win1", image);
    // waitKey();

    // Mat image_copy = image.clone();
    // Mat emptyMatrix = Mat(100, 200, CV_8UC3, Scalar(0,0,0));

    // imshow("Win2", emptyMatrix);
    // waitKey();

    // emptyMatrix.setTo(Scalar(255,255,255));
    // imshow("Win2", emptyMatrix);
    // waitKey();

    // Mat emptyOriginal = Mat(image.size(), image.type(), Scalar(100,100,100));
    // imwrite("../images/results/copy100.png", emptyOriginal);

    // Mat crop = image(Range(40,200), Range(170,320));
    // imwrite("../images/results/crop.png", crop);

    // Mat copiedImage = image.clone();
    // Mat copyRoi = image(Range(40,200), Range(180,320));
    // int roiHeight = copyRoi.size().height;
    // int roiWidth = copyRoi.size().width;

    // copyRoi.copyTo(copiedImage(Range(40, 40+roiHeight), Range(10, 10+roiWidth)));
    // copyRoi.copyTo(copiedImage(Range(40, 40+roiHeight), Range(330, 330+roiWidth)));

    // imwrite("../images/results/copy.png", copiedImage);

    // int resizeDownWidth = 300;
    // int resizeDownHeight = 200;
    // Mat resizedDown;
    // resize(image, resizedDown, Size(resizeDownWidth, resizeDownHeight), 0.0, 0.0, INTER_LINEAR);

    // int resizeUpWidth = 600;
    // int resizeUpHeight = 900;
    // Mat resizedUp;
    // resize(image, resizedUp, Size(resizeUpWidth, resizeUpHeight), 0.0, 0.0, INTER_LINEAR);

    // imshow("Win1", resizedDown);
    // imshow("Win2", resizedUp);
    // waitKey();

    // double scaleUpX = 1.5;
    // double scaleUpY = 1.5;

    // double scaleDown = 0.6;

    // Mat scaledUp, scaledDown;

    // resize(image, scaledUp, Size(), scaleUpX, scaleUpY, INTER_LINEAR);
    // resize(image, scaledDown, Size(), scaleDown, scaleDown, INTER_LINEAR);

    // imshow("Win1", scaledUp);
    // imshow("Win2", scaledDown);
    // waitKey();

    // Mat mask1 = Mat::zeros(image.size(), image.type());
    // imwrite("../images/results/mask1.png", mask1);

    // mask1(Range(50,200), Range(170,320)).setTo(255);
    // imwrite("../images/results/mask1a.png", mask1);

    // Mat mask2;
    // inRange(image, Scalar(0,0,150), Scalar(100,100,255), mask2);
    // imwrite("../images/results/mask2.png", mask2);

    //------------------ SECTION3

    Mat image = imread("../images/boy.jpg");
    // std::cout << "Image Data Type : " << image.type() << std::endl;

    // Mat image_16U = image.clone();
    // image_16U.convertTo(image_16U, CV_16U);
    // image_16U = image_16U*256;

    // Mat image_32F = image.clone();
    // image_32F.convertTo(image_32F, CV_32F);
    // image_32F = image_32F/255.0;

    // imshow("Win1", image);
    // imshow("Win2", image_16U);
    // imshow("Win3", image_32F);
    // waitKey();

    // double contrastPercentage = 80.0;

    Mat image32F = image.clone();
    // Mat highCont_1;
    // Mat highCont_2;

    image32F.convertTo(image32F, CV_32F);
    // highCont_1 = image32F * (1 + contrastPercentage/100.0);

    image32F = image32F/255.0;
    // highCont_2 = image32F * (1 + contrastPercentage/100.0);
    // imshow("Win1", image);
    // imshow("Win2", highCont_1);
    // imshow("Win3", highCont_2);
    // waitKey();

    int brightnessOffset = 100;

    Mat bright_32F;
    Mat brightHighChannels_32F[3];

    Mat tempBright = image32F.clone();
    tempBright = tempBright + brightnessOffset;


    split(image32F, brightHighChannels_32F);
    for (int i=0; i<3; i++) {
        add(brightHighChannels_32F[i], brightnessOffset/255.0, brightHighChannels_32F[i]);
    }
    merge(brightHighChannels_32F, 3, bright_32F);

    Mat bright_normalized_32F;
    Mat brightHighChannels_norm_32F[3];

    split(image32F, brightHighChannels_norm_32F);

    for(int i=0; i<3; i++) {
        add(brightHighChannels_norm_32F[i], brightnessOffset/255.0, brightHighChannels_norm_32F[i]);
    }
    merge(brightHighChannels_norm_32F, 3 , bright_normalized_32F);

    double minVal, maxVal;
    minMaxLoc(bright_normalized_32F, &minVal, &maxVal);
    bright_normalized_32F = bright_normalized_32F/maxVal;

    imshow("NoB", image);
    imshow("Incorrect", tempBright);
    imshow("Correct", bright_32F);
    imshow("Normalized", bright_normalized_32F);
    waitKey();
    return 0;
}