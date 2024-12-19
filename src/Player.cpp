#include "Player.h"
#include "utils.h"
#include "MathHelp.h"
#include <iostream>


Player::Player(ThreeBlade pos): m_Pos{pos}
{
	std::cout << "Player created\n";
}

void Player::DrawPlayer() const
{
	utils::SetColor(Color4f{ 0.3f,0.3f,1.f,1.f });
	utils::FillRect(m_Pos[0] - m_Size / 2, m_Pos[1] - m_Size / 2, m_Size, m_Size);
}

void Player::UpdatePlayer(IsPressed keysPressed,float elapsedSec)
{

	if (m_Velocity.VNorm() != 0) //vermijd translatie met 0
	{
		math::Translate(m_Pos, m_Velocity, m_Speed * elapsedSec);
	}
	
	//std::cout << "Player pos: " << m_Pos << std::endl;

	m_Velocity = {}; //Reset volocity
}

void Player::HandleInput(IsPressed keysPressed)
{
	if (keysPressed.m_WIsPressed)
	{
		m_Velocity += TwoBlade{ 0,1,0,0,0,0 };
	}
	if (keysPressed.m_AIsPressed)
	{
		m_Velocity += TwoBlade{ -1,0,0,0,0,0 };
	}
	if (keysPressed.m_SIsPressed)
	{
		m_Velocity += TwoBlade{ 0,-1,0,0,0,0 };
	}
	if (keysPressed.m_DIsPressed)
	{
		m_Velocity += TwoBlade{ 1,0,0,0,0,0 };
	}
	if (keysPressed.m_SpaceIsPressed)
	{
		m_Velocity += TwoBlade{ 0,0,1,0,0,0 };
	}
}
