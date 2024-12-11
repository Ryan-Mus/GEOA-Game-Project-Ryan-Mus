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

	void SetVelocity(TwoBlade velocity);
	TwoBlade GetVelocity() { return m_Velocity; };
	ThreeBlade GetPos() { return m_Pos; };
private:
	ThreeBlade m_Pos;
	TwoBlade m_Velocity{0,0,0,0,0,0};
	float m_Size{ 30 };
	float m_Speed{ 300.f };
};