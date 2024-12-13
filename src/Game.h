#pragma once
#include "structs.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "FlyFish.h"
#include "Player.h";

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
	}
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
	{
		
	}
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
	{
		
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

	//Player
	Player* m_pPlayer{};

	//Border
	OneBlade m_BottomBorder{ 0,1,0,0 };
	OneBlade m_LeftBorder{ 0,0,1,0 };

	//Rotate around line
	TwoBlade m_Pillar{ m_Window.width / 2.f,m_Window.height / 2.f,0,0,0,1 };

	OneBlade m_Plane{ (m_Window.width-10.f)/2.f / 2,1,1,0 };
	
	//Keys being pressed;
	IsPressed m_KeysPressed{};
};
