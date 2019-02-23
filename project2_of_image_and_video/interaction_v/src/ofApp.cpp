#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    video.load("dog.mp4");
    video.play();
    
    for ( int i=0; i<16; i++ ) {
        table[i] = ofRandom( 0, 255 );
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();     //decode the new frame if needed
    
    if (functionOne ==true){
        //Do computing only if a new frame was obtained
        if ( video.isFrameNew() ) {
            //Push the new frame to the beginning of the frame list
            frames.push_front( video.getPixels() );
        }
        
        //It is possible that video player did
        //not finish decoding the first frame at first testApp::update()
        //calling, so we need check, if there are frames
        if ( !frames.empty() ) {
            //Now constructing the output image in imagePixels
            
            //If imagePixels is not initialized yet, then initialize
            //it by copying from any frame.
            //This is the simplest way to create a pixel array
            //of the same size and type
            if ( !imagePixels.isAllocated() ) {
                imagePixels = frames[0];
            }
            
            //Getting video frame size for formulas simplification
            int w = frames[0].getWidth();
            int h = frames[0].getHeight();
            
            //Scan all the pixels
            for (int y=0; y<h; y++) {
                for (int x=0; x<w; x++) {
                    
                    //Get "slit" pixel color
                    ofColor color = getSlitPixelColor( x, y );
                    
                    //Set pixel to image pixels
                    imagePixels.setColor( x, y, color );
                }
            }
            //Set new pixels values to the image
            image.setFromPixels( imagePixels );
        }
    }
    
    if (functionTwo == true){
        //Do computing only if a new frame was obtained
        if ( video.isFrameNew() ) {
            //Getting pixels
            ofPixels pixels = video.getPixels();
            
            //Scan all the pixels
            for (int y=0; y<pixels.getHeight(); y++) {
                for (int x=0; x<pixels.getWidth(); x++) {
                    //Getting pixel (x,y) color
                    ofColor col = pixels.getColor( x, y );
                    
                    //Change color components of col
                    //using table
                    col.r = table[ col.r/4 ];
                    col.g = table[ col.g/4 ];
                    col.b = table[ col.b/4 ];
                    
                    if ( fmod(ofGetElapsedTimef(),2.0) == 0){
                        col.r = table[ col.r/32 ];
                        col.g = table[ col.g/32 ];
                        col.b = table[ col.b/32 ];
                    }
                    
                    //Set the color back to the pixel (x,y)
                    pixels.setColor( x, y, col );
                }
            }
            //Set pixel array to the image
            image2.setFromPixels( pixels );
        }
    }
    
    if (functionSix == true) {
        if (video.isFrameNew()) {
            //getting pixels
            ofPixels pixels = video.getPixels();
            
            //scan all the pixels
            for (int y = 0; y < pixels.getHeight(); y++){
                for (int x = 0; x < pixels.getWidth(); x++){
                    //getting pixel colot
                    ofColor col = pixels.getColor(x, y);
                    
                    //calculate the distance between each poxel and
                    //the mouse's position
                    //change pixels' color
                    float d = ofDist(x, y, ofGetMouseX(), ofGetMouseY());
                    float adjustbrightness = ofMap(d, 0, 100, 8, 0);
                    col.r *= adjustbrightness;
                    col.g *= adjustbrightness;
                    col.b *= adjustbrightness;
                    
                    //set color back to pixel
                    pixels.setColor(x, y, col);
                }
            }
            //set pixel array to the image
            image3.setFromPixels(pixels);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);    //set the color of background
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255,255,255);
    video.draw(0,0);    //draw the current video frame
    
    if(functionOne == true){
        image.draw(0,0);
    }
    
    if(functionTwo == true){
        ofSetColor(255,255,255);
        image2.draw(0,0);
    }
    
    if(functionThree== true){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(100*i, 80*j, 10);
                //isolate the translation matrix
                ofPushMatrix();     //stroe the transformation matrix
                ofTranslate(i*ofGetWidth()/2, j*ofGetHeight()/2);
                //ofRotateXDeg(ofGetElapsedTimeMillis()*0.05);
                //ofRotateYRad(10);
                ofRotateZDeg(ofGetElapsedTimeMillis()*0.05);
                ofScale(0.5f, 0.5f);    //change the video's size
                video.draw(0,0);
                ofPopMatrix();  //restore the transformation
            }
        }
    }
    
    if(functionFour==true){
        //getting pixels
        ofPixels pixels = video.getPixels();
        
        // scan the pixels
        for (int i = 4; i < pixels.getWidth()*2; i+=8){
            for (int j = 4; j < pixels.getHeight()*2; j+=8){
                // using the red pixel to control the size of a circle.
                unsigned char r = pixels[(j * 320 + i)*pixels.getNumChannels()];
                float val = 1 - ((float)r / 255.0f);
                // set the color by the position of the mouse
                ofSetColor(ofGetMouseX(), ofGetMouseY(), 0);
                // draw the circle
                ofDrawCircle(i/2,j/2,15*val);
            }
        }
    }
    
    if (functionFive == true) {
        //getting the video's pixels
        ofPixels &pixels = video.getPixels();
        
        //define variables w,h equal to frame width and height
        int w = pixels.getWidth();
        int h = pixels.getHeight();
        
        //define circle variables
        int step = 20;
        int r = ofMap(ofGetMouseX(), 0, ofGetWidth(), 5, 10);
        int locx = 0;
        int locy = 0;
        //draw circle
        for (int x = 0; x < w; x = x + step) {
            ofColor color = pixels.getColor(x , h/2);
            ofSetColor(color);
            for (int i = 0; i < w; i = i + step)
                ofDrawCircle(locx, locy, r);
            for (int j = 0; j < h; j = j + step) {
                ofDrawCircle(locx, locy, r);
                locy = locy + step;
            }
            locx = locx + step;
            locy = 0;
        }
    }
    
    if(functionSix == true){
        image3.draw(0,0);
    }

}

