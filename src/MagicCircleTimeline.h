//
//  MagicCircleTimeline.h
//  MagicCircleTimeline
//
//  Created by Mauro Ferrario on 12/12/15.
//
//

#ifndef __MagicCircleTimeline__MagicCircleTimeline__
#define __MagicCircleTimeline__MagicCircleTimeline__

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class MagicCircleTimeline
{
public:
            MagicCircleTimeline();
  void      setup();
  void      update();
  void      draw();
  void      save();
private:
  ofxTimeline timeline;
  ofxPanel            gui;
  ofParameterGroup    parameters;
  ofParameter<int>    guiSetup;
  void                guiSetupChanged(int & newGuiSetupId);
  void                receiveBandEnd(ofxTLBangEventArgs& bang);
  void                setupGUI();
  void                setupOSC();
  ofxOscSender        sender;
};

#endif /* defined(__MagicCircleTimeline__MagicCircleTimeline__) */
