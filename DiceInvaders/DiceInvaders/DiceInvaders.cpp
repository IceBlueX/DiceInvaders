
/*! \mainpage My Personal Index Page for DiceInvaders game
*
* \section intro_sec Introduction
*
* This is the introduction to a brief explanation of the written code. The DiceInvaders game composed of these esential objects.
*
* \section install_sec Installation
*
* \subsection step1 Part 1: The Classes
* The main classes in this program contain of the following : 
* Aside from the DiceInvaders class which is the Main class, Game class is composed of object from other 
* classes namely Player, Aliens, Bombs and Rockets.   
* \subsection step2 Part 2: NameSpaces
* The only utilized namespace (named GameConst) in this program is included in Constant header file which 
* Consist of constants that have been in this program multiple times.
*/
/**
*  @file    DiceInvaders.cpp
*  @author  Mehrdad Mehraban 
*  @date    1/29/2015
*  @version 1.0
*
*  @brief DiceInvaders class which is the Main class of the game "Dice Invaders" using the supplied library.
*
*  @section DESCRIPTION
*
*  Dice Invaders consists of four different objects: the player ship, 
*  the aliens, the aliens’ bombs and the player’s rockets. 
*  The goal of the game is to shoot as many aliens as possible 
*  without being hit by them or their bombs.
*  This game is written (C++) language in a great influence of Standard Template Library (STL) by Mirosoft Visual Studio 2013.
*
*/


#include "DiceInvaders.h"
#include "Constant.h"
#include "Game.h"
#include <windows.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <fstream>

/**
*  @brief Class that maintain the library of DiceInvaders dll file which is utilized in this game.
*/
class DiceInvadersLib
{
public:
	explicit DiceInvadersLib(const char* libraryPath)
	{
		m_lib = LoadLibrary(libraryPath);
		assert(m_lib);

		DiceInvadersFactoryType* factory = (DiceInvadersFactoryType*)GetProcAddress(
			m_lib, "DiceInvadersFactory");
		m_interface = factory();
		assert(m_interface);
	}

	~DiceInvadersLib()
	{
		FreeLibrary(m_lib);
	}

	IDiceInvaders* get() const
	{
		return m_interface;
	}

private:
	DiceInvadersLib(const DiceInvadersLib&);
	DiceInvadersLib& operator=(const DiceInvadersLib&);

private:
	IDiceInvaders* m_interface;
	HMODULE m_lib;
};


int APIENTRY WinMain(
	_In_ HINSTANCE instance,
	_In_opt_ HINSTANCE previousInstance,
	_In_ LPSTR commandLine,
	_In_ int commandShow)	//added the missing the SAL annotations
{
	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

	ofstream log;
	log.open ("log.txt");
	log << "init system\n";

	if (!system->init((int)GameConst::GamexWidth, (int)GameConst::GamexHeight)){
		return 0;
	}

	Game* game = new Game(system);	

	float lastTime = system->getElapsedTime();
	while (system->update())
	{
		log << "draw\n";
		game->drawSprites();
		game->updateGameStatus(system);

		float newTime = system->getElapsedTime();
		float move = (newTime - lastTime) * GameConst::MovexSpeed;
		lastTime = newTime;

		IDiceInvaders::KeyStatus keys;
		system->getKeyStatus(keys);
		game->fireKey(keys, newTime);

		log << "detect collisions\n";
		game->detectCollisions();

		
		log << "update screen\n";
		if (game->updateScreen(move, keys) || game->LifeRemained() <= 0 ){
			log << "Game is over\n";
			break;
		}
	}
	delete game;
	log.close();	
	Sleep(10000);
	system->destroy();
	return 0;
}



