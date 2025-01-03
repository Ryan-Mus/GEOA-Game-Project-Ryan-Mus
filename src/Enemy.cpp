//---------------------------
// Include Files
//---------------------------
#include "Enemy.h"
#include "utils.h"
//---------------------------
// Constructor & Destructor
//---------------------------
Enemy::Enemy(const ThreeBlade& spawnPoint): m_Pos{spawnPoint},m_Health{100}
{}
//---------------------------
// Member functions
//---------------------------
void Enemy::Update(float elapsedSec, const ThreeBlade& playerPos)
{
	math::Translate(m_Pos, TwoBlade{playerPos[0] - m_Pos[0],playerPos[1] - m_Pos[1],0,0,0,0 }, Speed * elapsedSec);
}

void Enemy::Draw() const
{
	utils::SetColor(Color4f{ 1 - m_Health / 100.f,m_Health / 100.f,0,1.f });
	utils::FillRect(m_Pos[0] - 30.f / 2, m_Pos[1] - 30.f / 2, 30.f, 30.f);
}




