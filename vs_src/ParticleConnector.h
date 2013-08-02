
#pragma once

#include "ofMain.h"
#include <set>

//class ParticleConnection;

class ParticleConnector {
  public:
	ParticleConnector(ofVec3f pos);
	~ParticleConnector();

	void update();
	ofVec3f position;
	ofVec3f direction;
	set<ParticleConnector*> connections;
	
	int binIndex1;
	int binIndex2;
	
	ofVec3f lowerBounds;
	ofVec3f upperBounds;
  protected:
	
};