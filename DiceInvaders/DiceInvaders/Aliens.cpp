/**
*  @file    Aliens.cpp
*  @author  Mehrdad Mehraban
*  @date    1/30/2015
*  @version 1.0
*
*  @brief Aliens class which generates and defines the capabilities of the enemies playing againt the Player.
*/



#include "Aliens.h"
#include "ctime"
#include <random>
#include <fstream>
#include <algorithm>    // std::transform
#include <functional>	//std::bind2nd
using namespace std;

/**
*   @brief	Default constructor   
*
*   @param  system : a pointer to refers to Bombs class
*
*   @return nothing
*/
Aliens::Aliens(IDiceInvaders* system){
	srand((unsigned int)rand());
	this->redSprite = system->createSprite("data/enemy1.bmp");
	this->greenSprite = system->createSprite("data/enemy2.bmp");
	this->timeBetweenBombs = 1.0f;
	this->aliensReachedBottom = false;
	this->generateAliens();
}
/**
*   @brief  Destructor (terminate sprites of the enemies)
*
*   @return nothing
*/

Aliens::~Aliens(){
	this->redSprite->destroy();
	this->greenSprite->destroy();
}

/**
*   @brief  Get the Vertical position of the requested alien appointed by index
*
*   @return returns the Horizontal position of the alien
*/

float Aliens::getHorizentalPosOfAlien(int index){
	return horizontalPositions[index];
}

/**
*   @brief  Get the Vertical position of the requested alien appointed by index
*
*   @return returns the vertical position of the alien
*/

float Aliens::getVerticalPosOfAlien(int index){
	return verticalPositions[index];
}

/**
*   @brief  Generate random types of aliens (enemy1, enemy2)
*
*   @return nothing
*/

void Aliens::generateAliens(){
	this->direction = "Right";
	this->timeOfLastBomb = 0.0f;

	this->alienType.resize(GameConst::AliensInTotal);
	this->horizontalPositions.resize(GameConst::AliensInTotal);
	this->verticalPositions.resize(GameConst::AliensInTotal);

	for (int i = 0; i < GameConst::AliensInTotal; i++) {
		if (rand() % 2 == 0)
			this->alienType[i] = "red";
		else
			this->alienType[i] = "green";
		this->horizontalPositions[i] = ((float)(i % GameConst::aliensInARow) * GameConst::SpritexEdge);
		this->verticalPositions[i] = ((float)(i / GameConst::aliensInARow) * GameConst::SpritexEdge);
	}
}


/**
*   @brief  Terminate the apointed aliens according to its index 
*
*   @param  index : The index of the specified by vector
*   
*   @return nothing
*/


void Aliens::destroy(int index){
	this->alienType.erase(this->alienType.begin() + index);
	this->horizontalPositions.erase(this->horizontalPositions.begin() + index);
	this->verticalPositions.erase(this->verticalPositions.begin() + index);
}


/**
*   @brief   Draw the given Sprite red or green
*
*   @return nothing
*/

void Aliens::draw(){
	uint8_t SizeOfHorizontalPos = horizontalPositions.size();
	for (int i = 0; i < SizeOfHorizontalPos; i++) {
		if (this->alienType[i] == "red")
			redSprite->draw((int)(this->horizontalPositions[i]), (int)(this->verticalPositions[i]));
		else
			greenSprite->draw((int)(this->horizontalPositions[i]), (int)(this->verticalPositions[i]));
	}
}

/**
*   @brief  Update the position of all of the aliens 
*
*   @param  move : The calculated current move 
*   @return return true if an alien is at the bottom of the screen or false if otherwise
*/

bool Aliens::updatePosition(float move){
	uint8_t SizeOfHorizontalPos = horizontalPositions.size();
	move = adjustDirection(move);
	bool outsideScreen = false;
#if DEBUG_STATUS
	ofstream log;
	log.open("log.txt", ios::out | ios::app);
	log << "number of enemies" << SizeOfHorizontalPos << "\n";
	for (int i = 0; i < SizeOfHorizontalPos; i++)
		log << "Hpos: " << this->horizontalPositions[i] << "Vpos: " << this->verticalPositions[i] << "		";

	log << "\n";
	log.close();
#endif // DEBUG_STATUS
	for (int i = 0; !outsideScreen && (i < SizeOfHorizontalPos); i++) {
		outsideScreen = (this->horizontalPositions[i] + move <= 0.0f) ||
			(this->horizontalPositions[i] + move >= GameConst::GamexWidth - GameConst::SpritexEdge);
	}

	if (outsideScreen){
		aliensReachedBottom = this->downwardMovement();
		move = adjustDirection(move);
	}

	for (int i = 0; i < SizeOfHorizontalPos; i++)
		this->horizontalPositions[i] += move;

	return aliensReachedBottom;
}


/**
*   @brief  adjust the direction of the enemies of which they are moving towards
*
*   @param  bombs : a pointer to refers to Bombs class
*   @param  time : the new time (updated runtime) at the moment
*   @return nothing
*/
float Aliens::adjustDirection(float move){
	if (direction == "Right")
		move = move;
	else
		move = -move;
	return move;
}


/**
*   @brief  coordinate the fired bombs with the position of the aliens
*
*   @param  bombs : a pointer to refers to Bombs class 
*   @param  time : the new time (updated runtime) at the moment
*   @return nothing
*/


void Aliens::fire(Bombs* bombs, float time){
	bool shouldCreateBomb = (time - this->timeOfLastBomb) > this->timeBetweenBombs;
	uint8_t SizeOfHorizontalPos = horizontalPositions.size();
	if (shouldCreateBomb) {
		if (SizeOfHorizontalPos > 0){
			int index = (rand() % SizeOfHorizontalPos);
			bombs->create(this->horizontalPositions[index], this->verticalPositions[index]);
			this->timeOfLastBomb = time;
		}
	}
}

/**
*   @brief  Change the direction of the Aliens and continues the movement of the aliens and check the vertical position  
*
*   @return return true if an alien is at the bottom of the screen or false if otherwise
*/

bool Aliens::downwardMovement(){
	if (this->direction == "Left")
		this->direction = "Right";
	else
		this->direction = "Left";
	transform(this->verticalPositions.begin(), this->verticalPositions.end(), this->verticalPositions.begin(),
		bind2nd(std::plus<float>(), GameConst::SpritexEdge)); 
	for (int i = 0; i < int(horizontalPositions.size()); i++) {
		if (verticalPositions[i] >= GameConst::GamexHeight - GameConst::SpritexEdge)
			return true;
	}
	return false;
}
