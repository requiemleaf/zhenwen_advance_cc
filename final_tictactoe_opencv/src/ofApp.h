#pragma once

#include "ofMain.h"
#include "ofxCv.h"
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
		
        //-------------------color tracking------------------------------
    
        ofVideoGrabber movie;   // movie object for captuyring Video from Cam
        ofxCvColorImage rgb,hsb;    //rgb object for storing color image data
        ofxCvGrayscaleImage hue,sat,bri,filtered1,filtered2;  //objects for storing grayscale image data
        ofxCvContourFinder contourFinder1;    //object to store contours of the filtered image
        ofxCvContourFinder contourFinder2;    //object to store contours of the filtered image
    
        int w,h;
        int findHue1;
        int findHue2;
    
        //--------------------tictactoe game-----------------------------
        void initgame();
    
        bool checkifwin();
        bool checkifdraw();
    
        int numberPlayer;
        int matrix[3][3]; //this matrix stores the x and o and blank box of the game, a value of 0 is blank, 1 is x and 2 is o
        int playerturn; //playerturn if it is 1 then 1st players turn else if it is 2 then its second players turn
        int result; //result of the game if it is 0 then draw if it is 1 then player 1 wins if it is 2 then player 2 wins
        bool gameover; //gameover if it is 0 then its not game over else if it is 1 then its game over
};
