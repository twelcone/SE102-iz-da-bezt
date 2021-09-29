#include "Game.h"
#include "Mario.h"

CMario::CMario(float x, float y, float vx):CGameObject(x, y)
{
	this->vx = vx;
};

void CMario::Update(DWORD dt)
{
	x += vx*dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}

void CMario::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx>0) ani = CAnimations::GetInstance()->Get(500);
	else ani = CAnimations::GetInstance()->Get(501);

	ani->Render(x, y);
}

void CBrick::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(510);

	ani->Render(x, y);

}


void CMap::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(530);
	ani->Render(x, y);
}



void CMap2::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(531);
	ani->Render(x, y);
}


CGoomba::CGoomba(float x, float y, float vx):CGameObject(x, y)
{
	this->vx = vx;
};

void CGoomba::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}

void CGoomba::Render()
{
	LPANIMATION ani;

	if (vx > 0) ani = CAnimations::GetInstance()->Get(520);
	else ani = CAnimations::GetInstance()->Get(521);

	ani->Render(x, y);
}


void CCloud::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(550);

	ani->Render(x, y);

}

void CCloud::Render(int k) {

	LPANIMATION ani;
	switch(k) {
		default:
		case 0: ani = CAnimations::GetInstance()->Get(550); break;
		case 1: ani = CAnimations::GetInstance()->Get(551); break;
		case 2: ani = CAnimations::GetInstance()->Get(552); break;
		case 3: ani = CAnimations::GetInstance()->Get(553); break;
		case 4: ani = CAnimations::GetInstance()->Get(554); break;
		case 5: ani = CAnimations::GetInstance()->Get(555); break;
	}

	ani->Render(x, y);

}
