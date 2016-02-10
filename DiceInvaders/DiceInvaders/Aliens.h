#ifndef ALIENS_H
#define ALIENS_H

#include "DiceInvaders.h"
#include "Bombs.h"
#include <vector>
#include <string>
#include "Constant.h"


using namespace std;

/**
*  @brief Class that handles the Aliens(enemies) functionality of the game.
*  @details Aliens class which generates and defines the capabilities of the enemies playing againt the Player.
*/
class Aliens {

public:
	// Default constructor   
	Aliens(IDiceInvaders* system);
	// Destructor  
	~Aliens();
	// Get the Horizontal position of the requested alien appointed by index
	float getHorizentalPosOfAlien(int index);
	// Get the Vertical position of the requested alien appointed by index
	float getVerticalPosOfAlien(int index);
	// Terminate the apointed aliens
	void destroy(int index);
	// Draw the given Sprite 
	void draw();
	// Update the position of all of the aliens  
	bool updatePosition(float move);
	// coordinate the fired bombs with the position of the aliens
	void fire(Bombs* bombs, float time);
//protected:
	// Vector to store integers
	vector<float> horizontalPositions;
	// Vector to store integers
	vector<float> verticalPositions;
	// 
	float timeBetweenBombs;
	// Generate random types of aliens (enemy1, enemy2)
	void generateAliens();



private:
	ISprite* redSprite;		///< Pointer to red aliens 
	ISprite* greenSprite;	///< Pointer to green aliens
	vector<string> alienType;		///< Vector to store integers
	string direction;	///< Stores the direction of which the aliens are moving towards  
	float timeOfLastBomb;	///< Stores the last time of fire
	bool downwardMovement();	// Downward movement of the position
	bool aliensReachedBottom; ///< Boolean flag if an alien reaches the bottom of the screen, the player loses and the game is over.
	float adjustDirection(float move); // adjust the direction

};

#endif