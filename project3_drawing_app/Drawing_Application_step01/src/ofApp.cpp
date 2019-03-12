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
    auto tex = mVideoGrabber.getTexture();
    mFbo.begin();
    ofClear(255, 255, 255, 255);
    tex.draw(0, 0);
    mFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    mFbo.draw(ofGetWidth() - mVideoGrabber.getWidth() / 2, ofGetHeight() - mVideoGrabber.getHeight() / 2, mVideoGrabber.getWidth() / 2, mVideoGrabber.getHeight() / 2);
    if (currentMode=="draw") {
        grayImage.draw(0, 0, ofGetWidth() - mVideoGrabber.getWidth() / 2, ofGetHeight() - mVideoGrabber.getHeight() / 2);
    }
    else if (currentMode == "diff") {
        grayFrame1.draw(0, 0, ofGetWidth() - mVideoGrabber.getWidth() / 2, ofGetHeight() - mVideoGrabber.getHeight() / 2);
        grayFrame2.draw(0, 0, ofGetWidth() - mVideoGrabber.getWidth() / 2, ofGetHeight() - mVideoGrabber.getHeight() / 2);
    }
    else if (currentMode == "blur") {
        float maxW = ofGetWidth() - mVideoGrabber.getWidth() / 2;
        float maxH = ofGetHeight() - mVideoGrabber.getHeight() / 2;
        for (int i = 0; i < blurImgs.size(); i++) {
            float x = (maxW / blurImgs.size()*i)/2;
            float y = (maxH / blurImgs.size()*i)/2;
            float w = maxW - (maxW / blurImgs.size())*i;
            float h = maxH - (maxH / blurImgs.size())*i;
            blurImgs[i].draw(x, y, w, h);
        }
    }
    // save image region
    imgSave.grabScreen(0, 0, ofGetWidth() - mVideoGrabber.getWidth() / 2, ofGetHeight() - mVideoGrabber.getHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            // press space to capture
            if (currentMode == "draw") {
                colorImg.setFromPixels(mVideoGrabber.getPixels());    //grab the image from the webcam
                grayImage = colorImg;
                grayImage.brightnessContrast(5, ofRandom(5, 10));
            }
            else if (currentMode == "diff") {
                colorImg.setFromPixels(mVideoGrabber.getPixels());    //grab the image from the webcam
                if (frameCounter == 0) {
                    grayFrame2.clear(); // clear any previous frame
                    grayFrame1 = colorImg;
                    frameCounter += 1;
                }
                else if (frameCounter == 1) {
                    grayFrame2 = colorImg;
                    grayFrame2.absDiff(grayFrame1);
                    frameCounter = 0;
                }
            }
            else if (currentMode == "blur") {
                if (blurCount>=0) {
                    colorImg.setFromPixels(mVideoGrabber.getPixels());
                    colorImg.blurGaussian(blurCount);
                    blurImgs.push_back(colorImg);
                    blurCount -= 1;
                }
                else {
                    blurImgs.clear();
                    blurCount = 30;
                }
            }
            break;
        case '1':
            // press 1 to start drawing
            currentMode = "draw";
            break;
        case '2':
            // press 2 for abs diff mode
            currentMode = "diff";
            break;
        case '3':
            currentMode = "blur";
            break;
        case OF_KEY_RETURN:
            // press enter to save image
            imgSave.save("img"+to_string(imgSaveNum)+".jpg");
            imgSaveNum += 1;
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
