//
//  ImageQuilter.cpp
//  wangTiler
//
//  Created by Clay Heaton on 2/6/16.
//
//

#include "ImageQuilter.h"

ImageQuilter::ImageQuilter(){
    quilted = false;
};

ImageQuilter::~ImageQuilter(){
    
};



/* Evaluate samples to see which is widest */
void ImageQuilter::assignSampleMaker(SampleMaker sm){
    sampleMaker = sm;
    
    maxW      = -1;
    maxWIndex = -1;
    
    for (int i = 0; i < sampleMaker.sourceImages.size(); i++) {
        ofImage si = sampleMaker.sourceImages[i];
        
        if(si.getWidth() > maxW) {
            maxW = si.getWidth();
            maxWIndex = i;
        }
    }
};

/* Show the samples before proceeding with quilting. */
void ImageQuilter::displaySampleImages(){
    int spacing = 8;
    int origSpacing = (sampleMaker.sourceImages.size() - 1) * (spacing/2.0);
    
    float xPos = (ofGetWindowWidth() / 2) - ((sampleMaker.sourceImages[maxWIndex].getWidth()/2) * sampleMaker.sourceImages.size()) - origSpacing;
    float yPos = (ofGetWindowHeight() / 2) - sampleMaker.sourceImages[maxWIndex].getHeight()/2;
    
    for (int i = 0; i < sampleMaker.sourceImages.size(); i++) {
        ofImage si = sampleMaker.sourceImages[i];
        si.draw(xPos,yPos);
        xPos += sampleMaker.sourceImages[maxWIndex].getWidth() + spacing;
    }
}