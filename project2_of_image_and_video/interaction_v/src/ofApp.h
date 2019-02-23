#pragma once

#include "ofMain.h"

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
    
        ofVideoPlayer video;    //declare video player object
        deque<ofPixels> frames;        //Frames buffer
        int N;                        //Frames buffer size
        float zoomFactor;
    
        //Pixels array for constructing output image
        ofPixels imagePixels;
        ofImage image;                //Output image
        ofImage image2;
        ofImage image3;
        ofColor getSlitPixelColor( int x, int y );
    
        int table[16];        //Declare table for color replacing
    
        bool functionOne=false;
        bool functionTwo=false;
        bool functionThree=false;
        bool functionFour=false;
        bool functionFive=false;
        bool functionSix=false;
		
};
