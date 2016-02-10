#ifndef GAME_H
#define GAME_H

#include "DiceInvaders.h"
#include "Player.h"
#include "Aliens.h"
#include "Rockets.h"
#include "Bombs.h"
#include "Constant.h"


using namespace std;

/**
*  @brief Class that handles all of the other classes existed in the game.
*  @details Game class manages the other classes namely Player, Aliens, Bombs and Rockets by 
*  making an object of each classes and feeds the required methods and fields to the DiceInvaders class.
*/
class Game 
{
public:
	// Default constructor   
	Game(IDiceInvaders* system);
	// Destructor  
	~Game();
	// Draw the given Sprite 
	void drawSprites();
	// Update the current screen 
	bool updateScreen(float move, IDiceInvaders::KeyStatus keys);
	// Update game status 
	void updateGameStatus(IDiceInvaders* system);
	// Check the fire key for player
	void fireKey(IDiceInvaders::KeyStatus keys, float newTime);
	// Check for remained life in the game 
	int LifeRemained();
	// Detect all of the related collision for  aliens and player
	void detectCollisions();
	// Check for collision for rockets and aliens for updating the scores
	bool checkRocketCollision();



private:
	IDiceInvaders* System;  ///< Pointer to a IDiceInvaders in a system
	Player* player;		///< Pointer to the class of Player 
	Aliens* aliens;		///< Pointer to the class of Aliens
	Rockets* rockets;	///< Pointer to the class of Rockets
	Bombs* bombs;		///< Pointer to the class of Bombs
};

#endif