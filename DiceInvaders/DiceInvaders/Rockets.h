#ifndef ROCKETS_H
#define ROCKETS_H

#include "DiceInvaders.h"
#include "Constant.h"
#include <vector>

using namespace std;

/**
*  @brief Class that handles the Rockets functionality of the game.
*  @details Rockets class which shows the behavior of the rockets being fired by the Player.
*/
class Rockets {
public:
	// Default constructor  
	Rockets(IDiceInvaders* system);
	// Destructor  
	~Rockets();
	// Draw the given Sprite 
	void draw();
	// Update the position of rockets  
	void updatePosition(float move);
	// Create a rocket based on the axis position from player
	void create(float horizontalPosition, float verticalPosition);
	// The check for collision in Rockets class
	bool isCollision(float horizontalPosition, float verticalPosition);
private:
	ISprite* sprite;	 ///< Pointer to rocket's Sprite 
	vector<float> verticalPositions;	///< Vertical vector to store float
	vector<float> horizontalPositions;	///< Horizental vector to store float
	int getNumberOfRockets();	///< Get the number of Bombs
	void destroy(int index);	///< Terminate the apointed Bombs
};

#endif