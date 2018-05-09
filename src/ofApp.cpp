#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(20, 0, 0);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(3000);
    
    string folderPath = "/Users/hollt054/Desktop/Videos_backup/20170810_iceland/retime/foo";
    ///Users/hollt054/Desktop/Videos_backup/20170530_boardwalk/tmp";
    ///Users/hollt054/Desktop/Videos_backup/20180413_metro";
    ///Users/hollt054/Desktop/Videos_backup/kronos_output";
    dir.open(folderPath);
    dir.allowExt("mov");
    numFiles = dir.listDir();
    movieIndex = 0;
    
    for (int i=0; i<numFiles; ++i)
    {
        cout << "Path at index [" << i << "] = " << dir.getName(i) << endl;
    }
    
    string firstFile = dir.getPath(movieIndex++);
    initSlitScan(firstFile);
}

//--------------------------------------------------------------
void ofApp::update(){
    myPlayer.nextFrame();
    myPlayer.update();
    
    copyScanline();
    
    if(counter == scanLength){
        std::cout << counter << " " << scanLength << " saving" << imageFileName << "\n";
        canvas.saveImage(imageFileName);
        initSlitScan(dir.getPath(movieIndex++));
    }
    counter ++;
}


//--------------------------------------------------------------
void ofApp::draw(){
    if(counter%1==0){
        //canvas.draw(0,0, scanWidth/5, scanHeight/5);
        canvas.drawSubsection((counter-5)/5.0, 0, 5/5.0, scanHeight/5.0, counter-5, 0, 5, scanHeight);
    }
    if(counter%200==0){
        std::cout <<counter<<"\n";
    }
}

void ofApp::copyScanline(){
    
    ofPixels pixels = myPlayer.getPixels();
    int nChannels = pixels.getNumChannels();
    int red, green, blue;
    for(int j=0; j < slitWidth; j++){
        for(int i=0; i < scanHeight; i++){
            if(isVerticalScan){
                red     = pixels[int((myPlayer.getWidth() * i + (myPlayer.getWidth()/4)+j) * nChannels    ) ];
                green   = pixels[int((myPlayer.getWidth() * i + (myPlayer.getWidth()/4)+j) * nChannels + 1) ];
                blue    = pixels[int((myPlayer.getWidth() * i + (myPlayer.getWidth()/4)+j) * nChannels + 2 )];
            }else{
                red     = pixels[int((myPlayer.getWidth() * myPlayer.getHeight()/2 * 1 + (i+j)) * nChannels    ) ];
                green   = pixels[int((myPlayer.getWidth() * myPlayer.getHeight()/2 * 1 + (i+j)) * nChannels + 1) ];
                blue    = pixels[int((myPlayer.getWidth() * myPlayer.getHeight()/2 * 1 + (i+j)) * nChannels + 2 )];
            }
            scanline.getPixels()[(i*slitWidth+j)*3+0] = red;
            scanline.getPixels()[(i*slitWidth+j)*3+1] = green;
            scanline.getPixels()[(i*slitWidth+j)*3+2] = blue;
            scanline.update();
        }
    }
    ofPixels crop;
    scanline.getPixelsRef().cropTo(crop,0,0,slitWidth, scanHeight);
    crop.pasteInto(canvas.getPixelsRef(),counter*slitWidth,0);
    canvas.update();
    
}

string ofApp::getImageFileNameFromMovieFileName(string inputString){
    string outputString = "";
    
    vector<std::string> pathTokens;
    char sep = '/';
    for(size_t p=0, q=0; p!=movieFileName.npos; p=q)
        pathTokens.push_back( movieFileName.substr(p+(p!=0), (q=movieFileName.find(sep, p+1))-p-(p!=0)));
    for(int i=0; i<pathTokens.size()-1; i++)
        outputString += pathTokens[i]+"/";
    
    
    vector<std::string> fileTokens;
    string fName = pathTokens.back();
    sep = '.';
    for(size_t p=0, q=0; p!=fName.npos; p=q)
        fileTokens.push_back( fName.substr(p+(p!=0), (q=fName.find(sep, p+1))-p-(p!=0)));
    for(int i=0; i<fileTokens.size()-1; i++)
        outputString += fileTokens[i];
    
    outputString += ".png";
    return outputString;
}

void ofApp::initSlitScan(string s){
    
    movieFileName = s;
    std::cout << "movie name is " << movieFileName << endl;
    
    imageFileName = getImageFileNameFromMovieFileName(movieFileName);
    
    myPlayer.loadMovie(movieFileName);
    myPlayer.firstFrame();
    
    isVerticalScan = false;
    slitWidth = 1;
    
    scanLength = myPlayer.getTotalNumFrames();
    if(scanLength > 25000){
        scanLength = 25000;
    }
    
    
    if(myPlayer.getHeight() > myPlayer.getWidth()){
        isVerticalScan = true;
    }
    scanWidth = scanLength * slitWidth;
    if (isVerticalScan){
        scanHeight = myPlayer.getHeight();
    }else{
        scanHeight = myPlayer.getWidth();
    }
    canvas.allocate(scanWidth, scanHeight, OF_IMAGE_COLOR);
    scanline.allocate(slitWidth, scanHeight, OF_IMAGE_COLOR);
    
    counter = 0;
    
    std::cout << "\n---------------------------------\n";
    std::cout << "Movie width: " << myPlayer.getWidth() << "\n";
    std::cout << "Movie height: " <<  myPlayer.getHeight() << "\n";
    std::cout << "Movie length: " <<  myPlayer.getTotalNumFrames() << "\n";
    std::cout << "Orientation: ";
    if(isVerticalScan){
        std::cout << "vertical\n";
    }else{
        std::cout << "horizontal\n";
        
    }
    std::cout << "Scan width: " <<  scanWidth << "\n";
    std::cout << "Scan height: " <<  scanHeight << "\n";
    std::cout << "The image will be saved as " << imageFileName << std::endl;
    std::cout << "---------------------------------\n";
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
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

