//
//  SourceImageLoader.cpp
//  wangTiler
//
//  Created by Clay Heaton on 2/6/16.
//
//

#include "SourceImageLoader.h"

SourceImageLoader::SourceImageLoader(){
    
    string path = "sources";
    ofDirectory dir(path);
    dir.listDir();
    
    // Store the directories and the names of them.
    for(int i = 0; i < dir.size(); i++){
        vector<string> results = ofSplitString(dir.getPath(i), "/");
        sourceDirectories.push_back(dir.getPath(i));
        sourceDirLabels.push_back(results[1]);
    }
    
    // Load defaults
    // Grass is the default
    activeDirIndex = 1;
    changeSource();
};

void SourceImageLoader::changeSource(){
    string defaultPath = sourceDirectories[activeDirIndex];
    ofDirectory defaultDir(defaultPath);
    defaultDir.listDir(); // Make this specific to images
    
    int prob = 100 / defaultDir.size();
    
    // Empty the vectors and repopulate
    sourceImages.clear();
    imageProbabilities.clear();
    
    for (int i = 0; i < defaultDir.size(); i++) {
        ofImage ofi;
        ofi.load(defaultDir.getPath(i));
        sourceImages.push_back(ofi);
        imageProbabilities.push_back(prob);
    }
};

SourceImageLoader::~SourceImageLoader(){
    
};
