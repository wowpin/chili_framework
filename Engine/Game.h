/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
	void SetReticleWhite();
	void SetReticleBlue();
	void SetReticleYellow();
	void SetReticleRed();
	void DrawReticleSmall(int x, int y, int r, int g, int b);
	void DrawReticleBig(int x, int y, int r, int g, int b);
	void DrawBox(int targetX, int targetY, int r, int g, int b);
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	int x = 100;
	int y = 100;

	const int targetX = 250;
	const int targetY = 400;

	const int displacement = 5;

	int r = 255;
	int g = 255;
	int b = 255;

	bool altReticle = false;

	int reticleMaxSize = 10;
	int centerStripWidth = 300;
	int targetSize = 10;

	int vx = 0;
	int vy = 0;

	bool inhibitUp = false;
	bool inhibitDown = false;
	bool inhibitLeft = false;
	bool inhibitRight = false;
};