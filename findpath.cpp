////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "stlastar.h" // See header for copyright and usage information
#include "app.h"
#include <iostream>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "findpath.h"
#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

// Global data

// The world map


	
void MapSearchNode::initialise()
{
	int gameMap[MAP_WIDTH * MAP_HEIGHT] = 
	{
	// 000102030405060708091011121314151617181920
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,	//00
		9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,9,	//01
		9,1,9,9,9,1,9,9,9,1,9,1,9,9,9,1,9,9,9,1,9,	//02
		9,1,9,9,9,1,9,9,9,1,9,1,9,9,9,1,9,9,9,1,9,	//03
		9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,	//04
		9,1,9,9,9,1,9,1,9,9,9,9,9,1,9,1,9,9,9,1,9,	//05
		9,1,1,1,1,1,9,1,1,1,9,1,1,1,9,1,1,1,1,1,9,	//06
		9,9,9,9,9,1,9,9,9,1,9,1,9,9,9,1,9,9,9,9,9,	//07
		1,1,1,1,9,1,9,1,1,1,1,1,1,1,9,1,9,1,1,1,1,	//08
		9,9,9,9,9,1,9,1,9,9,1,9,9,1,9,1,9,9,9,9,9,	//09
		1,1,1,1,1,1,1,1,9,9,9,9,9,1,1,1,1,1,1,1,1,	//10
		9,9,9,9,9,1,9,1,1,1,1,1,1,1,9,1,9,9,9,9,9,	//11
		1,1,1,1,9,1,9,1,9,9,9,9,9,1,9,1,9,1,1,1,1,	//12
		9,9,9,9,9,1,9,1,1,1,9,1,1,1,9,1,9,9,9,9,9,	//13
		9,1,1,1,1,1,1,1,9,1,9,1,9,1,1,1,1,1,1,1,9,	//14
		9,1,9,9,1,9,9,9,9,1,1,1,9,9,9,9,1,9,9,1,9,	//15
		9,1,9,9,1,1,1,1,1,1,9,1,1,1,1,1,1,9,9,1,9,	//16
		9,1,9,9,1,9,9,9,9,1,9,1,9,9,9,9,1,9,9,1,9,	//17
		9,1,9,9,1,9,9,9,9,1,9,1,9,9,9,9,1,9,9,1,9,	//18
		9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,	//19
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9	//20

	};
	
	this->gameMap = gameMap;
	
}
int MapSearchNode::GetMap(int x, int y)
{

		if( x < 0 ||
			x >= MAP_WIDTH ||
			 y < 0 ||
			 y >= MAP_HEIGHT
		  )
		{
			return 9;	 
		}
		//cout<<"Maptest"<<endl;
		return this->gameMap[(y*MAP_WIDTH)+x];
}


// Definitions



bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	cout << "Node position : (" << x << ", " << y << ")" << endl;

}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	float xd = fabs(float(((float)x - (float)nodeGoal.x)));
	float yd = fabs(float(((float)y - (float)nodeGoal.y)));

	return xd + yd;
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (this->GetMap( x-1, y ) < 9) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (this->GetMap( x, y-1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (this->GetMap( x+1, y ) < 9)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (this->GetMap( x, y+1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );

}

// Main

int MapSearchNode::findPath(int StartNodeX, int StartNodeY, int EndNodeX, int EndNodeY, sf::Sprite AISprite)
{
	
	//cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...
	
	AStarSearch<MapSearchNode> astarsearch;
	
	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{
		
		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = StartNodeX;
		nodeStart.y = StartNodeY; 
	

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = EndNodeX;						
		nodeEnd.y = EndNodeY; 
		
		//cout<<EndNodeX<<" "<<EndNodeY<<endl;
		// Set Start and goal states
		
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();
				
			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				p->PrintNodeInfo();
	#endif			
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			//cout << "Search found goal state\n";
				
				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif
				int steps = 0;

				node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}
					if (steps = 0)
					{
						AISprite.Move(x-StartNodeX, y-StartNodeY);
						
					}
					node->PrintNodeInfo();
					
					
					steps ++;

				
				};

				//cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();

	
		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			//cout << "Search terminated. Did not find goal state\n";
		
		}

		// Display the number of loops the search went through
		//cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}
	return 0;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////