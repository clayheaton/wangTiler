//
//  ImageQuilter.h
//  wangTiler
//
//  Created by Clay Heaton on 2/6/16.
//
//

#pragma once

#include "ofMain.h"
#include "SampleMaker.h"

class ImageQuilter {
public:
    ImageQuilter();
    ~ImageQuilter();
    
    void assignSampleMaker(SampleMaker sm);
    void displaySampleImages();
    int widthOfWidestSample();
    
    bool quilted;
    
    SampleMaker sampleMaker;
    
    vector<ofImage> images;
    vector<int>     imageProbabilities;
    
    int maxW, maxWIndex;
};