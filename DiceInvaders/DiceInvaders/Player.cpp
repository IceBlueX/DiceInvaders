/**
*  @file    Player.cpp
*  @author  Mehrdad Mehraban
*  @date    1/29/2015
*  @version 1.0
*
*  @brief Player class which defines the movement and capabilities of the player in the game. 
*/


#include "Player.h"

/**
*   @brief	Default constructor
*
*   @param  system : a pointer to refers to Bombs class
*
*   @return nothing
*/
Player::Player(IDiceInvaders* system){
	this->sprite = system->createSprite("data/player.bmp");
	this->life = 3;
	this->score = 0;
	getHorizontalPosition();
}

/**
*   @brief  Destructor (terminate sprites of the enemies)
*
*   @return nothing
*/
Player::~Player(){
	this->sprite->destroy();
}

/**
*   @brief  Get the initial Horizontal position of the player
*
*   @return returns the initial Horizontal position of the player
*/
float Player::getHorizontalPosition(){
	return this->horizontalPosition = 0.5f * GameConst::GamexWidth;
}

/**
*   @brief  Update the position of all of the bombs
*
*   @param  move : The calculated current move
*   @return nothing
*/
void Player::updatePosition(float move){
	if (this->horizontalPosition + move > (GameConst::GamexWidth - GameConst::SpritexEdge))
		this->horizontalPosition = GameConst::GamexWidth - GameConst::SpritexEdge;
	else if (this->horizontalPosition + move < 0)
		this->horizontalPosition = 0;
	else
		this->horizontalPosition = this->horizontalPosition + move;

}


/**
*   @brief   Draw the given Sprite (the player)
*
*   @return nothing
*/
void Player::drawSprite(){
	sprite->draw((int)this->horizontalPosition, (int)(GameConst::GamexHeight - GameConst::SpritexEdge));
}

/**
*   @brief  Coordinate the fired rockets with the position of the player
*
*   @param  rockets : a pointer to refers to Bombs class
*   @param  time : the new time (updated runtime) at the moment
*   @return nothing
*/
void Player::fire(Rockets* rockets, float time){
	if (!this->timeOfLastRocket)
		this->timeOfLastRocket = -1.0f; 
	if ((time - this->timeOfLastRocket) > 0.8f) {
		rockets->create(this->horizontalPosition, GameConst::GamexHeight - GameConst::SpritexEdge);
		this->timeOfLastRocket = time;
	}
}

