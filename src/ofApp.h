#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVideoPlayer myPlayer;
    ofImage canvas;
    ofImage scanline;
    bool isVerticalScan;
    int scanWidth;
    int scanHeight;
    int slitWidth;
    int scanLength;
    
    int counter;
    ofDirectory dir;
    int numFiles;
    int movieIndex;
    
    void initSlitScan(string s);
    
    string movieFileName;
    string imageFileName;
    
    
    void copyScanline();
    string getImageFileNameFromMovieFileName(string inputString);
    
    
};

