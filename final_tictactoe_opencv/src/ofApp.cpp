#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    w = 640;
    h = 480;
    
    movie.initGrabber(w, h);   // open default webcam @ 640x480
    
    //reserve memory for cv images
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filtered1.allocate(w, h);
    filtered2.allocate(w, h);
    
    gameover==false;
}

//--------------------------------------------------------------
void ofApp::initgame(){
    //x(red) starts first
    playerturn = 1;
    
    //clear the matrix
    for(int i = 0; i <= 2; i++){
        for(int j = 0; j <= 2; j++){
            matrix[i][j] = 0;
        }
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);   // specify clear values for the color buffers
    glColor3f(0, 0, 0); //Sets the current color.
    
    if(checkifwin() == true){
        
        //the player who made the previous move is the winner
        if(playerturn == 1){
            gameover = true;
            result = 2; //player2 wins
        }
        else{
            gameover = true;
            result = 1; //player1 wins
        }
    }
    
    else if(checkifdraw() == true){
        gameover = true;
        result = 0;
    }
    
    movie.update();
    
    if (movie.isFrameNew()) {
        
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels().getData(), w, h);
        //mirror horizontal
        rgb.mirror(false,false);
        //duplicate rgb
        hsb = rgb;
        //Convert the image into an hsb image
        hsb.convertRgbToHsv();
        //store the three channels as grayscale images
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            //findHue1
            filtered1.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue1-2,findHue1+2) ? 255 : 0;
            //findHue2
            filtered2.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue2-2,findHue2+2) ? 255 : 0;
        }
        
        filtered1.flagImageChanged();
        filtered2.flagImageChanged();
        
