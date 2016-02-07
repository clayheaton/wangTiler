//
//  SampleMaker.cpp
//  wangTiler
//
//  Created by Clay Heaton on 2/6/16.
//
//

#include "SampleMaker.h"

SampleMaker::SampleMaker(){
    
}

SampleMaker::SampleMaker(vector<ofImage> sources, vector<int>probabilities){
    this->sourceImages       = sources;
    this->imageProbabilities = probabilities;
}

SampleMaker::~SampleMaker(){

}
