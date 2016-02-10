#ifndef BOMBS_H
#define BOMBS_H

#include "DiceInvaders.h"
#include <vector>
#include "Constant.h"

using namespace std;

/**
*  @brief Class that handles the Bombs functionality of the game.
*  @details Bombs class which shows the behavior of the bombs being drops by aliens.
*/
class Bombs {
public:
	// Default constructor  
	Bombs(IDiceInvaders* system);
	// Destructor  
	~Bombs();
	// Draw the given Sprite 
	void draw();
	// Update the position of bombs  
	void updatePosition(float move);
	// Create a bomb based on the axis position from aliens
	void create(float horizontalPosition, float verticalPosition);
	// The check for collision in Bombs class
	bool isCollision(float horizontalPosition, float verticalPosition);
private:
	ISprite* sprite;	 ///< Pointer to bomb's Sprite 
	vector<float> verticalPositions;	///< Vertical Vector to store float
	vector<float> horizontalPositions;	///< HorizontalVector to store float
	int getNumberOfBombs();		///< Get the number of Bombs
	void destroy(int index);	///< Terminate the apointed Bombs
};

#endif