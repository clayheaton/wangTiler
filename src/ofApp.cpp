#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // TODO: Rework GUI so that it's easier to replace components as we move through stages.
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addLabel("SOURCE IMAGE SELECTION");
    gui->addTextInput("NEW IMAGE(S)", "ENTER FULL DIRECTORY PATH");
    gui->addButton("IMPORT IMAGE(S)");
    gui->addBreak()->setHeight(10.0f);
    
    
    vector<string> options = sourceImageLoader.sourceDirLabels;
    
    gui->addDropdown("SELECT AN EXISTING SOURCE IMAGE", options);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
    
    SampleMaker sm = SampleMaker(sourceImageLoader.sourceImages,sourceImageLoader.imageProbabilities);
    imageQuilter.assignSampleMaker(sm);
    
    // Application tracks state through currentStatus
    currentStatus = viewingSource;
    
    ofSetBackgroundColorHex(0x000000);
}

//--------------------------------------------------------------
void ofApp::update(){
    gui->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColorHex(0x000000);
    gui->draw();
    
    switch (currentStatus) {
        case viewingSource:
            drawViewingSource();
            break;
        case viewingQuilt:
            drawViewingQuilt();
            break;
        case viewingTiles:
            drawViewingTiles();
            break;
        case exportCompleted:
            drawExportCompleted();
            break;
            
        default:
            break;
    }
}

void ofApp::drawViewingSource(){
    ofSetBackgroundColorHex(0x000000);

    imageQuilter.displaySampleImages();

}

void ofApp::drawViewingQuilt(){
    ofSetBackgroundColorHex(0x000000);

}

void ofApp::drawViewingTiles(){
    ofSetBackgroundColorHex(0x000000);

}

void ofApp::drawExportCompleted(){
    ofSetBackgroundColorHex(0x000000);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//-----------------------------------------------------------
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
//    if (currentStatus == viewingSource) {
//        currentStatus = viewingQuilt;
//    } else if (currentStatus == viewingQuilt){
//        currentStatus = viewingTiles;
//    } else if (currentStatus == viewingTiles) {
//        currentStatus = exportCompleted;
//    } else if(currentStatus == exportCompleted) {
//        // Exit the application
//        ofExit();
//    }
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

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    sourceImageLoader.activeDirIndex = e.child;
    sourceImageLoader.changeSource();
    
    imageQuilter.sampleMaker.sourceImages = sourceImageLoader.sourceImages;
    imageQuilter.sampleMaker.imageProbabilities = sourceImageLoader.imageProbabilities;
    
    cout << sourceImageLoader.sourceDirectories[e.child] << endl;
}
