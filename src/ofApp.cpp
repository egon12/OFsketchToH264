#include "ofApp.h"
#include <x264.h>
#include "movie/MovieSaver.hpp"

PointsGroup *pointsGroup;
Points* points;
ofImage img;
ofPixels pixels;
ofImage graphic;
MovieSaver *movieSaver;
bool start = true;

//--------------------------------------------------------------
void ofApp::setup(){

    pointsGroup = new PointsGroup();
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    movieSaver = new MovieSaver(
                                "/tmp/100rgb/a.264",
                                ofGetWidth(),
                                ofGetHeight()
                                );
    
    ofSetFrameRate(24);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);

    int i = 0;
    for (auto const &ps: pointsGroup->get()) {
        for (auto const &p: ps->get()) {
            ofSetColor(ofColor::fromHsb(i++ % 255, 255, 255));
            ofDrawLine(0,0,p.x, p.y);
        }
    }
    
    if (start) {
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        pixels = img.getPixels();
        auto p = pixels.getData();
        movieSaver->addFrame(p);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == OF_KEY_LEFT) {
        start = false;
        delete movieSaver;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    points->add(glm::vec2(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    points = new Points();
    pointsGroup->add(points);
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
