#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"


class ofApp : public ofBaseApp{
    
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofVideoGrabber mVideoGrabber; //declare a ofVideoGrabber object
    ofFbo    mFbo;
    ofxCvGrayscaleImage grayImage;
    ofxCvColorImage colorImg;
    // screen save
    int imgSaveNum = 0; // counter for saving screens
    ofImage imgSave;
    // abs diff
    ofxCvGrayscaleImage grayFrame1;
    ofxCvGrayscaleImage grayFrame2;
    int frameCounter = 0;
    // blur
    vector<ofxCvColorImage> blurImgs;
    int blurCount = 30;
    string currentMode = "none";
    
    
};
