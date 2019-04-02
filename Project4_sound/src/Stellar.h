//
//  Stellar.hpp
//  mySketch

#include "ofMain.h"
#include "ofApp.h"
#include <vector>

#ifndef Stellar_hpp
#define Stellar_hpp

#include <stdio.h>

class Stellar{
    
    public:
    
        Stellar();
    
        ofVec2f s_pos;
        int s_r;
        ofColor s_color;
        float increx;
        float increy;
    
        void setup();
        void draw();
        void update();
        void playSound();
        ofColor getColor();
        ofPoint getPoint();
    
        int sound_type; // 0 - 7
        ofSoundPlayer sound;
        ofColor color;
        float life;
        bool is_contact;
        float mouse_posx;
        float mouse_posy;
    float disX;
    float disY;
    float R;
};

#endif /* Stellar_hpp */
