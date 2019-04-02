//
//  Stellar.cpp
//  mySketch


#include "Stellar.h"
#include "ofApp.h"

Stellar::Stellar(){
    
    string sound_path_list[] = { "01.mp3", "02.mp3", "03.mp3", "04.mp3", "05.mp3", "06.mp3", "07.mp3"};
    
    sound_type = ofRandom(7);
    sound.load(sound_path_list[sound_type]);
    sound.setMultiPlay(true);

    sound.setVolume(20);
    
    increx = ofRandom(-15,15) / 5;
    increy = ofRandom(-15,15) / 5;
    
    s_pos.x = ofRandom(ofGetWindowWidth()/10, 9 * ofGetWindowWidth()/10);
    s_pos.y = ofRandom(ofGetWindowHeight()/10, 9 * ofGetWindowHeight()/10);
    s_r = ofRandom(120,200);
    s_color = ofColor(0, ofRandom(100,255), ofRandom(100,255), ofRandom(150,255));
};

void Stellar::draw(){
    ofFill();
    ofSetColor(s_color);
    ofDrawEllipse(s_pos.x, s_pos.y, s_r, s_r);
    
    mouse_posx = ofGetMouseX();
    mouse_posy = ofGetMouseY();
    disX = (mouse_posx - s_pos.x) * (mouse_posx - s_pos.x) ;
    disY = (mouse_posy - s_pos.y) * (mouse_posy - s_pos.y) ;
    R = (50 + s_r) * (50+ s_r);

}

void Stellar::update(){
    
    if(s_pos.x + s_r / 2 > ofGetWindowWidth() || s_pos.x - s_r / 2 < 0){
        increx = - increx;
        this->playSound();
    }
    s_pos.x = s_pos.x + increx;
    
    if(s_pos.y + s_r / 2 > ofGetWindowHeight() || s_pos.y - s_r / 2 < 0){
        increy = - increy;
        this->playSound();
    }
    s_pos.y = s_pos.y + increy;
    
}

void Stellar::playSound(){
    sound.play();
}

ofColor Stellar::getColor(){return s_color;}
ofPoint Stellar::getPoint(){return s_pos;}