ofColor ofApp::getSlitPixelColor( int x, int y ){
    //Main formula for connecting (x,y) with frame number
    float f = x/8;
    
    //Compute two frame numbers surrounding f
    int i0 = int( f );
    int i1 = i0 + 1;
    
    //Compute weights of the frames i0 and i1
    float weight0 = i1 - f;
    float weight1 = 1 - weight0;
    
    //Limiting frame numbers by range from 0 to n=frames.size()-1
    int n = frames.size() - 1;
    i0 = ofClamp( i0, 0, n );
    i1 = ofClamp( i1, 0, n );
    
    //Getting the frame colors
    ofColor color0 = frames[ i0 ].getColor( x, y );
    ofColor color1 = frames[ i1 ].getColor( x, y );
    
    //Interpolate colors - this is the function result
    ofColor color = color0 * weight0 + color1 * weight1;
    
    return color;
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '1':
            functionOne=true;
            break;
        case '2':
            functionTwo=true;
            break;
        case '3':
            functionThree=true;
            break;
        case '4':
            functionFour=true;
            break;
        case '5':
            functionFive=true;
            break;
        case '6':
            functionSix=true;
            break;

        case 'r':
            functionOne=false;
            functionTwo=false;
            functionThree=false;
            functionFour=false;
            functionFive=false;
            functionSix=false;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    if (functionFour == true) {
        if(functionFour==true){
            //set the speed
            float pct = (float)x / (float)ofGetWidth();
            float speed = (2 * pct - 1) * 1.5f;
            //map the speed value to an output range.
            float newSpeed=ofMap(speed, -1.5, 1.5, 1 ,2);
            video.setSpeed(newSpeed);
        }
    }

    if (functionFive == true) {
        //connect the speed variable with mouse X
        float mappedSpeed = ofMap(float(x), 0.0f, ofGetWidth(), 0, 2.0f);
        video.setSpeed(mappedSpeed);
        //connect the zoom factor with mouse Y
        zoomFactor = ofMap(float(y), 0.0f, ofGetHeight(), 0, 2.0f);
    }
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
