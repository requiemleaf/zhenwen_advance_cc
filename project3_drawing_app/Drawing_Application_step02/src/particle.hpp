#ifndef particle_hpp
#define particle_hpp


#include "ofMain.h"
#include <vector>
//#include <stdio.h>

class Particles{
    
public:
    Particles();
    void setup(ofImage img, int scl, int col);
    void update();
    void draw();
    void follow(vector<ofVec2f> flowField);
    void applyForce(ofVec2f force);
    void updatePrev();
    void edges();
    
    int size = 1;
    int scl;
    int col;
    
    ofImage img;
    ofVec2f prePos;
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    
};

#endif /* particle_hpp */
