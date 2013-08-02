//
//  ParticleConnectionGenerator.cpp
//  emptyExample
//
//  Created by James George on 5/29/13.
//
//

#include "ParticleConnectionGenerator.h"
#include "ParticleConnectorBin.h"

ParticleConnectionGenerator::ParticleConnectionGenerator(){
	lastMinDistance = 0;
	minDistance = 50;
	currentBinSize = minDistance*2;
	numParticles = 100;
	searchStartIdx = 0;
	searchStepSize = 1;
	drawConnections = true;
	lastBoundarySize = 0;
	boundarySize = 500;
	bBinMeshDirty = false;
	maxTotalConnections = 400000;
	
}

void ParticleConnectionGenerator::setup(){
	
	for(int i = 0; i < numParticles; i++){
		pointMesh.addVertex( ofVec3f(0, 0, 0) );
		connectors.push_back(new ParticleConnector( pointMesh.getVertices()[i] ));
	}
	
	for(int i = 0; i < maxTotalConnections; i++){
		connectionMesh.addColor(ofFloatColor(0));
		connectionMesh.addVertex(ofVec3f(0,0,0));
		connectionMesh.addColor(ofFloatColor(0));
		connectionMesh.addVertex(ofVec3f(0,0,0));
		freeConnectionIndeces.insert(i);
	}
	connectionMesh.setMode(OF_PRIMITIVE_LINES);
}

void ParticleConnectionGenerator::update(){
	
	if(lastMinDistance != minDistance ||
	   lastBoundarySize != boundarySize)
	{
		setBounds(boundarySize, minDistance);
		
		lastMinDistance = minDistance;
		lastBoundarySize = boundarySize;

		ofVec3f boundaryPoint = ofVec3f(boundarySize,boundarySize,boundarySize);
		for(int i = 0; i < connectors.size(); i++){
			connectors[i]->upperBounds =  boundaryPoint;
			connectors[i]->lowerBounds = -boundaryPoint;
		}
		for(int i = 0; i < connections.size(); i++){
			connections[i].minDistance = minDistance;
		}
		
	}

	for(int i = 0; i < connectors.size(); i++){
		connectors[i]->update();
		
		connectors[i]->binIndex1 = positionToBinIndex(connectors[i]->position, NULL);
		connectors[i]->binIndex2 = positionToBinIndex(connectors[i]->position, NULL);
	}
	
	if(!drawConnections) return;
	
	
	searchStartIdx = (searchStartIdx + 1) % searchStepSize;
	float squaredDistance = pow(minDistance,2);

	for(int i = 0; i < connectors.size(); i++){
		int numConnects = 0;
		for(int j = searchStartIdx; j < connectors.size(); j+= searchStepSize){
			if(i != j &&
			  (connectors[i]->binIndex1 == connectors[j]->binIndex1 || connectors[i]->binIndex2 == connectors[j]->binIndex2) &&
			   connectors[i]->connections.find(connectors[j]) == connectors[i]->connections.end() &&
			   connectors[j]->connections.find(connectors[i]) == connectors[j]->connections.end() &&
			   connectors[i]->position.distanceSquared(connectors[j]->position) < squaredDistance &&
			   !freeConnectionIndeces.empty())
			{
				ParticleConnection connection;
				connection.a = connectors[i];
				connection.b = connectors[j];
				connection.connectionMeshRef = &connectionMesh;
				connection.connectionVboIndex = *freeConnectionIndeces.begin();
				freeConnectionIndeces.erase(freeConnectionIndeces.begin());
//				connection.steps = 10;
				connection.minDistance = minDistance;
				connection.createConnections();
				connection.a->connections.insert(connection.b);
				connection.b->connections.insert(connection.a);
				
//				cout << "connection made " << freeConnectionIndeces.size() << endl;
				connections.push_back(connection);
//				if(numConnects++ >= maxConnections) break;
			}
		}
	}
	
	for(int i = connections.size()-1; i >= 0; i--){
		
		connections[i].updateConnections();
		
		if(connections[i].currentColor < 0){
			
			set<ParticleConnector*>& setA = connections[i].a->connections;
			set<ParticleConnector*>& setB = connections[i].b->connections;
			
			setA.erase( setA.find( connections[i].b) );
			setB.erase( setB.find( connections[i].a) );
			
			//reclaim connection
			freeConnectionIndeces.insert( connections[i].connectionVboIndex );
			connections.erase(connections.begin() + i);
			//cout << "connection erased" << endl;
		}
	}
}

