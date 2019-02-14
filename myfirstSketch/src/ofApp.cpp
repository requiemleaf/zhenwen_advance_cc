#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mImage.load("skating.png");
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    mVideo.load("Wayne_outputfinal.mp4");
    mVideo.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    mVideo.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    mImage.draw(ofGetMouseX(),ofGetMouseY());
    ofSetRectMode(OF_RECTMODE_CENTER);
    mVideo.draw(0,0);
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
