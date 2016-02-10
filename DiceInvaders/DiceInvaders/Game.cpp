/**
*  @file    Game.cpp
*  @author  Mehrdad Mehraban
*  @date    1/29/2015
*  @version 1.0
*
*  @brief Game class manages the other classes namely Player, Aliens, Bombs and Rockets by 
*  making an object of each classes and feeds the required methods and fields to the DiceInvaders class. 
*/

#include "Game.h"
#include "Player.h"
#include <fstream>


/**
*   @brief	Default constructor
*
*   @param  system : a pointer to refers to Bombs class
*
*   @return nothing
*/
Game::Game(IDiceInvaders* system){
	aliens = new Aliens(system);
	player = new Player(system);
	bombs = new Bombs(system);
	rockets = new Rockets(system);
}


/**
*   @brief  Destructor (terminate the pointers)
*
*   @return nothing
*/
Game::~Game(){
	delete player;
	delete aliens;
	delete bombs;
	delete rockets;
}


/**
*   @brief  Draws the sprite of all pointer
*
*   @return nothing
*/
void Game::drawSprites(){
	player->drawSprite();
	aliens->draw();
	bombs->draw();
	rockets->draw();
}


/**
*   @brief  Update the screen acoring to the movement 
*
*   @param  move : The calculated current move
*   @param  keys : the keyboard status on each occasion
*   @return return true if an alien is at the bottom of the screen (Gameover) or false if otherwise
*/
bool Game::updateScreen(float move, IDiceInvaders::KeyStatus keys) {
	if (aliens->updatePosition(0.25f * move))
		return true;
	bombs->updatePosition(2.0f * move);
	rockets->updatePosition(2.5f * move);
	if (keys.right)
		player->updatePosition(move);
	else if (keys.left)
		player->updatePosition(-move);
	return false;
}

/**
*   @brief	Update game status of the game
*
*   @param  system : a pointer to refers to Bombs class
*
*   @return nothing
*/
void Game::updateGameStatus(IDiceInvaders* system){
	
	char *textcounters = (char*)malloc(sizeof(char) * 4);
	_itoa_s(player->getscore(), textcounters, 4, 10);
	system->drawText(int(GameConst::GamexWidth - 70), int(GameConst::GamexHeight - 20), "Score: ");
	system->drawText(int(GameConst::GamexWidth - 20), int(GameConst::GamexHeight - 20), textcounters);

	_itoa_s(player->getlife(), textcounters, 4, 10);
	system->drawText(int(0), int(GameConst::GamexHeight - 20), "Life: ");
	system->drawText(int(30), int(GameConst::GamexHeight - 20), textcounters);
}

/**
*   @brief  Detect all of the related collision for  aliens and player
*
*
*   @return nothing
*/
void Game::detectCollisions(){
	uint8_t _life = player->getlife();
	uint16_t _score = player->getscore();

	if (bombs->isCollision(this->player->horizontalPosition, GameConst::GamexHeight - GameConst::SpritexEdge)){
		_life--;
	}
	for (int i = 0; i < int(this->aliens->horizontalPositions.size()); i++) {
		bool horizontalOverlap = abs(this->player->horizontalPosition - this->aliens->horizontalPositions[i]) < GameConst::SpritexEdge;
		bool verticalOverlap = abs(GameConst::GamexHeight - GameConst::SpritexEdge - this->aliens->verticalPositions[i]) < GameConst::SpritexEdge;
		if (horizontalOverlap && verticalOverlap) {
			this->aliens->destroy(i);
			_life--;
			_score++;
		}
	}
	player->setlife(_life);
	_score += checkRocketCollision();
	player->setscore(_score);

}

/**
*   @brief	Update game status of the game
*
*   @return get the remained life from the player
*/
int Game::LifeRemained(){
	return player->getlife();
}

/**
*   @brief	Check the fire key for fire rocket as well bombs for aliens 
*
*   @param  keys : represend the keyboard status  
*   @param  newTime : the new time (updated runtime) at the moment
*   @return nothing
*/
void Game::fireKey(IDiceInvaders::KeyStatus keys, float newTime){
	if (keys.fire)
		this->player->fire(this->rockets, newTime);
	this->aliens->fire(this->bombs, newTime);

}

/**
*   @brief	Check for collision for rockets and aliens for updating the scores and generate the updated states of aliens.
*
*
*   @return returns true if there is a collision between the rockets and aliens
*/
bool Game::checkRocketCollision(){
	for (int i = 0; i < int(this->aliens->horizontalPositions.size()); i++) {
		if (rockets->isCollision(this->aliens->horizontalPositions[i], this->aliens->verticalPositions[i])) {
			this->aliens->destroy(i);
			if (this->aliens->horizontalPositions.size() == 0) {
				this->aliens->timeBetweenBombs *= 0.5f;
				this->aliens->generateAliens();
			}

			return true;
		}
	}
	return false;
}

