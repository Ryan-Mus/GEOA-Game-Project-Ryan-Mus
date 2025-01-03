#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "MathHelp.h"
//-----------------------------------------------------
// Enemy Class									
//-----------------------------------------------------
class Enemy final
{
public:
	Enemy(const ThreeBlade& spawnPoint);	// Constructor
	~Enemy() = default;						// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Enemy(const Enemy& other)					= default;
	Enemy(Enemy&& other) noexcept				= default;
	Enemy& operator=(const Enemy& other)		= default;
	Enemy& operator=(Enemy&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Update(float elapsedSec, const ThreeBlade& playerPos);
	void Draw() const;
	
	ThreeBlade GetPos() const { return m_Pos; };
	int GetHealth() const { return m_Health; };
	void LoseHealth(int amount) { m_Health -= amount; };

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ThreeBlade m_Pos;
	int m_Health;
	float Speed{ 250.f };
};

 
