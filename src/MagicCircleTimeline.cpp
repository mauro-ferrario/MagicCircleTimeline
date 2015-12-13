//
//  MagicCircleTimeline.cpp
//  MagicCircleTimeline
//
//  Created by Mauro Ferrario on 12/12/15.
//
//

#include "MagicCircleTimeline.h"


MagicCircleTimeline::MagicCircleTimeline()
{
  
}

void MagicCircleTimeline::setup()
{
  timeline.setup(); //registers events
  timeline.setDurationInSeconds(120); //sets time
  timeline.setLoopType(OF_LOOP_NONE); //turns the timeline to loop
  
  timeline.addBangs("End");
  for(int a = 0; a < 24; a++)
  {
    timeline.addCurves("light_"+ofToString(a), ofRange(0, 255));
  }
  timeline.setName("timeline_0");
  timeline.loadTracksFromFolder("timeline_0/");
  timeline.setHeight(ofGetWindowHeight());
  timeline.setDurationInSeconds(20);
  ofAddListener(timeline.events().bangFired, this, &MagicCircleTimeline::receiveBandEnd);
  setupGUI();
  setupOSC();
}

void MagicCircleTimeline::setupOSC()
{
  sender.setup("localhost", 12345);
}

void MagicCircleTimeline::receiveBandEnd(ofxTLBangEventArgs& bang){
  ofLogNotice("Bang fired from track " + bang.track->getName());
}

void MagicCircleTimeline::setupGUI()
{
  gui.setup();
  parameters.setName("Parameters");
  parameters.add(guiSetup.set("Gui setup", 0, 0, 100));
  gui.add(parameters);
  guiSetup.addListener(this, &MagicCircleTimeline::guiSetupChanged);
}

void MagicCircleTimeline::guiSetupChanged(int & newGuiSetupId){
  string name = "timeline_"+ofToString(newGuiSetupId);
  timeline.loadTracksFromFolder(name+"/");
  timeline.setName(name);
}

void MagicCircleTimeline::update()
{
  ofxOscMessage m;
  m.setAddress("ControlLight");
  for(int a = 0; a < 24; a++)
    m.addIntArg(timeline.getValue("light_"+ofToString(a)));
  sender.sendMessage(m);
}

void MagicCircleTimeline::draw()
{
  timeline.draw();
  gui.draw();
}

void MagicCircleTimeline::save()
{
  timeline.saveTracksToFolder(timeline.getName());
}