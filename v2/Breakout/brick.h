//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"
#include <vector>

// Types

// Constants

// Prototypes

class CBrick : public CEntity
{
    // Member Functions
public:
    CBrick();
    virtual ~CBrick();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    void SetHit(bool _b);
    bool IsHit() const;

	int i_Counter = 200;
	bool b_GoingRight = false;
	
	int i_AttackTimer = 200;

	void EnemyMovement();
	void EnemyAttack();


protected:

private:
    CBrick(const CBrick& _kr);
    CBrick& operator= (const CBrick& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;

private:
	std::vector<CBall*> m_Bullets;
	float m_fDeltaTick;

};


#endif    // __BRICK_H__

