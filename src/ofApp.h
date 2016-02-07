
// Lato fonts from http://www.latofonts.com/ released under OFL (Open Font License)

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ImageQuilter.h"
#include "SourceImageLoader.h"

enum AppStatus {viewingSource = 0, viewingQuilt = 1, viewingTiles = 2, exportCompleted = 3};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void drawViewingSource();
    void drawViewingQuilt();
    void drawViewingTiles();
    void drawExportCompleted();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    AppStatus         currentStatus;
    SourceImageLoader sourceImageLoader;
    ImageQuilter      imageQuilter;
    
    ofxDatGui* gui;
//    ofxDatGuiFolder* sourceFolder;
//    ofxDatGuiFolder* quiltingFolder;
//    ofxDatGuiFolder* tilingFolder;
//    ofxDatGuiFolder* finalFolder;
};
