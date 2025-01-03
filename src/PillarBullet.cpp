#include "PillarBullet.h"
#include "Pillar.h"

//---------------------------
// Constructor & Destructor
//---------------------------
PillarBullet::PillarBullet(const ThreeBlade& pos,const TwoBlade& velocity, float speed)
    : m_Velocity{ velocity }, m_Speed{ speed }, m_Pillar{ TwoBlade{ pos[0], pos[1], 0, 0, 0, 1 }, 100.f, 180.f }
{}

//---------------------------
// Member functions
//---------------------------
void PillarBullet::Update(float elapsedSec, std::deque<Bullet>& bullets)
{
    m_Pillar.Translate(m_Velocity, m_Speed * elapsedSec);
    for (Bullet& bullet : bullets)
    {
        if (math::GetDistance(m_Pillar.GetLine(), bullet.GetPos()) < 100.f)
        {
            bullet.TranslateBullet(m_Velocity, m_Speed * elapsedSec);
        }
    }
    m_Pillar.Update(elapsedSec, bullets);

    m_LifeTime -= elapsedSec;
}

void PillarBullet::Draw() const
{
    m_Pillar.Draw();
}

TwoBlade PillarBullet::GetLine() const
{
    return m_Pillar.GetLine();
}

void PillarBullet::RotateBullet(const TwoBlade& line, float degrees)
{
    m_Pillar.RotatePillar(line, degrees);
}

void PillarBullet::ReflectBullet(const OneBlade& plane)
{
    m_Velocity = (plane * -m_Velocity * ~plane).Grade2();
}
