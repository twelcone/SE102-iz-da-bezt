#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14

class CBrick : public CGameObject {
public: 
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CMap : public CGameObject {
public:
	CMap(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CMap2 : public CGameObject {
public:
	CMap2(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CCloud : public CGameObject {
public:
	CCloud(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Render(int x);
	void Update(DWORD dt) {}
};

class CGrass : public CGameObject {
public:
	CGrass(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Render(int x);
	void Update(DWORD dt) {}
};



class CMario : public CGameObject
{
protected:
	float vx;
public:
	CMario(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};

class CGoomba : public CGameObject
{
protected:
	float vx;
public:
	CGoomba(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};


