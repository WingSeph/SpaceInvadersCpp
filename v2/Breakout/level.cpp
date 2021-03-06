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
#include "Game.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iBricksRemaining(0)
, m_pPaddle(0)
, m_pBall(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecBricks.size() > 0)
    {
        CBrick* pBrick = m_vecBricks[m_vecBricks.size() - 1];

        m_vecBricks.pop_back();

        delete pBrick;
    }

    delete m_pPaddle;
    m_pPaddle = 0;

    delete m_pBall;
    m_pBall = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    const float fBallVelX = 0.0f;
    const float fBallVelY = 300.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);



	//m_pBall = new CBall();
    //VALIDATE(m_pBall->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, fBallVelX, fBallVelY));

    m_pPaddle = new CPaddle();
    VALIDATE(m_pPaddle->Initialise());




    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pPaddle->SetX(_iWidth / 2.0f);
    m_pPaddle->SetY(static_cast<float>(_iHeight - ( 1.5f * m_pPaddle->GetHeight())));

    const int kiNumBricks = 35;
    const int kiStartX = 40;
    const int kiGap = 5;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

	//create 36 sprites

    for (int i = 0; i < kiNumBricks; ++i)
    {
        CBrick* pBrick = new CBrick();
        VALIDATE(pBrick->Initialise());

        pBrick->SetX(static_cast<float>(iCurrentX));
        pBrick->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

        if (iCurrentX > _iWidth - 10)
        {
            iCurrentX = kiStartX;
            iCurrentY += 45;
        }

        m_vecBricks.push_back(pBrick);
    }

    SetBricksRemaining(kiNumBricks);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        m_vecBricks[i]->Draw();
    }

    m_pPaddle->Draw();
	//m_pBall->Draw();

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	//m_pBall->Process(_fDeltaTick);
	m_pPaddle->Process(_fDeltaTick);
	//ProcessBallWallCollision();
	//ProcessPaddleWallCollison();
	//ProcessBallPaddleCollision();
    //ProcessBallBrickCollision();

    ProcessCheckForWin();
//	ProcessBallBounds();

    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        m_vecBricks[i]->Process(_fDeltaTick);
    }
	
   
    
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);







}

CPaddle* 
CLevel::GetPaddle() const
{
    return (m_pPaddle);
}


void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        if (!m_vecBricks[i]->IsHit())
        {
            return;
        }
    }

    CGame::GetInstance().GameOverWon();
}

int 
CLevel::GetBricksRemaining() const
{
    return (m_iBricksRemaining);
}

void 
CLevel::SetBricksRemaining(int _i)
{
    m_iBricksRemaining = _i;
    UpdateScoreText();
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
CLevel::UpdateScoreText()
{
    m_strScore = "Aliens Remaining: ";

    m_strScore += ToString(GetBricksRemaining());
}


void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}


void
CLevel::ProcessBallBrickCollision()
{
	// if(m_pPaddle->)

	
	for (int i = 0; i < m_pPaddle->GetBulletAmounts(); i++)
	{
		//CBall* m_pBall = m_pPaddle->GetBullet();

		for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
		{
			if (!m_vecBricks[i]->IsHit())
			{
				float fBallR = m_pBall->GetRadius();

				float fBallX = m_pBall->GetX();
				float fBallY = m_pBall->GetY();

				float fBrickX = m_vecBricks[i]->GetX();
				float fBrickY = m_vecBricks[i]->GetY();

				float fBrickH = m_vecBricks[i]->GetHeight();
				float fBrickW = m_vecBricks[i]->GetWidth();

				if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
					(fBallX - fBallR < fBrickX + fBrickW / 2) &&
					(fBallY + fBallR > fBrickY - fBrickH / 2) &&
					(fBallY - fBallR < fBrickY + fBrickH / 2))
				{
					//Hit the front side of the brick...
					m_pBall->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
					m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1);
					m_vecBricks[i]->SetHit(true);

					SetBricksRemaining(GetBricksRemaining() - 1);
				}
			}
		}
	}

}


/*
void
CLevel::ProcessBallBounds()
{
if (m_pBall->GetX() < 0)
{
m_pBall->SetX(0);
}
else if (m_pBall->GetX() > m_iWidth)
{
m_pBall->SetX(static_cast<float>(m_iWidth));
}

if (m_pBall->GetY() < 0)
{
m_pBall->SetY(0.0f);
}
else if (m_pBall->GetY() > m_iHeight)
{
CGame::GetInstance().GameOverLost();
//m_pBall->SetY(static_cast<float>(m_iHeight));
}
}
*/



/*

void
CLevel::ProcessBallPaddleCollision()
{
float fBallR = m_pBall->GetRadius();

float fBallX = m_pBall->GetX();
float fBallY = m_pBall->GetY();

float fPaddleX = m_pPaddle->GetX();
float fPaddleY = m_pPaddle->GetY();

float fPaddleH = m_pPaddle->GetHeight();
float fPaddleW = m_pPaddle->GetWidth();

if ((fBallX + fBallR > fPaddleX - fPaddleW / 2) && //ball.right > paddle.left
(fBallX - fBallR < fPaddleX + fPaddleW / 2) && //ball.left < paddle.right
(fBallY + fBallR > fPaddleY - fPaddleH / 2) && //ball.bottom > paddle.top
(fBallY - fBallR < fPaddleY + fPaddleH / 2))  //ball.top < paddle.bottom
{
m_pBall->SetY((fPaddleY - fPaddleH / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1); //Reverse ball's Y direction
}
}
*/

/*
void
CLevel::ProcessBallWallCollision()
{
if (m_pPaddle->GetBulletAmounts() != 0)
{

float fBallX = m_pBall->GetX();
float fBallY = m_pBall->GetY();
float fBallW = m_pBall->GetWidth();
float fBallH = m_pBall->GetHeight();

float fHalfBallW = fBallW / 2;
float fHalfBallH = fBallH / 2;

if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
{
delete m_pBall; //delete ball
}

if (fBallY  > m_iHeight - fHalfBallH)  //represents the situation when the ball has hit the bottom wall
{
delete m_pBall; //delete ball
}
}


}
*/
