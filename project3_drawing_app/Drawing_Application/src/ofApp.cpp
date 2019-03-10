#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mVideoGrabber.setVerbose(true);
    mVideoGrabber.setup(320, 240);
    
    mFbo.allocate(mVideoGrabber.getWidth(), mVideoGrabber.getHeight(), GL_RGBA);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    mVideoGrabber.update();
//    if(mVideoGrabber.isFrameNew()){
//    }
    
    auto tex =mVideoGrabber.getTexture();
    mFbo.begin();
    ofClear(255,255,255,255);
    tex.draw(0,0);
    mFbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    mFbo.draw(ofGetWidth()-mVideoGrabber.getWidth()/2, ofGetHeight()-mVideoGrabber.getHeight()/2,mVideoGrabber.getWidth()/2,mVideoGrabber.getHeight()/2);
    
//    camTex.draw(0, ofGetHeight()-mVidGrabber.getHeight()/2, ofGetWidth()-mVidGrabber.getWidth()/2, ofGetHeight()-mVidGrabber.getHeight()/2);
    
    colorImg.draw(0, 0, ofGetWidth()-mVideoGrabber.getWidth()/2, ofGetHeight()-mVideoGrabber.getHeight()/2);
    grayImage.draw(0, 0, ofGetWidth()-mVideoGrabber.getWidth()/2, ofGetHeight()-mVideoGrabber.getHeight()/2);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
//        case 't':
//            camTex.loadData(mVidGrabber.getPixels());
//            break;
        case 'p':
            colorImg.setFromPixels(mVideoGrabber.getPixels());    //grab the image from the webcam
            grayImage=colorImg; //grayscale the image
            break;
    }
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
