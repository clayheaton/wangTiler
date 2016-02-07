//
//  SampleMaker.h
//  wangTiler
//
//  Created by Clay Heaton on 2/6/16.
//
//

#pragma once

#include "ofMain.h"

class SampleMaker {
public:
    SampleMaker();

    SampleMaker(vector<ofImage> sources, vector<int>probabilities);
    ~SampleMaker();
    
    vector<ofImage> sourceImages;
    vector<int>     imageProbabilities;
};