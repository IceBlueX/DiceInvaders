/**
*  @file    Bombs.cpp
*  @author  Mehrdad Mehraban
*  @date    1/29/2015
*  @version 1.0
*
*  @brief Bombs class which shows the behavior of the bombs being drops by aliens.
*/
#include "Bombs.h"


/**
*   @brief	Default constructor
*
*   @param  system : a pointer to refers to Bombs class
*
*   @return nothing
*/
Bombs::Bombs(IDiceInvaders* system){
	this->sprite = system->createSprite("data/bomb.bmp");

}

/**
*   @brief  Destructor (terminate sprites of the enemies)
*
*   @return nothing
*/
Bombs::~Bombs(){
	this->sprite->destroy();
}

/**
*   @brief   Draw the given Sprite (bombs)
*
*   @return nothing
*/
void Bombs::draw(){
	uint8_t SizeOfHorizontalPos = verticalPositions.size();
	for (int i = 0; i < SizeOfHorizontalPos; i++) {
		this->sprite->draw((int)this->horizontalPositions[i], (int)this->verticalPositions[i]);
	}
}

/**
*   @brief  Terminate the apointed aliens according to its index
*
*   @param  index : The index of the specified by vector
*
*   @return nothing
*/
void Bombs::destroy(int index){
	this->horizontalPositions.erase(this->horizontalPositions.begin() + index);
	this->verticalPositions.erase(this->verticalPositions.begin() + index);
}


/**
*   @brief  Update the position of all of the bombs
*
*   @param  move : The calculated current move
*   @return nothing
*/
void Bombs::updatePosition(float move){
	uint8_t SizeOfHorizontalPos = verticalPositions.size();
	for (int i = 0; i < SizeOfHorizontalPos; i++) {
		if (this->verticalPositions[i] < 0.0f)
			this->destroy(i);
	}

	for (int i = 0; i < SizeOfHorizontalPos; i++)
		this->verticalPositions[i] += move;
}


/**
*   @brief Create and add anew element to Bombs vector's axis position
*
*   @param  horizontalPosition : The horizontal position of a new bomb to add as a vector
*   @param  verticalPosition : The vertical position of a new bomb to add as a vector
*   @return nothing
*/
void Bombs::create(float horizontalPosition, float verticalPosition){
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
bool Bombs::isCollision(float horizontalPosition, float verticalPosition){
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