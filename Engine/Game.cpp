/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// reticle color change
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		SetReticleYellow();
	}
	else
	{
		SetReticleWhite();
	}

	// change reticle color if X is between 350 and 450
	//if (x >= (gfx.ScreenWidth / 2) - (centerStripWidth / 2) && x <= (gfx.ScreenWidth / 2) + (centerStripWidth / 2))
	//{
	//	SetReticleBlue();
	//}

	if ((x + reticleMaxSize >= targetX && x - reticleMaxSize <= targetX) && 
		(y + reticleMaxSize >= targetY && y - reticleMaxSize < targetY))
	{
		SetReticleBlue();
	}

	// check which reticle to draw (default / alternative)
	altReticle = wnd.kbd.KeyIsPressed(VK_CONTROL);

	// make sure there is one velocity increase per button press
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (!inhibitUp)
		{
			vy -= 1;
			inhibitUp = true;
		}
	}
	else
	{
		inhibitUp = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (!inhibitDown)
		{
			vy += 1;
			inhibitDown = true;
		}
	}
	else
	{
		inhibitDown = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (!inhibitLeft)
		{
			vx -= 1;
			inhibitLeft = true;
		}
	}
	else
	{
		inhibitLeft = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (!inhibitRight)
		{
			vx += 1;
			inhibitRight = true;
		}
	}
	else
	{
		inhibitRight = false;
	}

	// update position with velocity
	x += vx;
	y += vy;

	// handle stopping at screen boundary
	// right edge
	if(x + reticleMaxSize > gfx.ScreenWidth)
	{ 
		x = gfx.ScreenWidth - reticleMaxSize;
		vx = 0;
	}

	// left edge
	if (x - reticleMaxSize < 0)
	{
		x = reticleMaxSize;
		vx = 0;
	}

	// bottom edge
	if (y + reticleMaxSize > gfx.ScreenHeight)
	{
		y = gfx.ScreenHeight - reticleMaxSize;
		vy = 0;
	}

	//top edge
	if (y - reticleMaxSize < 0)
	{
		y = reticleMaxSize;
		vy = 0;
	}
}

void Game::SetReticleWhite()
{
	r = 255;
	g = 255;
	b = 255;
}

void Game::SetReticleBlue()
{
	r = 0;
	g = 0;
	b = 255;
}

void Game::SetReticleYellow()
{
	r = 255;
	g = 255;
	b = 0;
}

void Game::DrawReticleSmall(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(-5 + x, y, r, g, b);
	gfx.PutPixel(-4 + x, y, r, g, b);
	gfx.PutPixel(-3 + x, y, r, g, b);
	gfx.PutPixel(3 + x, y, r, g, b);
	gfx.PutPixel(4 + x, y, r, g, b);
	gfx.PutPixel(5 + x, y, r, g, b);
	gfx.PutPixel(x, -5 + y, r, g, b);
	gfx.PutPixel(x, -4 + y, r, g, b);
	gfx.PutPixel(x, -3 + y, r, g, b);
	gfx.PutPixel(x, 3 + y, r, g, b);
	gfx.PutPixel(x, 4 + y, r, g, b);
	gfx.PutPixel(x, 5 + y, r, g, b);
}

void Game::DrawReticleBig(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(-9 + x, y, r, g, b);
	gfx.PutPixel(-8 + x, y, r, g, b);
	gfx.PutPixel(-7 + x, y, r, g, b);
	gfx.PutPixel(7 + x, y, r, g, b);
	gfx.PutPixel(8 + x, y, r, g, b);
	gfx.PutPixel(9 + x, y, r, g, b);
	gfx.PutPixel(x, -9 + y, r, g, b);
	gfx.PutPixel(x, -8 + y, r, g, b);
	gfx.PutPixel(x, -7 + y, r, g, b);
	gfx.PutPixel(x, 7 + y, r, g, b);
	gfx.PutPixel(x, 8 + y, r, g, b);
	gfx.PutPixel(x, 9 + y, r, g, b);
}

void Game::DrawBox(int targetX, int targetY, int r, int g, int b)
{
	gfx.PutPixel(-5 + targetX, -5 + targetY, r, g, b);
	gfx.PutPixel(-5 + targetX, -4 + targetY,  r, g, b);
	gfx.PutPixel(-5 + targetX, -3 + targetY,  r, g, b);
	gfx.PutPixel(-4 + targetX, -5 + targetY,  r, g, b);
	gfx.PutPixel(-3 + targetX, -5 + targetY, r, g, b);
	gfx.PutPixel(-5 + targetX, 5 + targetY, r, g, b);
	gfx.PutPixel(-5 + targetX, 4 + targetY, r, g, b);
	gfx.PutPixel(-5 + targetX, 3 + targetY, r, g, b);
	gfx.PutPixel(-4 + targetX, 5 + targetY, r, g, b);
	gfx.PutPixel(-3 + targetX, 5 + targetY, r, g, b);
	gfx.PutPixel(5 + targetX, -5 + targetY, r, g, b);
	gfx.PutPixel(5 + targetX, -4 + targetY, r, g, b);
	gfx.PutPixel(5 + targetX, -3 + targetY, r, g, b);
	gfx.PutPixel(4 + targetX, -5 + targetY, r, g, b);
	gfx.PutPixel(3 + targetX, -5 + targetY, r, g, b);
	gfx.PutPixel(5 + targetX, 5 + targetY, r, g, b);
	gfx.PutPixel(5 + targetX, 4 + targetY, r, g, b);
	gfx.PutPixel(5 + targetX, 3 + targetY, r, g, b);
	gfx.PutPixel(4 + targetX, 5 + targetY, r, g, b);
	gfx.PutPixel(3 + targetX, 5 + targetY, r, g, b);
}

void Game::ComposeFrame()
{
	// draw stationary reticle
	DrawBox(targetX, targetY, 255, 255, 255);

	if (!altReticle)
	{
		DrawReticleSmall(x, y, r, g, b);
	}
	else
	{
		DrawReticleBig(x, y, r, g, b);
	}
}