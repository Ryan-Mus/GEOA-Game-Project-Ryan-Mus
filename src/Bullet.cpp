//---------------------------
// Include Files
//---------------------------
#include "Bullet.h"
#include "utils.h"
#include <iostream>
//---------------------------
// Constructor & Destructor
//---------------------------
Bullet::Bullet(const ThreeBlade& pos, const TwoBlade& velocity): m_Pos{pos},m_Velocity{velocity},m_Speed{500.f}
{
	//std::cout << m_Pos << " " << m_Velocity << std::endl;
}

//---------------------------
// Member functions
//---------------------------

void Bullet::Update(float elapsedSec)
{
	math::Translate(m_Pos, m_Velocity, m_Speed * elapsedSec);
}

void Bullet::Draw() const
{
	//std::cout << (m_Pos/m_Pos.VNorm()) << std::endl;
	utils::SetColor(Color4f{ m_Pos[0]/m_Pos.VNorm(), m_Pos[1] / m_Pos.VNorm(), m_Pos[2] / m_Pos.VNorm(),1.f});
	utils::FillEllipse(m_Pos[0], m_Pos[1], 5.f, 5.f);
}

void Bullet::RotateBullet(const TwoBlade& line, float degrees)
{
	math::RotateAroundLine(m_Pos, line, degrees);
	math::RotateAroundLine(m_Velocity, line, degrees);
}

void Bullet::ReflectBullet(const OneBlade& plane)
{
	m_Velocity = (plane * m_Velocity * ~plane).Grade2();
}



