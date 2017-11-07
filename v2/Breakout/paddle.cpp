//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Paddle.h"
#include "ball.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPaddle::CPaddle()
{

}

CPaddle::~CPaddle()
{

}

bool
CPaddle::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));

    return (true);
}

void
CPaddle::Draw()
{
	for (int i = 0; i < GetBulletAmounts(); i++)
	{
		if (m_Bullets[i]->GetY() <= 0)
		{
			m_Bullets.erase((m_Bullets.begin() + i));
		}
		else
		{
			m_Bullets[i]->Draw();
			m_Bullets[i]->Process(m_fDeltaTick);
		}




	}
    CEntity::Draw();
}

int
CPaddle::GetBulletAmounts()
{
	return (m_Bullets.size());
}

void
CPaddle::Process(float _fDeltaTick)
{
    
	m_fDeltaTick = _fDeltaTick;

	float fHalfPaddleW = static_cast<float>(m_pSprite->GetWidth() / 2.0f);

	//shoot ball
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		

		if (m_Bullets.size() == 0)
		{

			//create new ball
			CBall* m_pBall = new CBall;

			//set position to middle of paddle
			m_pBall->SetX(GetX());
			m_pBall->SetY(GetY());

			//initialise velocity
			m_pBall->Initialise(GetX(), GetY(), 0.0f, 300.0f);

			//Process
			m_pBall->SetIsEnemy(false);

			m_Bullets.push_back(m_pBall);
		}
	}

	

	//movement left or right
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 400.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 400.0f * _fDeltaTick;
	}
	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPaddleW;
	}
	else if (m_fX + fHalfPaddleW >= 385)
	{
		m_fX = 385-fHalfPaddleW;
	}
	
	CEntity::Process(_fDeltaTick);
}
