#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	vidPlayer.load("fingers.mov");
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);
	
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);

	bLearnBakground = true;
	threshold = 80;
	ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
	//ofBackground(100,100,100);

    bool bNewFrame = false;


	vidPlayer.update();
	bNewFrame = vidPlayer.isFrameNew();
    cout << bNewFrame << endl;

	if (bNewFrame){


		colorImg.setFromPixels(vidPlayer.getPixels());

        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// draw the incoming video image
	ofSetHexColor(0xffffff);
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2 - colorImg.getWidth()/2,ofGetHeight()/2 - colorImg.getHeight()/2);
	if(bShowVideo){
		colorImg.draw(0,0);
	}
    for (int i = 0; i < contourFinder.nBlobs; i++){
		ofSetColor(ofColor::fuchsia);
		ofFill();
		ofDrawEllipse(contourFinder.blobs[i].boundingRect.getCenter(), 20,20);
    }
	ofPopMatrix();
	
	ofDrawBitmapString("Press 'v' to toggle video and path drawing", ofGetWidth()/2.0, ofGetHeight()-100.0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case 'v':
			ofBackground(ofColor::white);
			bShowVideo = !bShowVideo;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
