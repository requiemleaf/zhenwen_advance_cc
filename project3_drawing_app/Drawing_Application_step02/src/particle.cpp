#include "particle.hpp"
#include <ofMain.h>


Particles::Particles() = default;

void Particles::setup(ofImage _img, int _scl, int _col){
    img = _img;
    scl = _scl;
    col = _col;
    pos = ofVec2f(floor(ofRandom(ofGetWidth())), floor(ofRandom(ofGetHeight())));
    prePos = pos;
    vel = ofVec2f(0,0);
    acc = ofVec2f(0,0);
}

void Particles::update(){
    vel += acc;
    // set a limit of the max velocity
    ofVec2f limitedVel = vel.limit(20);
    // add the limited velocity to position
    pos += limitedVel;
    acc = acc * 0;
}


void Particles::draw(){
    
    //ofSetColor(50,20);
//    ofPixels pixels = img.getPixels();
//
//    int pIndex = floor(pos.x) + floor(pos.y) * int(img.getWidth());
//
//    int red = pixels[pIndex * 3];
//    int green = pixels[pIndex * 3 + 1];
//    int blue = pixels[pIndex * 3 + 2];
    ofColor color = img.getColor(floor(pos.x), floor(pos.y));
    //cout << "r is " << color.r << endl;
    
    //int greyscale = round(red * 0.222 + green * 0.707 + blue * 0.071);
    int greyscale = round(color.r * 0.222 + color.g * 0.707 + color.b * 0.071);
    //cout << "greyscale is " << greyscale << endl;
    if ( greyscale < 200 ) {
        ofSetColor(greyscale, 30);
        ofDrawLine(pos.x, pos.y, prePos.x, prePos.y);
    }
    prePos = pos;
}

void Particles::follow(vector<ofVec2f> _flowField){
    int x = floor(pos.x / scl);
    int y = floor(pos.y / scl);
    int index = abs(x + y * col);
    //cout << "col is " << col << endl;
    //cout << "index is " << index << endl;
    ofVec2f force = _flowField[index];
        //cout << "force is " << force << endl;
    applyForce(force);
}

void Particles::applyForce(ofVec2f _force){
    acc += _force;
    //cout << "acc is " << acc << endl;
}

void Particles::updatePrev(){
    prePos.x = pos.x;
    prePos.y = pos.y;
}

void Particles::edges(){
    if ( pos.x > ofGetWidth() ) {
        pos.x = 0;
        updatePrev();
        
    }
    if ( pos.x < 0 ) {
        pos.x = ofGetWidth();
        updatePrev();
    }
    if ( pos.y > ofGetHeight() ) {
        pos.y = 0;
        updatePrev();
    }
    if ( pos.y < 0 ) {
        pos.y = ofGetHeight();
        updatePrev();
    }
}
