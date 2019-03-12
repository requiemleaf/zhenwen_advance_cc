#pragma once

#include "ofMain.h"
#include "particle.hpp"
#include <vector>

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
    
        int scl = 10; // the scale of each pixel
        int col; // colume
        int row; // row
        float inc = 0.05; // noise increment
    
        float zOff = 0;
    
        string path = "../../../hw_03_drawing_step01/bin/data";

        ofImage testImg;
        ofImage rImg;
    
        vector<ofImage> myImages;
    
        vector< shared_ptr<Particles> > particles;
        //vector<Particle> particles; // array for all particles
        vector <ofVec2f> flowField; // array for direction vectors
		
};
