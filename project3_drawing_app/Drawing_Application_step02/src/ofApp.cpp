#include "ofApp.h"
#include <particle.hpp>

//--------------------------------------------------------------
void ofApp::setup(){
    // set framerate
    ofSetFrameRate(60);
    
    ofSetBackgroundAuto(false);
    
    ofBackground(255, 255, 255);
    
    // load the test image
    //testImg.load("bottle02.jpg");
    //testImg.load("../../../hw_03_drawing_step01/bin/data/img0.jpg");
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("jpg");
    //populate the directory object
    int folderLength = dir.listDir();
    cout << "array Length is " << folderLength << endl;
    
    for ( int i = 0; i < folderLength; i ++ ) {
        string fileName = "../../../hw_03_drawing_step01/bin/data/img" + ofToString(i) + ".jpg";
        ofImage img;
        img.load(fileName);
        myImages.push_back(img);
    
    }
    
    int rIndex = floor(ofRandom(folderLength));
    testImg = myImages[rIndex];
    
    
    // add particles to the array
    for ( int i = 0; i < 1000; i ++ ) {
//        Particle p;
//        p.setup();
//        particles.push_back(p);
        particles.push_back( make_shared<Particles>() );
    }
    
    for (int i = 0; i < particles.size(); i ++ ) {
        particles[i] -> setup(testImg, scl, 80);
    }
    
    // build grids
    col = floor(ofGetWidth()/scl);
    row = floor(ofGetHeight()/scl);
    //std::cout << "row: " << row << endl;
    //std::cout << "column: " << col << endl;
    flowField.resize(col * row);
}

//--------------------------------------------------------------
void ofApp::update(){
//    for (int i = 0; i < particles.size(); i ++ ) {
//
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // draw the image
    float xOff = 0;
    for ( int x = 0; x < col; x ++ ) {
        float yOff = 0;
        for ( int y = 0; y < row; y ++ ) {
            int index = x + y * col;
            // getting a angle
            float angle = ofNoise(xOff, yOff, zOff) * 360;
            //std::cout << "angle is " << angle << endl;
            // create a vector based on the angle and save it to flowField
            ofVec2f v = ofVec2f(1,0).getRotated(angle);
            flowField[index] = v;
            // draw a line based on the angle
//            ofPushView();
//                ofTranslate(x * scl, y * scl);
//                ofRotateZDeg(ofVec2f(1,0).angle(v));
//                ofSetColor(50, 100);
//                ofSetLineWidth(2);
//                ofDrawLine(0, 0, scl, 0);
//            ofPopView();
            yOff += inc;
        }
        xOff += inc;
    }
    zOff += 0.01;
    
    // draw the particles
    for (int i = 0; i < particles.size(); i ++ ) {
        particles[i] -> follow(flowField);
        particles[i] -> update();
        particles[i] -> edges();
        particles[i] -> draw();
    }
    
    // draw the image
    //testImg.draw(0,0,ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
