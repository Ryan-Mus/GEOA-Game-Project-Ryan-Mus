#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "MathHelp.h"

//-----------------------------------------------------
// MyClass Class									
//-----------------------------------------------------
class Bullet final
{
public:
	Bullet(const ThreeBlade& pos, const TwoBlade& velocity);				// Constructor
	~Bullet() = default;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Bullet(const Bullet& other)					= default;
	Bullet(Bullet&& other) noexcept				= default;
	Bullet& operator=(const Bullet& other)		= default;
	Bullet& operator=(Bullet&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Update(float elapsedSec);
	void Draw() const;
	void RotateBullet(const TwoBlade& line, float degrees);
	void ReflectBullet(const OneBlade& plane);

	ThreeBlade GetPos() { return m_Pos; };


private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ThreeBlade m_Pos;
	TwoBlade m_Velocity;
	float m_Speed;
	
};

 
