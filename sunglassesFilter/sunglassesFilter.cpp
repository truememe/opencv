#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;

int main() {
    String faceImagePath = "../images/musk.jpg";

    Mat faceImage = imread(faceImagePath);
    faceImage.convertTo(faceImage, CV_32FC3);
    faceImage = faceImage/255.0;

    String sunglassImagePath = "../images/sunglass.png";
    Mat sunglassPNG = imread(sunglassImagePath, -1);

    sunglassPNG.convertTo(sunglassPNG, CV_32F);
    sunglassPNG = sunglassPNG/255.0;
    resize(sunglassPNG, sunglassPNG, Size(300,100));

    int sunglassHeight = sunglassPNG.size().height;
    int sunglassWidth = sunglassPNG.size().width;

    Mat sunglassRGBAChannels[4];
    Mat sunglassRGBChannels[3];
    split(sunglassPNG, sunglassRGBAChannels);
    for (int i=0; i<3; i++) 
    {
        sunglassRGBChannels[i] = sunglassRGBAChannels[i];
    }

    Mat sunglassBGR, sunglassMask1;
    merge(sunglassRGBChannels, 3, sunglassBGR);
    sunglassMask1 = sunglassRGBAChannels[3];

    imshow("Face Image", faceImage);
    waitKey();

    imshow("Sunglass Color Channels", sunglassBGR);
    imshow("Mask", sunglassMask1);
    waitKey();

    imwrite("../images/results/sunglassRBG.png", sunglassBGR);
    imwrite("../images/results/sunglassAlpha.png", sunglassMask1);

    Mat faceSunglassImage = faceImage.clone();
    Mat roiFace = faceSunglassImage(Range(150,250),Range(140,440));
    sunglassBGR.copyTo(roiFace);

    imwrite("../images/results/sunglassFaceNaive.png", faceSunglassImage);

    imshow("SunglassFaceNaive", faceSunglassImage);
    waitKey();

    Mat sunglassMask;
    Mat sunglassMaskChannels[] = {sunglassMask1, sunglassMask1, sunglassMask1};
    merge(sunglassMaskChannels, 3, sunglassMask);
    sunglassMask = sunglassMask/255;

    Mat faceSunglassOK = faceImage.clone();
    Mat eyeROI = faceSunglassOK(Range(150,250), Range(140,440));

    Mat eyeROIChannels[3];
    split(eyeROI, eyeROIChannels);
    Mat maskedEyeChannels[3];
    Mat maskedEye;

    for(int i=0; i<3; i++)
    {
        multiply(eyeROIChannels[i], (1-sunglassMaskChannels[i]), maskedEyeChannels[i]);
    }
    merge(maskedEyeChannels, 3, maskedEye);

    Mat maskedGlass;
    multiply(sunglassBGR, sunglassMask, maskedGlass);

    Mat eyeROIFinal;
    add(maskedEye, maskedGlass, eyeROIFinal);

    imshow("MaskedEyeRegion", maskedEye);
    imshow("MaskedGlass", maskedGlass);
    imshow("Eye ROI final", eyeROIFinal);
    waitKey();

    return 0;
}