void ParticleConnectionGenerator::setBounds(float bounds, float minDist){
	currentBinSize = minDist * 2;
	currentSubdivisions = ceil(bounds*2 / currentBinSize);
	
	//minDistance = bounds / currentBinSize / 2.0;
	
	bBinMeshDirty = true;
	//boundarySize = currentSubdivisions * currentBinSize / 2.;

	
//	ofVec3f lowerBounds = ofVec3f(-bounds,-bounds,-bounds);
//	cout << "upper bound was " << bounds << " width min distance " << minDistance << " and an adjusted size of " << adjustedArea;
//	bounds = adjustedArea ;
//	cout << "adjusted upper bounds is " << bounds << endl;

	/*
	for(int i = 0; i < connectors.size(); i++){
		connectors[i]->lowerBounds = lowerBounds;
		connectors[i]->upperBounds = upperBounds;
	}

	for(int i = 0; i < binsLayer1.size(); i++) delete binsLayer1[i];
	for(int i = 0; i < binsLayer2.size(); i++) delete binsLayer2[i];
	binsLayer1.clear();
	binsLayer2.clear();
	
	binSpaceDivision1.clear();
	binSpaceDivision2.clear();

	ofVec3f binSize = (upperBounds - lowerBounds) / subdivisions;
	
	//create initial bins
	for(int z = 0; z < subdivisions; z++){
		for(int y = 0; y < subdivisions; y++){
			for(int x = 0; x < subdivisions; x++){
				ofVec3f binMin = lowerBounds + binSize * ofVec3f(x,y,z);
				ofVec3f binMax = lowerBounds + binSize * ofVec3f(x+1,y+1,z+1);
				ParticleConnectorBin* b = new ParticleConnectorBin();
				b->minBound = binMin;
				b->maxBound = binMax;
				b->size = binSize;
				binsLayer1.push_back(b);
				
				binSpaceDivision1[ positionToBinIndex(b->minBound, binsLayer1[0]) ] = binsLayer1.size()-1;
			}
		}
	}
	
	//offset bins
	for(int z = 0; z <= subdivisions; z++){
		for(int y = 0; y <= subdivisions; y++){
			for(int x = 0; x <= subdivisions; x++){
				ofVec3f binMin = lowerBounds + binSize * ofVec3f(x,y,z) - binSize/2;
				ofVec3f binMax = lowerBounds + binSize * ofVec3f(x+1,y+1,z+1) - binSize/2;
				ParticleConnectorBin* b = new ParticleConnectorBin();
				b->minBound = binMin;
				b->maxBound = binMax;
				b->size = binSize;
				binsLayer2.push_back(b);
				
				binSpaceDivision2[ positionToBinIndex(b->minBound, binsLayer2[0]) ] = binsLayer2.size()-1;
				
			}
		}
	}
	 */
}

int ParticleConnectionGenerator::positionToBinIndex(ofVec3f pos, ParticleConnectorBin* refBin){
//	ofVec3f quantized = (pos + refBin->minBound) / refBin->size;
	ofVec3f quantized = (pos - ofVec3f(boundarySize, boundarySize, boundarySize)) / currentBinSize;
	return floor(quantized.x) +
		   floor(quantized.y) * currentSubdivisions +
		   floor(quantized.z) * currentSubdivisions * currentSubdivisions;
}

void ParticleConnectionGenerator::drawBins(){

	if(bBinMeshDirty){
		binMesh.clear();
		binMesh.setMode(OF_PRIMITIVE_LINES);
		
		//layer one
		ofVec3f lowerBounds(-boundarySize,-boundarySize,-boundarySize);
		
		for(int z = 0; z < currentSubdivisions; z++){
			for(int y = 0; y < currentSubdivisions; y++){
				for(int x = 0; x < currentSubdivisions; x++){
					ofVec3f binMin = lowerBounds + currentBinSize * ofVec3f(x,y,z);
					
					binMesh.addVertex( binMin );
					binMesh.addVertex( binMin + ofVec3f(currentBinSize,0,0) );
					
					binMesh.addVertex( binMin );
					binMesh.addVertex( binMin + ofVec3f(0,currentBinSize,0) );
					
					binMesh.addVertex( binMin );
					binMesh.addVertex( binMin + ofVec3f(0,0,currentBinSize) );

				}
			}
		}
		
		for(int z = 0; z <= currentSubdivisions; z++){
			for(int y = 0; y <= currentSubdivisions; y++){
				for(int x = 0; x <= currentSubdivisions; x++){
					ofVec3f binMin = lowerBounds + currentBinSize * ofVec3f(x,y,z) - currentBinSize/2;
					
					binMesh.addVertex( binMin );
					binMesh.addVertex( binMin + ofVec3f(currentBinSize,0,0) );

					binMesh.addVertex( binMin );
					binMesh.addVertex( binMin + ofVec3f(0,currentBinSize,0) );
					
					binMesh.addVertex( binMin );
					binMesh.addVertex( binMin + ofVec3f(0,0,currentBinSize) );
					
				}
			}
		}
		bBinMeshDirty = false;
	}

	ofPushStyle();
	
	binMesh.draw();
	/*	
	for(int i = 0; i < binsLayer1.size(); i++){
		ofVec3f position = binsLayer1[i]->minBound + (binsLayer1[i]->maxBound - binsLayer1[i]->minBound) / 2.0;
		ofBox(position,
			  binsLayer1[i]->size.x,
			  binsLayer1[i]->size.y,
			  binsLayer1[i]->size.z);
	}
	
	for(int i = 0; i < binsLayer2.size(); i++){
		ofVec3f position = binsLayer2[i]->minBound + (binsLayer2[i]->maxBound - binsLayer2[i]->minBound) / 2.0;
		ofBox(position,
			  binsLayer2[i]->size.x,
			  binsLayer2[i]->size.y,
			  binsLayer2[i]->size.z);
	}
	 
	*/
	ofPopStyle();
}

void ParticleConnectionGenerator::draw(){
	
	ofPushStyle();
	ofNoFill();
	
	for(int i = 0; i < connectors.size(); i++){
		pointMesh.setVertex(i, connectors[i]->position);
		
	}
	pointMesh.drawVertices();

	connectionMesh.draw();
	
//	for(int i = 0; i < connections.size(); i++){
//		connections[i].connectionLines.draw();
//	}
	
	ofPopStyle();
}

