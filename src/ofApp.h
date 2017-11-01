#pragma once


#include "ofMain.h"
#include "ofxCvHaarFinder.h"


class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    const int thresholdFaceSize = 150 * 150;
    ofVideoGrabber grabber;
    
    ofxCvHaarFinder finder;
    
    ofFbo facemask;
    
};
