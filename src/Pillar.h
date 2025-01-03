
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#pragma once
#include "MathHelp.h"
#include "utils.h"
#include "Bullet.h"

#include <deque>

//-----------------------------------------------------
// Pillar Class									
//-----------------------------------------------------
class PillarBullet; //forward declaration
class Pillar final
{
public:
	Pillar(TwoBlade line, float radius = 50.f,float speed = 120.f);			// Constructor
	~Pillar() = default;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Pillar(const Pillar& other)					= default;
	Pillar(Pillar&& other) noexcept				= default;
	Pillar& operator=(const Pillar& other)		= default;
	Pillar& operator=(Pillar&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Draw() const;
	//Bullet Pillar Update
	void Update(float elapsedSec, std::deque<Bullet>& bullets);
	void Update(float elapsedSec,std::deque<Bullet>& bullets, ThreeBlade& playerPos);
	//Map Pillar update
	void Update(float elapsedSec, std::deque<Bullet>& bullets, ThreeBlade& playerPos, std::deque<PillarBullet>& pillarBullets);

	void Translate(const TwoBlade& direction, float distance)
	{
		math::Translate(m_Line, direction, distance);
	}
	void RotatePillar(const TwoBlade& line, float degrees);
	TwoBlade GetLine() const { return m_Line; };


private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	TwoBlade m_Line;
	float m_Radius;
	float m_Speed;
	
};

 