//        set the contrast of the image
//        filtered1.threshold(30);
//        filtered2.threshold(30);
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        //contourFinder1.findContours(ofxCvGrayscaleImage &input, int minArea, int maxArea, int nConsidered, bool bFindHoles)
        contourFinder1.findContours(filtered1, w*h/100, w*h/20, 4, false,true);
        contourFinder2.findContours(filtered2, w*h/100, w*h/20, 4, false,true);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw the checkerboard
    glBegin(GL_LINES);
    glColor3f(107, 114, 124);
    //2 vertical lines
    glVertex2f(ofGetWidth()/2+w/3, 0);
    glVertex2f(ofGetWidth()/2+w/3, h);
    glVertex2f(ofGetWidth()/2+w*2/3, h);
    glVertex2f(ofGetWidth()/2+w*2/3, 0);
    //2 horizontal lines
    glVertex2f(ofGetWidth()/2, h/3);
    glVertex2f(ofGetWidth(), h/3);
    glVertex2f(ofGetWidth()/2, h*2/3);
    glVertex2f(ofGetWidth(), h*2/3);
    glEnd();
    
    //draw the x and o
    for(int i = 0; i <= 2; i++){
        for(int j = 0; j <= 2; j++){
            if(matrix[i][j] == 1) //if it is 1 then draw x
            {
                ofSetColor(255, 0, 0);
                glLineWidth(10.0f);
                glBegin(GL_LINES);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 - h/3*1/4, h/6 + i * h/3 - h/3*1/4);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 + h/3*1/4, h/6 + i * h/3 + h/3*1/4);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 - h/3*1/4, h/6 + i * h/3 + h/3*1/4);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 + h/3*1/4, h/6 + i * h/3 - h/3*1/4);
                glEnd();
            }
            else if(matrix[i][j] == 2) //if it is 2 then draw o
            {
                ofSetColor(0, 0, 255);
                glLineWidth(10.0f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 - h/3*1/4, h/6 + i * h/3 - h/3*1/4);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 - h/3*1/4, h/6 + i * h/3 + h/3*1/4);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 + h/3*1/4, h/6 + i * h/3 + h/3*1/4);
                glVertex2f(ofGetWidth()/2+w/6 + j * w/3 + h/3*1/4, h/6 + i * h/3 - h/3*1/4);
                glEnd();
            }
        }
    }
    
    //draw the sdescription
    ofPushMatrix();
    ofTranslate(640,0);
    ofSetColor(255, 255, 255);
    
    if(gameover == true){
        
        ofDrawBitmapString("Game Over", ofGetWidth()/4-40, 210);
        
        if(result == 0)
            ofDrawBitmapString("Its a draw", ofGetWidth()/4-30, 235);
        
        if(result == 1)
            ofDrawBitmapString("Player1 wins", ofGetWidth()/4-50, 235);
        
        if(result == 2)
            ofDrawBitmapString("Player2 wins", ofGetWidth()/4-50, 235);
        
        ofDrawBitmapString("Do you want to continue (y/n)", ofGetWidth()/4-100, 260);
    }
    ofPopMatrix();
    
    
    glLineWidth(1.0f);
    ofSetColor(255,255,255);
    //draw all cv images
    rgb.draw(0,0);
    //hsb.draw(640,0);
    //hue.draw(0,240);
    //sat.draw(320,240);
    //bri.draw(640,240);
    //filtered1.draw(0,0);
    contourFinder1.draw(0,0);
    contourFinder2.draw(0,0);
    
    //draw red circles for found blobs
    for (int i=0; i<contourFinder1.nBlobs; i++) {
        
        for (int i=0; i<contourFinder2.nBlobs; i++) {
                
            int x1= contourFinder1.blobs[i].centroid.x;
            int y1= contourFinder1.blobs[i].centroid.y;
            int x2= contourFinder2.blobs[i].centroid.x;
            int y2= contourFinder2.blobs[i].centroid.y;
                
            //draw red circles for found blobs
            ofSetColor(255, 0, 0);
            ofDrawCircle(x1, y1, 10);
                
            //draw blue circles for found blobs
            ofSetColor(0, 0, 255);
            ofDrawCircle(x2, y2, 10);
                
            ofLogNotice() <<x1<< ": " << y1;
            ofLogNotice() <<x2<< ": " << y2;
            

            // puts the x or o on the blank box
            if(gameover == false){
                
                if(playerturn == 1){
                    
                    if(matrix[3*(y1 - 50) / h][3*x1 / w] == 0){
                        matrix[3*(y1 - 50) / h][3*x1 / w] = 1;
                        playerturn = 2;
                    }
                }
                
                else{
                    
                    if(matrix[3*(y2 - 50) / h][3*x2 / w] == 0){
                        
                        matrix[3*(y2 - 50) / h][3*x2 / w] = 2;
                        playerturn = 1;
                    }
                }
            }
        }
    }

    //draw the grid on the movie
    glBegin(GL_LINES);
    glColor3f(107, 114, 124);
    //2 vertical lines
    glVertex2f(w/3, 0);
    glVertex2f(w/3, h);
    glVertex2f(w*2/3, h);
    glVertex2f(w*2/3, 0);
    //2 horizontal lines
    glVertex2f(0, h/3);
    glVertex2f(ofGetWidth()/2, h/3);
    glVertex2f(0, h*2/3);
    glVertex2f(ofGetWidth()/2, h*2/3);
    glEnd();
    
    //print data
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    reportStream << "red blobs found " << contourFinder1.nBlobs << "   " << "red hue value " << findHue1 <<endl
    << "blue blobs found " << contourFinder2.nBlobs << "  " << "blue hue value " << findHue2 <<endl;
    ofDrawBitmapString(reportStream.str(), 20, 500);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int mx = mouseX % w;
    int my = mouseY % h;
    
    switch(key){
        case 'y':
            if(gameover == true){
                
                gameover = false;
                initgame();
            }
            break;
        case 'n':
            if(gameover == true)
                ofExit();
            break;
        case '1':
            findHue1 = hue.getPixels()[my*w+mx];
            break;
        case '2':
            findHue2 = hue.getPixels()[my*w+mx];
            break;
        case 'r':
            gameover= false;
            initgame();
            break;
    }
}


//--------------------------------------------------------------
bool ofApp::checkifwin(){
    int i, j;
    
    //check if there are horizontal win i.e if there is any row that has same value
    for(i = 0; i <= 2; i++){
        
        for(j = 1; j <= 2; j++){
            
            if(matrix[i][0] != 0 && matrix[i][0] == matrix[i][j]){
                
                if(j == 2)
                    return true;
            }
            else
                break;
        }
    }
    
    //check if there are vertical win i.e if there is any column that has same value
    for(i = 0; i <= 2; i++){
        
        for(j = 1; j <= 2; j++){
            
            if(matrix[0][i] != 0 && matrix[0][i] == matrix[j][i]){
                
                if(j == 2)
                    return true;
            }
            else
                break;
        }
    }
    
    //check if there is any diagonal win i.e. if there is any diagonals that has same value
    for(i = 1; i <= 2; i++){
        
        if(matrix[0][0] != 0 && matrix[0][0] == matrix[i][i]){
            
            if(i == 2)
                return true;
        }
        else
            break;
    }
    
    for(i = 1; i <= 2; i++){
        
        if(matrix[2][0] != 0 && matrix[2][0] == matrix[2 - i][i]){
            
            if(i == 2)
                return true;
        }
        else
            break;
    }
}


//--------------------------------------------------------------
bool ofApp::checkifdraw(){
    int i, j;
    bool draw;
    
    for(i = 0; i <= 2; i++){
        
        for(j = 0; j <= 2; j++){
            
            if(matrix[i][j] == 0)
                return false;
        }
    }
    return true;
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
