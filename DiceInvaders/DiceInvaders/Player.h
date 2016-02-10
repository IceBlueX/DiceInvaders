#ifndef PLAYER_H
#define PLAYER_H

#include "DiceInvaders.h"
#include "Rockets.h"
#include "Bombs.h"

/**
*  @brief Class that handles the Player functionality of the game.
*  @details Player class which defines the movement and capabilities of the player in the game. 
*/
class Player {
public:
	// Default constructor   
	Player(IDiceInvaders* system);
	// Destructor  
	~Player();
	// Update the position of all of the player
	void updatePosition(float move);
	// Draw the given Sprite (the player)
	void drawSprite();
	// Coordinate the fired rockets with the position of the player
	void fire(Rockets* rockets, float time);
	// Get the life remained from the player  
	uint8_t const getlife()  { return life; }
	// Set the life remained from the player  
	void setlife(const uint8_t& _life) { life = _life; }
	// Get the score achieved by the player  
	uint16_t const getscore()  { return score; }
	// Set the score achieved by the player  
	void setscore(const uint16_t& _score) { score = _score; }
	float horizontalPosition; ///< Horizontal positon stored as a float number

private:	
	int life; ///< Stores the life remained by the player
	int score;	///< The player's score
	ISprite* sprite;	///< Pointer to rocket's Sprite 
	float timeOfLastRocket;		///< Stores the exact time of the last rocket	
	float getHorizontalPosition();	// Get the initial Horizontal position of the player
}; 

#endif