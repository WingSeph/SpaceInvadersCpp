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
#include <stdlib.h>  
#include <time.h>   
#include "ball.h"


// This Include
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBrick::CBrick()
: m_bHit(false)
{

}

CBrick::~CBrick()
{

}

bool
CBrick::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));
	i_MoveCounter = 100;

	i_AttackTimer = rand() % 500;

    return (true);
}

void
CBrick::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
	for (int i = 0; i < m_Bullets.size(); i++)
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
}

void
CBrick::Process(float _fDeltaTick)
{
	float m_fDeltaTick = _fDeltaTick;

	if (!m_bHit)
    {
		CEntity::Process(_fDeltaTick);
    }

	EnemyMovement();
	EnemyAttack();
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i]->Process(_fDeltaTick);
	}

}

void
CBrick::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
CBrick::IsHit() const
{
    return (m_bHit);
}

void
CBrick::EnemyMovement()
{
	i_Counter--;

	if (i_Counter == 0)
	{
		if (GetX() == 0)
		{
			SetY(GetY() + 5);
			b_GoingRight = true;
		}
		else if (GetX() == 400)
		{
			SetY(GetY() + 5);
			b_GoingRight = false;
		}

		if (!b_GoingRight)
		{
			SetX(GetX() - 5);
		}
		else if (b_GoingRight)
		{
			SetX(GetX() + 5);
		}

		i_Counter = 200;
	}
}

void 
CBrick::EnemyAttack()
{
	if (i_AttackTimer > 0)
	{
		i_AttackTimer--;
	}

	if (i_AttackTimer <= 0)
	{
		//shoot bullet
		m_Bullets.clear();
		if (m_Bullets.size() == 0)
		{

			//create new ball
			CBall* m_pBall = new CBall;

			m_pBall->SetIsEnemy(true);

			//set position to middle of enemy
			m_pBall->SetX(GetX());
			m_pBall->SetY(GetY());

			//initialise velocity
			m_pBall->Initialise(GetX(), GetY(), 0.0f, 300.0f);

			//Process
			

			m_Bullets.push_back(m_pBall);

			//reset timer
			srand(time(NULL));
			i_AttackTimer = rand() % 5000;
		}
	}



}