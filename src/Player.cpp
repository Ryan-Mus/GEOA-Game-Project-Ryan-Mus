#include "Player.h";
#include "utils.h";
#include <iostream>;

Player::Player(ThreeBlade pos): m_Pos{pos}
{
	std::cout << "Player created\n";
}

void Player::DrawPlayer() const
{
	utils::SetColor(Color4f{ 0.3f,0.3f,1.f,1.f });
	utils::FillRect(m_Pos[0]-m_Size/2, m_Pos[1]-m_Size/2, m_Size, m_Size);
}

void Player::UpdatePlayer(IsPressed keysPressed,float elapsedSec)
{
	HandleInput(keysPressed);
	if (m_Velocity != TwoBlade{})
	{
		Motor translator{ Motor::Translation(m_Speed * elapsedSec,m_Velocity)};
		m_Pos = (translator * m_Pos * ~translator).Grade3();
	}
	
	//std::cout << "Player pos: " << m_Pos << std::endl;

	m_Velocity = {};
}

void Player::SetVelocity(TwoBlade velocity)
{
	
	m_Velocity = m_Velocity + velocity;

	//std::cout << "Velocity Set to " << m_Velocity << std::endl;
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
}
