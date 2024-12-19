#include "FlyFish.h"

struct IsPressed
{
	bool m_WIsPressed{ false };
	bool m_AIsPressed{ false };
	bool m_SIsPressed{ false };
	bool m_DIsPressed{ false };
	bool m_SpaceIsPressed{ false };
};

class Player
{
public:
	Player(ThreeBlade pos);
	
	void DrawPlayer() const;
	void UpdatePlayer(IsPressed keysPressed, float elapsedSec);

	void HandleInput(IsPressed keysPressed);

	TwoBlade GetVelocity() { return m_Velocity; };
	ThreeBlade GetPos() { return m_Pos; };
	void SetPos(const ThreeBlade& point) { m_Pos = point; };

	float GetEnergy() { return m_Pos[2]; };
	void  LoseEnergy(float amount) { m_Pos[2] -= amount; };
private:
	ThreeBlade m_Pos{};
	TwoBlade m_Velocity{};
	float m_Size{ 30 };
	float m_Speed{ 300.f };
};