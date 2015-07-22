#ifndef FINDPATH_H
#define FINDPATH_H
#include "stlastar.h"
class MapSearchNode
{
private:
public:
	unsigned int x;	 // the (x,y) positions of the node
	unsigned int y;	
	
	static const int MAP_WIDTH = 21;
	static const int MAP_HEIGHT = 21;
	MapSearchNode() { x = y = 0; initialise(); GetMap(x, y);}
	MapSearchNode( unsigned int px, unsigned int py ) { x=px; y=py; initialise(); GetMap(x, y);}

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );
	
	void PrintNodeInfo();

	int findPath(int StartNodeX, int StartNodeY, int EndNodeX, int EndNodeY, sf::Sprite AISprite);
	//int mapCreation(int x, int y);
	int GetMap(int x, int y);
	int* gameMap;
	//int gameMap;
	void initialise();
};
#endif