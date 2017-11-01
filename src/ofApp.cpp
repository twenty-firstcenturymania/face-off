#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    grabber.setup(640, 480);
	finder.setup("haarcascade_frontalface_default.xml");
    
   facemask.allocate(640, 480);
}

//--------------------------------------------------------------
void ofApp::update()
{
    grabber.update();

    if (grabber.isFrameNew())
    {
        finder.findHaarObjects(grabber.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    facemask.begin();
    ofBackground(255);
    
    ofNoFill();
	for(unsigned int i = 0; i < finder.blobs.size(); i++)
    {
        // Ignore small "faces".
        if (finder.blobs[i].boundingRect.getArea() > thresholdFaceSize)
        {
            ofRectangle rect = finder.blobs[i].boundingRect;

            float xNose = rect.getCenter().x;
            float yNose = rect.getCenter().y;
            float yEye = rect.getCenter().y - 0.11 * rect.getHeight();
            float yMouth = rect.getCenter().y + 0.24 * rect.getHeight();
            float xEyeOffset = 0.18 * rect.getWidth();

            float xEyeRight = xNose + xEyeOffset;
            float xEyeLeft  = xNose - xEyeOffset;

            ofDrawCircle(xEyeRight, yEye, 10);
            ofDrawCircle(xEyeLeft, yEye, 10);

            ofDrawCircle(xNose, yNose, 10);

            ofDrawRectangle(xNose - 20, yMouth - 5, 40, 10);

            ofDrawRectangle(rect);
            
            float faceCenterX = rect.getCenter().x;
            float faceCenterY = rect.getCenter().y;
            float faceWidth = rect.getWidth();
            float faceHeight = rect.getHeight();
            
            float faceOvalHeight = rect.height * 1.3;
            float faceOvalWidth = rect.width * 0.9;
            float faceOvalX = faceCenterX;
            float faceOvalY = faceCenterY;
            
            
            //constructing a mask
            ofPath ellipseMask;
            ellipseMask.setFillColor(ofColor(0, 0));
            ellipseMask.rectangle(0, 0, ofGetWidth(), ofGetHeight());
            ellipseMask.setCircleResolution(64);
            
          
          //  ellipseMask.ellipse(faceOvalX, faceOvalY, faceOvalWidth, faceOvalHeight);
            
            
         //   ofDrawEllipse(faceOvalX, faceOvalY, faceOvalWidth, faceOvalHeight);
            

        }
        
        facemask.end();
      
        ofFill();
        ofSetColor(255);
        grabber.draw(0, 0);
        
        ofTexture maskedgrabberTexture = grabber.getTexture();
        maskedgrabberTexture.setAlphaMask(facemask.getTexture());
        maskedgrabberTexture.draw(ofGetMouseX(), ofGetMouseY());
        
        
        
        //facemask.draw(0,0);
        facemask.draw(ofGetMouseX(), ofGetMouseY());
    
    }
}

