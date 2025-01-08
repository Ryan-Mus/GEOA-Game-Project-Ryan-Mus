#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "MathHelp.h"
#include "utils.h"
#include "Bullet.h"
#include "Pillar.h"

#include <deque>
//-----------------------------------------------------
// PillarBullet Class									
//-----------------------------------------------------
class PillarBullet final
{
public:
    PillarBullet(const ThreeBlade& pos,const TwoBlade& velocity, float speed);  // Constructor
    ~PillarBullet() = default;                                             // Destructor

    // -------------------------
    // Copy/move constructors and assignment operators
    // -------------------------    
    PillarBullet(const PillarBullet& other) = default;
    PillarBullet(PillarBullet&& other) noexcept = default;
    PillarBullet& operator=(const PillarBullet& other) = default;
    PillarBullet& operator=(PillarBullet&& other) noexcept = default;

    //-------------------------------------------------
    // Member functions						
    //-------------------------------------------------
    void Update(float elapsedSec, std::deque<Bullet>& bullets, std::vector<Enemy>& enemies);
    void Draw() const;

    TwoBlade GetLine() const;
    float GetLifeTime() const { return m_LifeTime; }

    void RotateBullet(const TwoBlade& line, float degrees);
    void ReflectBullet(const OneBlade& plane);
private:
    //-------------------------------------------------
    // Datamembers								
    //-------------------------------------------------
    Pillar m_Pillar;
    TwoBlade m_Velocity;
    float m_Speed;
    float m_LifeTime{ 10.f };
};
