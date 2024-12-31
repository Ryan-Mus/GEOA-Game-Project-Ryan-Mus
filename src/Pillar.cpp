//---------------------------
// Include Files
//---------------------------
#include "Pillar.h"

//---------------------------
// Constructor & Destructor
//---------------------------
Pillar::Pillar(TwoBlade line, float radius,float speed):m_Line{line},m_Radius{radius},m_Speed{speed}
{
	// nothing to create
}

void Pillar::Draw() const
{
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawEllipse(Point2f{ m_Line[0],m_Line[1] }, m_Radius, m_Radius);
	utils::FillEllipse(Point2f{ m_Line[0],m_Line[1] }, 2, 2);
}

void Pillar::Update(float elapsedSec, std::deque<Bullet>& bullets, ThreeBlade& playerPos)
{
	if (math::GetDistance(m_Line, playerPos) < m_Radius)
	{
		math::RotateAroundLine(playerPos, m_Line, m_Speed * elapsedSec);
	}
	for (Bullet& bullet : bullets)
	{
		if (math::GetDistance(m_Line, bullet.GetPos()) < m_Radius)
		{
			bullet.RotateBullet(m_Line, m_Speed * elapsedSec);
		}
	}
}

//---------------------------
// Member functions
//---------------------------

// Write member functions here




