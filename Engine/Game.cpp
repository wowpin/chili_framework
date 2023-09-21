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
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		b = 0;
	}
	else
	{
		b = 255;
	}

	altReticle = wnd.kbd.KeyIsPressed(VK_CONTROL);

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

	x += vx;
	y += vy;

	if (x < reticleRadius)
	{
		//x = reticleRadius;
		x -= vx;
		vx = 0;
	}
	if (x > Graphics::ScreenWidth - reticleRadius)
	{
		//x = Graphics::ScreenWidth - reticleRadius;
		x -= vx;
		vx = 0;
	}
	if (y < reticleRadius)
	{
		//y = reticleRadius;
		y -= vy;
		vy = 0;
	}
	if (y > Graphics::ScreenHeight - reticleRadius)
	{
		//y = Graphics::ScreenHeight - reticleRadius;
		y -= vy;
		vy = 0;
	}

}

void Game::ComposeFrame()
{
	if (!altReticle)
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
	else
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
}