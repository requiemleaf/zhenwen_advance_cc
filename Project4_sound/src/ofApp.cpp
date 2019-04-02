#include "ofApp.h"
#include "Stellar.h"
#include "ofxGui.h"


//
float mass = 0.007; //Mass of point
float g = 9.8; //Gravity force
float time0; //Time value, used for time step computing
//Ball position and velocity
ofPoint pos, vel;

//
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowTitle("ACC");
    ofSetCircleResolution(75);
    //Set up sound sample
    sound1.load( "23.wav" ); //Load sound sample
    sound1.setMultiPlay( true );
    //Model setup
    time0 = ofGetElapsedTimef(); //Get current time
    pos = ofPoint( ofGetWidth(), 100 ); //Ball's initial position
    vel = ofPoint( 0, 0 ); //Initial velocity
    
    ofBackground(239);
    ofSetLineWidth(3);
    //ofSetCircleResolution(72);
    for (int i = 0; i < 10; i++) {
        Stellar *s = new Stellar();
        stellars.push_back(s);
        //stellars[i].setup();
    }
    
    mouse_r = 50;
 
    play.addListener(this, &ofApp::playPressed);

    //set up declared objects
    gui.setup("Parameters");
    gui.add(play.setup("CueBallplay"));
    gui.add(volume.setup("CueBallVolume",0.3f,0.0f,1.0f));
    gui.add(speed.setup("CueBallSoundSpeed",1.0f,0,5.0f));
    gui.add(volumeB.setup("BallVolume",1.0f,0.0f,1.0f));
    gui.add(speedB.setup("BallSoundSpeed",1.0f,0,2.0f));
    
    // the fft needs to be smoothed out, so I create an array of floats
    bands=128;
    fftSmooth=new float [bands];   //smooth the signal
    for (int i=0; i<bands; i++){
        fftSmooth[i]=0;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    for (Stellar *s: stellars) {
        s->update();
        ofPoint real_pos = s->getPoint();
    }
     bool bounced = updateBall();
    if ( bounced ) {
        //Start sample playing
        sound1.play();
        sound1.setVolume(0.3);
        float speed = ofMap( pos.x, 0, ofGetWidth(), 0.2, 2 );
    }
   // ofSoundUpdate();
    
    
    float * value =ofSoundGetSpectrum(bands);
    for (int i=0; i<bands; i++){
        //let the smoothed value sink to zero
        fftSmooth[i]*=0.95f;
        //take the max, either the smoothed or the incoming
        if(fftSmooth[i]<value[i]){
            fftSmooth[i]=value[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    //draw the panel
    gui.draw();
    
    sound1.setVolume(volume);
    sound1.setSpeed(speed);
    
    for (Stellar *s: stellars) {
        s->draw();
        //s->playSound();
        s->sound.setSpeed(speedB);
        s->sound.setVolume(volumeB);
        
    }    
    //ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), mouse_r, mouse_r);
    ofSetColor(0, ofRandom(100,255), ofRandom(100,255), ofRandom(150,255));
    
    ofNoFill();
       for (int i=0; i<bands; i++){
    ofDrawCircle( pos.x, 800 - pos.y, sin(fftSmooth[i])*200);
       }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


//--------------------------------------------------------------
bool ofApp::updateBall() {
    ofPushStyle();
    bool bounced = false;
   
    
    //Compute dt
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    //Compute gravity force acceleration
    //using the second Newton's law
    ofPoint acc( 0, -g/mass );
    //Change velocity and position using Euler's method
    vel += acc * dt;
    pos += vel * dt;
    
    //Check if the ball bounced off floor
    if ( pos.y < 0 ) {
        //Elastic bounce with momentum conservation
        pos.y = -pos.y+10;
        vel.y = -vel.y;
        //Set random velocity by x axe in range [-300, 500]
        vel.x = ofRandom( -300, 500 );
        bounced = true;
    }
   
    
    //Check if the ball is out of screen
    if ( pos.x < 0 ) { pos.x += ofGetWidth(); }
    if ( pos.x > ofGetWidth() ) { pos.x -= ofGetWidth(); }
    
    return bounced;
    
    ofPopStyle();
}


void ofApp::playPressed(){
    sound1.play();
}


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
