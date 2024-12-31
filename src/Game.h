#pragma once
#include "structs.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "Player.h"
#include "Pillar.h"
#include <vector>
#include <deque>
#include <memory>
#include <iostream>

class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	~Game();

	void Run( );

	void Update(float elapsedSec);

	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
	{
		if (e.keysym.scancode == SDL_SCANCODE_W)
		{
			m_KeysPressed.m_WIsPressed = true;
		}
		if (e.keysym.scancode == SDL_SCANCODE_A)
		{
			m_KeysPressed.m_AIsPressed = true;
		}
		if (e.keysym.scancode == SDL_SCANCODE_S)
		{
			m_KeysPressed.m_SIsPressed = true;
		}
		if (e.keysym.scancode == SDL_SCANCODE_D)
		{
			m_KeysPressed.m_DIsPressed = true;
		}
		if (e.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			m_KeysPressed.m_SpaceIsPressed = true;
		}
	}
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
	{
		if (e.keysym.scancode == SDL_SCANCODE_W)
		{
			m_KeysPressed.m_WIsPressed = false;
		}
		if (e.keysym.scancode == SDL_SCANCODE_A)
		{
			m_KeysPressed.m_AIsPressed = false;
		}
		if (e.keysym.scancode == SDL_SCANCODE_S)
		{
			m_KeysPressed.m_SIsPressed = false;
		}
		if (e.keysym.scancode == SDL_SCANCODE_D)
		{
			m_KeysPressed.m_DIsPressed = false;
		}
		if (e.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			m_KeysPressed.m_SpaceIsPressed = false;
		}
	}
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
	{
		
	}
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
	{
		if (m_pPlayer->GetEnergy() > 100.f)
		{
			Point2f mousePos{ static_cast<float>(e.x),static_cast<float>(e.y) };
			ThreeBlade playerPos{ m_pPlayer->GetPos() };
			TwoBlade velocity{ mousePos.x - playerPos[0],mousePos.y - playerPos[1],0,0,0,0 };
			velocity /= velocity.VNorm();

			m_Bullets.emplace_back(Bullet{ ThreeBlade{playerPos[0],playerPos[1],10.f,playerPos[3]},velocity });
			m_pPlayer->LoseEnergy(100.f);
		}
		else std::cout << "No energy: " << m_pPlayer->GetEnergy() << std::endl;
	}
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
	{
		
	}

	const Rectf& GetViewPort() const
	{
		return m_Viewport;
	}

private:
	// DATA MEMBERS
	// The window properties
	const Window m_Window;
	const Rectf m_Viewport;
	// The window we render to
	SDL_Window* m_pWindow;
	// OpenGL context
	SDL_GLContext m_pContext;
	// Init info
	bool m_Initialized;
	// Prevent timing jumps when debugging
	const float m_MaxElapsedSeconds;
	
	// FUNCTIONS
	void InitializeGameEngine( );
	void CleanupGameEngine( );
	void InitializeVariables();
	void CleanUpVariables();

	void PlayerBorderCheck();
	void BulletBorderCheck();

	//Player
	std::unique_ptr<Player> m_pPlayer{};

	//Border
	OneBlade m_BottomBorder{ 0,0,1,0 };
	OneBlade m_TopBorder{ -m_Window.height,0,1,0 };
	OneBlade m_LeftBorder{ 0,1,0,0 };
	OneBlade m_RightBorder{ -m_Window.width,1,0,0 };

	//Rotate around line
	Pillar m_Pillar{ TwoBlade{m_Window.width/2,m_Window.height/2,0,0,0,1} ,200,240.f};

	OneBlade m_Plane{ (m_Window.width-10.f)/2.f / 2,1,1,0 };
	
	//Keys being pressed;
	IsPressed m_KeysPressed{};

	//Bullets
	std::deque<Bullet> m_Bullets;

	//update
	const int SUBSTEPS{ 8 };
};
