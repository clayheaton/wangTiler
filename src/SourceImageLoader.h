//
//  SourceImageLoader.h
//  wangTiler
//
//  Created by Clay Heaton on 2/6/16.
//
//

#pragma once

#include "ofMain.h"

class SourceImageLoader {
public:
    SourceImageLoader();
    ~SourceImageLoader();
    
    void changeSource();
    
    vector<string>  sourceDirectories;
    vector<string>  sourceDirLabels;
    
    int activeDirIndex;
    
    vector<ofImage> sourceImages;
    vector<int>     imageProbabilities;
};