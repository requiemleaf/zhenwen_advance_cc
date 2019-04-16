#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetBackgroundAuto(false); // turns off automatic bg clearing
    ofBackground(0);
    
    std::string url = "https://data.nasa.gov/resource/y77d-th95.json";
    
    // Now parse the JSON
    bool parsingSuccessful = json.open(url);
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << json.getRawString(true);
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
    int i = 0;
    for (i = 0; i < json.size(); ++i)
    {
        
        const Json::Value& x = json[i]["geolocation"]["coordinates"][0];
        const Json::Value& y = json[i]["geolocation"]["coordinates"][1];
        const Json::Value year = json[i]["year"].asString();
        if (year == "2002-01-01T00:00:00.000" ||  year == "2003-01-01T00:00:00.000" || year == "2004-01-01T00:00:00.000" || year == "2005-01-01T00:00:00.000" || year == "2006-01-01T00:00:00.000"){
            std::string latitude = x.asString();
            float xVal = ofToFloat(latitude);
            std::string longitude = y.asString();
            float yVal = ofToFloat(longitude);
            ofLogNotice(ofToString(i)) << xVal << yVal;
            
            if (xVal != 0){
                meteorLat.push_back(xVal);
            };
            if (yVal !=0){
                meteorLong.push_back(yVal);
            }
            cout << meteorLat.size() << endl;
        }
        
        //ofLogNotice(ofToString(i)) << x << y;
        
    }
    for (int i = 0; i<meteorLat.size(); ++i){
        float xVal = ofMap(meteorLat[i], -180, 180, 0, ofGetWidth());
        float yVal = ofMap(meteorLong[i], -90, 90, 0, ofGetHeight());
        ofLogNotice("x values") << xVal;
        ofLogNotice("y values") << yVal;
        
        //path.curveTo(xVal, yVal, i);
        path.curveTo(xVal,yVal, i);
        if (i == meteorLat.size() - 1){
            
            path.close();
            path.setStrokeColor(ofColor::blue);
            path.setFillColor(ofColor::red);
            path.setFilled(true);
            path.setStrokeWidth(2);
        }
    }


    oneShot = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    }

//--------------------------------------------------------------
void ofApp::draw(){

    // anything in between ofBeginSaveScreenAsPDF(...) and ofEndSaveScreenAsPDF()
    // is saved to the file
    if( oneShot ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf");
    }
    
    ofSetColor(255);
    ofFill();
    path.draw();

    //ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 10);
    
    // Finish saving the PDF and reset oneShot to false
    // Ending the PDF tells openFrameworks to resume drawing to the screen.
    if( oneShot ){
        ofEndSaveScreenAsPDF();
        oneShot=false;
    }
    
    
//    for (int i = 0; i<meteorLat.size(); ++i){
//        float xVal1 = ofMap(meteorLat[i], -180, 180, 0, ofGetWidth());
//        float yVal1 = ofMap(meteorLong[i], -90, 90, 0, ofGetHeight());
//        float xVal2 = ofMap(meteorLat[meteorLat.size()-i], -180, 180, 0, ofGetWidth());
//        float yVal2 = ofMap(meteorLong[meteorLat.size()-i], -90, 90, 0, ofGetHeight());
//
//
//    float x0= xVal1;
//    float y0= yVal1;
//    float x1 = xVal1+50+100*cos(ofGetElapsedTimef()*1.0f);
//    float y1 = yVal1+200*sin(ofGetElapsedTimef()/3.5f);
//    float x2 = xVal1+60*cos(ofGetElapsedTimef()*2.0f);
//    float y2 = yVal1+200*sin(ofGetElapsedTimef());
//    float x3= xVal2;
//    float y3= yVal2;
//
//    ofFill();
//    ofSetHexColor(0xFF9933);
//    ofBeginShape();
//    ofVertex(x0,y0);
//    ofBezierVertex(x1,y1,x2,y2,x3,y3);
//    ofEndShape();
//    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
        if(key == 's' ){
            oneShot = true;
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
