#pragma once
#include "structs.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "Player.h"
#include "Pillar.h"
#include "PillarBullet.h"
#include "Enemy.h"
#include <cmath>
#include <vector>
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
		if (e.keysym.scancode == SDL_SCANCODE_P)
		{
			m_DevMode = !m_DevMode;
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
		float requiredEnergy{ 100.f };
		if (m_DevMode) requiredEnergy = 0;
		if (m_pPlayer->GetEnergy() > requiredEnergy and e.button == SDL_BUTTON_LEFT)
		{
			Point2f mousePos{ static_cast<float>(e.x),static_cast<float>(e.y) };
			ThreeBlade playerPos{ m_pPlayer->GetPos() };
			TwoBlade velocity{ mousePos.x - playerPos[0],mousePos.y - playerPos[1],0,0,0,0 };
			velocity /= velocity.VNorm();

			m_Bullets.emplace_back(Bullet{ ThreeBlade{playerPos[0],playerPos[1],10.f,playerPos[3]},velocity });
			m_pPlayer->LoseEnergy(requiredEnergy);
		}
		else if (m_pPlayer->GetEnergy() > requiredEnergy*10.f and e.button == SDL_BUTTON_RIGHT)
		{
			Point2f mousePos{ static_cast<float>(e.x),static_cast<float>(e.y) };
			ThreeBlade playerPos{ m_pPlayer->GetPos() };
			TwoBlade velocity{ mousePos.x - playerPos[0],mousePos.y - playerPos[1],0,0,0,0 };
			velocity /= velocity.VNorm();
			if (playerPos[0] < 100) playerPos[0] = 101.f;
			if (playerPos[1] < 100) playerPos[1] = 101.f;
			if (playerPos[0] > m_Window.width - 100.f) playerPos[0] = m_Window.width - 101.f;
			if (playerPos[1] > m_Window.height- 100.f) playerPos[1] = m_Window.height - 101.f;
			m_PillarBullets.emplace_back(PillarBullet{ThreeBlade{playerPos[0],playerPos[1],0,0},velocity,300.f});
			m_pPlayer->LoseEnergy(requiredEnergy*10.f);
		}
		else
		{
			std::cout << "No energy: " << m_pPlayer->GetEnergy() << std::endl;
		}
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

	void UpdateEnemies(float elapsedSec);
	void UpdateBullets(float elapsedSec);
	void EnemySpawner(float elapsedSec);

	//Player
	std::unique_ptr<Player> m_pPlayer{};

	//Border
	OneBlade m_BottomBorder{ 0,0,1,0 };
	OneBlade m_TopBorder{ -m_Window.height,0,1,0 };
	OneBlade m_LeftBorder{ 0,1,0,0 };
	OneBlade m_RightBorder{ -m_Window.width,1,0,0 };

	//Pillar
	Pillar m_Pillar{ TwoBlade{m_Window.width/2,m_Window.height/2,0,0,0,1} ,200,120.f};
	
	//Keys being pressed;
	IsPressed m_KeysPressed{};

	//Bullets
	std::deque<Bullet> m_Bullets;
	std::deque<PillarBullet> m_PillarBullets;

	//Enemies
	std::vector<Enemy> m_Enemies;

	//update
	const int SUBSTEPS{ 8 };
	float m_TotalTime{0};
	float m_LastSpawnTime{ 0 };

	int m_Score{ 0 };

	bool m_DevMode{false};
};
