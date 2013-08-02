
#pragma once

#include "ofMain.h"
#include "ParticleConnection.h"
#include "ParticleConnector.h"

class ParticleConnectorBin;
class ParticleConnectionGenerator {
  public:
	ParticleConnectionGenerator();

	bool drawConnections;
	int	numParticles;
	int maxTotalConnections;
	float maxConnections;
	
	float minDistance;
	float boundarySize;
	
	void setup();
	void update();
	void draw();

	void drawBins();
	
	
  protected:
	ofMesh pointMesh;
	float lastMinDistance;
	float lastBoundarySize;
	float currentBinSize;
	
	ofVboMesh binMesh;
	

	ofVboMesh connectionMesh;
	set<int> freeConnectionIndeces;
	
	void setBounds(float bounds, float minDistance);

	int currentSubdivisions;
	vector<ParticleConnector*> connectors;
	vector<ParticleConnectorBin*> binsLayer1;
	vector<ParticleConnectorBin*> binsLayer2;
	vector<ParticleConnection> connections;
	
	bool bBinMeshDirty;
	int positionToBinIndex(ofVec3f pos, ParticleConnectorBin* refBin);
	
	map<int,int> binSpaceDivision1;
	map<int,int> binSpaceDivision2;
	
	int searchStartIdx;
	int searchStepSize;
};