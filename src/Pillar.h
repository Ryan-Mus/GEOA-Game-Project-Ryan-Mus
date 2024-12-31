
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
	void Update(float elapsedSec,std::deque<Bullet>& bullets, ThreeBlade& playerPos);


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

 
