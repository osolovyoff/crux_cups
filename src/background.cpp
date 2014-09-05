#include "background.h"
#include "settings.h"
#include "utils.h"
#include <math.h>

extern HGE * hge;
float shift = 50.f;

void Background::Initialize()
{
	shift = (float)GetSystemMetrics(SM_CXSCREEN) - settings.GetScreenWidth() ;

	HTEXTURE tex = hge->Texture_Load("img/bg.jpg");
	m_sprite = new hgeSprite(tex,0,0,(float)settings.GetScreenWidth()+shift,(float)settings.GetScreenHeight()+shift);

	x = shift/2;
	y = shift/2;

	dx = 0;
	dy = 0;
}

void Background::Release()
{
	delete m_sprite;
}

void Background::Render()
{
	m_sprite->Render(-x,-y);
}

void Background::Update()
{
	Randomize();
	const float dt = hge->Timer_GetDelta();
	const float speed = 8*shift;
	const int xa = static_cast<int>(shift - x);
	const int xb = (int) x;
	const int ya = static_cast<int>(shift - y);
	const int yb = (int) y;

	float rnd_x = fRandom(-xb,xa);
	float rnd_y = fRandom(-yb,ya);
	rnd_x = rnd_x * dt / speed;
	rnd_y = rnd_y * dt / speed;

	if ( x < 0 ) rnd_x = fabs(rnd_x);
	if ( y < 0 ) rnd_y = fabs(rnd_y);
	if ( shift < x ) rnd_x = -1*fabs(rnd_x);
	if ( shift < y ) rnd_y = -1*fabs(rnd_y);

	dx += rnd_x;
	dy += rnd_y;

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x > shift) x = shift;
	if (y > shift) y = shift;

	x = x + dx;
	y = y + dy;
}

Background::~Background()
{
	Release();
}

