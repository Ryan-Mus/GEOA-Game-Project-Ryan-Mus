#pragma once
//---------------------------
// Include Files
//---------------------------
#include "Pillar.h"
#include "PillarBullet.h"
//---------------------------
// Constructor & Destructor
//---------------------------
Pillar::Pillar(TwoBlade line, float radius,float speed):m_Line{line},m_Radius{radius},m_Speed{speed}
{
	// nothing to create
}

//---------------------------
// Member functions
//---------------------------

void Pillar::Draw() const
{
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawEllipse(Point2f{ m_Line[0],m_Line[1] }, m_Radius, m_Radius);
	utils::FillEllipse(Point2f{ m_Line[0],m_Line[1] }, 2, 2);
}

void Pillar::Update(float elapsedSec, std::deque<Bullet>& bullets)
{
	for (Bullet& bullet : bullets)
	{
		if (math::GetDistance(m_Line, bullet.GetPos()) < m_Radius)
		{
			bullet.RotateBullet(m_Line, m_Speed * elapsedSec);
		}
	}
}

void Pillar::Update(float elapsedSec, std::deque<Bullet>& bullets, std::vector<Enemy>& enemies)
{
	for (auto& bullet : bullets)
	{
		if (math::GetDistance(m_Line, bullet.GetPos()) < m_Radius)
		{
			bullet.RotateBullet(m_Line, m_Speed * elapsedSec);
		}
	}
	for (auto& enemy : enemies)
	{
		if (math::GetDistance(m_Line, enemy.GetPos()) < m_Radius)
		{
			enemy.RotateEnemy(m_Line, m_Speed * elapsedSec);
		}
	}
}

void Pillar::Update(float elapsedSec, std::deque<Bullet>& bullets, ThreeBlade& playerPos, std::deque<PillarBullet>& pillarBullets, std::vector<Enemy>& enemies)
{
	if (math::GetDistance(m_Line, playerPos) < m_Radius)
	{
		math::RotateAroundLine(playerPos, m_Line, m_Speed * elapsedSec);
	}
	for (auto& bullet : bullets)
	{
		if (math::GetDistance(m_Line, bullet.GetPos()) < m_Radius)
		{
			bullet.RotateBullet(m_Line, m_Speed * elapsedSec);
		}
	}
	for (auto& pillarBullet : pillarBullets)
	{
		if (math::GetDistance(m_Line, pillarBullet.GetLine()) < m_Radius)
		{
			pillarBullet.RotateBullet(m_Line, m_Speed * elapsedSec);
		}
	}
	for (auto& enemy : enemies)
	{
		if (math::GetDistance(m_Line, enemy.GetPos()) < m_Radius)
		{
			enemy.RotateEnemy(m_Line, m_Speed * elapsedSec);
		}
	}
}

void Pillar::RotatePillar(const TwoBlade& line, float degrees)
{
	math::RotateAroundLine(m_Line, line, degrees);
}




