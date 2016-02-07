/*
    Copyright (C) 2016 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once
#include "ofxDatGuiComponent.h"

class ofxDatGuiScrollView : public ofxDatGuiComponent {

    public:
    
        ofxDatGuiScrollView(string name, int nVisible = 6) : ofxDatGuiComponent(name)
        {
            mAutoHeight = true;
            mNumVisible = nVisible;
            setTheme(ofxDatGuiComponent::theme.get());
            ofAddListener(ofEvents().mouseScrolled, this, &ofxDatGuiScrollView::onMouseScrolled, OF_EVENT_ORDER_BEFORE_APP);
        }
    
    /*
        list manipulation
    */
    
        void add(string label)
        {
            int y = 0;
            if (children.size() > 0) y = children.back()->getY() + children.back()->getHeight() + mSpacing;
            children.push_back(new ofxDatGuiButton( label ));
            children.back()->setTheme(mTheme);
            children.back()->setWidth(mRect.width, 0);
            children.back()->setPosition(0, y);
            children.back()->setParentPosition(mRect.x, mRect.y);
            children.back()->onButtonEvent(this, &ofxDatGuiScrollView::onButtonEvent);
        //  cout << "ofxDatGuiScrollView :: total items = " << children.size() << endl;
            if (mAutoHeight) autoSize();
        }
    
        ofxDatGuiButton* get(int index)
        {
            return static_cast<ofxDatGuiButton*>(children[index]);
        }
    
        void swap(int index1, int index2)
        {
            if (isValidIndex(index1) && isValidIndex(index2) && index1 != index2){
                std::swap(children[index1], children[index2]);
                positionItems();
            }
        }
    
        void move(int from, int to)
        {
            if (isValidIndex(from) && isValidIndex(to) && from != to){
                auto itr_from = children.begin() + from;
                auto itr_to = children.begin() + to;
                if (itr_from < itr_to ) {
                // move down //
                    rotate(itr_from, itr_from+1, itr_to+1);
                } else if (itr_from > itr_to) {
                // move up //
                    rotate(itr_to, itr_from, itr_from+1);
                }
                positionItems();
            }   else {
                cout << "invalid move operation, check your indices" << endl;
            }
        }
    
        void move(ofxDatGuiComponent* item, int index)
        {
            for(int i=0; i<children.size(); i++){
                if (children[i] == item) {
                    move(i, index); return;
                }
            }
        }
    
        void clear()
        {
            for (auto i:children) delete i;
            children.clear();
        }
    
        void remove(int index)
        {
            if (isValidIndex(index)) {
                delete children[index];
                children.erase(children.begin()+index);
            }
            positionItems();
        }
    
        void remove(ofxDatGuiComponent* item)
        {
            for(int i=0; i<children.size(); i++){
                if (children[i] == item) {
                    delete children[i];
                    children.erase(children.begin()+i);
                    positionItems(); return;
                }
            }
        }
   
    /*
        temporary getters until mRect is implemented in ofxDatGuiComponent
    */
    
        int getX()
        {
            return mRect.x;
        }
    
        int getY()
        {
            return mRect.y;
        }

        int getWidth()
        {
            return mRect.width;
        }
    
        int getHeight()
        {
            return mRect.height;
        }
    
        int getNumItems()
        {
            return children.size();
        }
    
    /*
        list presentation
    */

        void setTheme(ofxDatGuiTheme* theme)
        {
            mTheme = theme;
            mSpacing = theme->layout.vMargin;
            mBackground = theme->color.guiBackground;
            for (auto i:children) i->setTheme(theme);
            setWidth(theme->layout.width, theme->layout.labelWidth);
        }
    
        void setWidth(int width, float labelWidth = 1)
        {
            mRect.width = width;
            for (auto i:children) i->setWidth(mRect.width, labelWidth);
            if (mAutoHeight) autoSize();
        }
    
        void setHeight(int height)
        {
            mAutoHeight = false;
            mRect.height = height;
            mView.allocate( mRect.width, mRect.height );
        }

        void setPosition(int x, int y)
        {
            mRect.x = x;
            mRect.y = y;
            for(auto i:children) i->setParentPosition(x, y);
        }
    
        void setBackgroundColor(ofColor color)
        {
            mBackground = color;
        }
    
    /*
        update & draw
    */

        void update()
        {
            for(auto i:children) i->update();
        }
    
        void draw()
        {
            ofPushStyle();
                ofFill();
            // draw a background behind the fbo //
                ofSetColor(ofColor::black);
                ofDrawRectangle(mRect);
            // draw into the fbo //
                mView.begin();
                ofClear(255,255,255,0);
                ofSetColor(mBackground);
                ofDrawRectangle(0, 0, mRect.width, mRect.height);
                for(auto i:children) i->draw();
                mView.end();
            // draw the fbo of list content //
                ofSetColor(ofColor::white);
                mView.draw(mRect.x, mRect.y);
            ofPopStyle();
        }

    private:
    
        ofFbo mView;
        ofRectangle mRect;
        ofColor mBackground;
        ofxDatGuiTheme* mTheme;
    
        int mSpacing;
        int mNumVisible;
        bool mAutoHeight;
    
        void autoSize()
        {
            mRect.height = ((mTheme->layout.height + mSpacing) * mNumVisible) - mSpacing;
            mView.allocate( mRect.width, mRect.height );
        }
    
        void onMouseScrolled(ofMouseEventArgs &e)
        {
            if (children.size() > 0 && mRect.inside(e.x, e.y) == true){
                float sy = e.scrollY * 2;
                int topY = children.front()->getY();
                int btnH = children.front()->getHeight() + mSpacing;
                int minY = mRect.height + mSpacing  - (children.size() * btnH);
                bool allowScroll = false;
                if (sy < 0){
                    if (topY > minY){
                        topY += sy;
                        if (topY < minY) topY = minY;
                        allowScroll = true;
                    }
                }   else if (sy > 0){
                    if (topY < 0){
                        topY += sy;
                        if (topY > 0) topY = 0;
                        allowScroll = true;
                    }
                }
                if (allowScroll){
                    children.front()->setPosition(0, topY);
                    for(int i=0; i<children.size(); i++) children[i]->setPosition(0, topY + (btnH * i));
                }
            }
        }
    
        void onButtonEvent(ofxDatGuiButtonEvent e)
        {
            if (scrollViewEventCallback != nullptr) {
                int i = 0;
                for(i; i<children.size(); i++) if (children[i] == e.target) break;
                ofxDatGuiScrollViewEvent e1(this, e.target, i);
                scrollViewEventCallback(e1);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void positionItems()
        {
            int y = children.front()->getY();
            for(auto i:children){
                i->setPosition(0, y);
                y = i->getY() + i->getHeight() + mSpacing;
            }
        }
    
        bool isValidIndex(int index)
        {
            return index >= 0 && index < children.size();
        }

};
