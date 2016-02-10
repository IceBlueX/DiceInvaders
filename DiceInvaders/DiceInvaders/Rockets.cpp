/**
*  @file    Rockets.cpp
*  @author  Mehrdad Mehraban
*  @date    1/29/2015
*  @version 1.0
*
*  @brief Rockets class which shows the behavior of the rockets being fired by the Player.
*/

#include "Rockets.h"


/**
*   @brief	Default constructor
*
*   @param  system : a pointer to refers to Bombs class
*
*   @return nothing
*/
Rockets::Rockets(IDiceInvaders* system){
	this->sprite = system->createSprite("data/rocket.bmp");

}

/**
*   @brief  Destructor (terminate sprites of the enemies)
*
*   @return nothing
*/
Rockets::~Rockets(){
	this->sprite->destroy();
}

/**
*   @brief   Draw the given Sprite (the rockets)
*
*   @return nothing
*/
void Rockets::draw(){
	uint8_t SizeOfHorizontalPos = verticalPositions.size();
	for (int i = 0; i < SizeOfHorizontalPos; i++) {
		this->sprite->draw((int)this->horizontalPositions[i], (int)this->verticalPositions[i]);
	}
}

/**
*   @brief  Update the position of all of the bombs
*
*   @param  move : The calculated current move
*   @return nothing
*/
void Rockets::updatePosition(float move){
	uint8_t SizeOfHorizontalPos = verticalPositions.size();
	for (int i = 0; i < SizeOfHorizontalPos; i++) {
		if (this->verticalPositions[i] > GameConst::GamexHeight)
			this->destroy(i);
		}
	for (int i = 0; i < SizeOfHorizontalPos; i++)
		this->verticalPositions[i] += -move;
}

/**
*   @brief Create and add anew element to Bombs vector's axis position
*
*   @param  horizontalPosition : The horizontal position of a new bomb to add as a vector
*   @param  verticalPosition : The vertical position of a new bomb to add as a vector
*   @return nothing
*/
void Rockets::create(float horizontalPosition, float verticalPosition){
	this->horizontalPositions.push_back(horizontalPosition);
	this->verticalPositions.push_back(verticalPosition);
}

/**
*   @brief  The check for collision in Bombs class
*
*   @param  horizontalPosition : The horizontal position of a new bomb to add as a vector
*   @param  verticalPosition : The vertical position of a new bomb to add as a vector
*   @return true if there is a collision or false if otherwise
*/
bool Rockets::isCollision(float horizontalPosition, float verticalPosition){
	uint8_t SizeOfHorizontalPos = verticalPositions.size();
	for (int i = 0; i < SizeOfHorizontalPos; i++) {
		bool horizontalOverlap = abs(horizontalPosition - this->horizontalPositions[i]) < GameConst::SpritexEdge;
		bool verticalOverlap = abs(verticalPosition - this->verticalPositions[i]) < GameConst::SpritexEdge;
		if (horizontalOverlap && verticalOverlap) {
			this->destroy(i);
			return true;
		}
	}
	return false;
}

/**
*   @brief  Terminate the apointed aliens according to its index
*
*   @param  index : The index of the specified by vector
*
*   @return nothing
*/
void Rockets::destroy(int index){
	this->horizontalPositions.erase(this->horizontalPositions.begin() + index);
	this->verticalPositions.erase(this->verticalPositions.begin() + index);
}