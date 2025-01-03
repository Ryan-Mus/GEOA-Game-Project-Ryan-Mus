#include <algorithm>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <chrono>
#include "Game.h"
#include "utils.h"
#include "MathHelp.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_Viewport{ 0,0,window.width,window.height }
	, m_pWindow{ nullptr }
	, m_pContext{ nullptr }
	, m_Initialized{ false }
	, m_MaxElapsedSeconds{ 0.1f }
{
	InitializeGameEngine();
	InitializeVariables();
}

Game::~Game()
{
	CleanupGameEngine();
	CleanUpVariables();
}

void Game::InitializeGameEngine()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_Init: " << SDL_GetError() << std::endl;
		return;
	}

	// Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Create window
	m_pWindow = SDL_CreateWindow(
		m_Window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(m_Window.width),
		int(m_Window.height),
		SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_CreateWindow: " << SDL_GetError() << std::endl;
		return;
	}

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return;
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_Window.isVSyncOn)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cerr << "BaseGame::Initialize( ), error when calling SDL_GL_SetSwapInterval: " << SDL_GetError() << std::endl;
			return;
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	glOrtho(0, m_Window.width, 0, m_Window.height, -1, 1); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(m_Window.width), int(m_Window.height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling TTF_Init: " << TTF_GetError() << std::endl;
		return;
	}


	m_Initialized = true;
}

void Game::Run()
{
	if (!m_Initialized)
	{
		std::cerr << "BaseGame::Run( ), BaseGame not correctly initialized, unable to run the BaseGame\n";
		std::cin.get();
		return;
	}

	// Main loop flag
	bool quit{ false };

	// Set start time
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	//The event loop
	SDL_Event e{};
	while (!quit)
	{
		// Poll next event from queue
		while (SDL_PollEvent(&e) != 0)
		{
			// Handle the polled event
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				this->ProcessKeyDownEvent(e.key);
				break;
			case SDL_KEYUP:
				this->ProcessKeyUpEvent(e.key);
				break;
			case SDL_MOUSEMOTION:
				e.motion.y = int(m_Window.height) - e.motion.y;
				this->ProcessMouseMotionEvent(e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				e.button.y = int(m_Window.height) - e.button.y;
				this->ProcessMouseDownEvent(e.button);
				break;
			case SDL_MOUSEBUTTONUP:
				e.button.y = int(m_Window.height) - e.button.y;
				this->ProcessMouseUpEvent(e.button);
				break;
			}
		}

		if (!quit)
		{
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

			// Calculate elapsed time
			float elapsedSeconds = std::chrono::duration<float>(t2 - t1).count();

			// Update current time
			t1 = t2;

			// Prevent jumps in time caused by break points
			elapsedSeconds = std::min(elapsedSeconds, m_MaxElapsedSeconds);

			// Call the BaseGame object 's Update function, using time in seconds (!)
			this->Update(elapsedSeconds);

			// Draw in the back buffer
			this->Draw();

			// Update screen: swap back and front buffer
			SDL_GL_SwapWindow(m_pWindow);
		}
	}
}

void Game::CleanupGameEngine()
{
	SDL_GL_DeleteContext(m_pContext);

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();

}

void Game::InitializeVariables()
{
	m_pPlayer = std::make_unique<Player>(ThreeBlade{200.f, m_Window.height / 2.f,0.f});
	Motor translator{ Motor::Translation(m_Window.height,TwoBlade{0,1,0,0,0,0}) };;
	m_Enemies.reserve(8);
	m_Enemies.push_back(ThreeBlade{ m_Window.width,m_Window.height / 2,0,1 });
	m_Enemies.push_back(ThreeBlade{ m_Window.width,m_Window.height ,0,1 });
	m_Enemies.push_back(ThreeBlade{ m_Window.width,0,0,1 });
}

void Game::CleanUpVariables()
{

}
void Game::PlayerBorderCheck()
{
	if (math::GetDistance(m_BottomBorder,m_pPlayer->GetPos()) <= 15.f)
	{
		m_KeysPressed.m_SIsPressed = false;
		//std::cout << math::GetDistance(m_BottomBorder,m_pPlayer->GetPos()) << std::endl;
	}
	if (math::GetDistance(m_TopBorder, m_pPlayer->GetPos()) <= 15.f)
	{
		m_KeysPressed.m_WIsPressed = false;
	}
	if (math::GetDistance(m_LeftBorder, m_pPlayer->GetPos()) <= 15.f)
	{
		m_KeysPressed.m_AIsPressed = false;
	}
	if (math::GetDistance(m_RightBorder, m_pPlayer->GetPos()) <= 15.f)
	{
		m_KeysPressed.m_DIsPressed = false;
	}

}
void Game::BulletBorderCheck()
{
	for (int i{}; i < m_Bullets.size(); ++i)
	{
		if (math::GetDistance(m_BottomBorder, m_Bullets[i].GetPos()) <= 5.f)
		{
			m_Bullets[i].ReflectBullet(m_BottomBorder);
		}
		if (math::GetDistance(m_BottomBorder, m_Bullets[i].GetPos()) >= m_Window.height - 5.f)
		{
			m_Bullets[i].ReflectBullet(m_BottomBorder);
		}
		if (math::GetDistance(m_LeftBorder, m_Bullets[i].GetPos()) <= 5.f)
		{
			m_Bullets[i].ReflectBullet( m_LeftBorder);
		}
		if (math::GetDistance(m_LeftBorder, m_Bullets[i].GetPos()) >= m_Window.width - 5.f)
		{
			m_Bullets[i].ReflectBullet(m_LeftBorder);
		}
	}
	for (PillarBullet& pillarBullet : m_PillarBullets)
	{
		if (math::GetDistance(m_BottomBorder, pillarBullet.GetLine()) <= 100.f)
		{
			//std::cout << "Distance: " << math::GetDistance(m_BottomBorder, pillarBullet.GetLine()) << std::endl;
			pillarBullet.ReflectBullet(m_BottomBorder);
		}
		if (math::GetDistance(m_BottomBorder, pillarBullet.GetLine()) >= m_Window.width - 100.f)
		{
			pillarBullet.ReflectBullet(m_BottomBorder);
		}
		if (math::GetDistance(m_LeftBorder, pillarBullet.GetLine()) <= 100.f)
		{
			pillarBullet.ReflectBullet(m_LeftBorder);
		}
		if (math::GetDistance(m_LeftBorder, pillarBullet.GetLine()) >= m_Window.height - 100.f)
		{
			pillarBullet.ReflectBullet(m_LeftBorder);
		}
	}
}
void Game::Update(float elapsedSec)
{
	//std::cout << "Framerate: " << 1.f / elapsedSec << std::endl;

	//Player Update
	PlayerBorderCheck();

	m_pPlayer->HandleInput(m_KeysPressed);
	m_pPlayer->UpdatePlayer(m_KeysPressed, elapsedSec);

	//Pillar Update
	ThreeBlade pos{ m_pPlayer->GetPos() };
	m_Pillar.Update(elapsedSec, m_Bullets, pos,m_PillarBullets);
	m_pPlayer->SetPos(pos);

	//Enemy Update
	for (auto it = m_Enemies.begin(); it != m_Enemies.end();)
	{
		it->Update(elapsedSec, m_pPlayer->GetPos());

		if (it->GetHealth() <= 0) {
			it = m_Enemies.erase(it);  //Delete en go next
		}
		else if (math::GetDistance(it->GetPos(), m_pPlayer->GetPos()) < 15.f)
		{
			m_pPlayer->LoseHealth(20);
			it = m_Enemies.erase(it);  //Delete en go next
		}
		else {
			++it;  // Increment if none deleted
		}
	}

	//substeps for better bullet updates
	for (int i{}; i < SUBSTEPS; ++i)
	{
		BulletBorderCheck();
		//Bullets
		for (auto it = m_Bullets.begin(); it != m_Bullets.end();) 
		{
			it->Update(elapsedSec / SUBSTEPS);

			if (it == m_Bullets.begin() && it->GetPos()[2] < 0.f) 
			{
				// if first bullet time is up pop_front
				m_Bullets.pop_front();
				it = m_Bullets.begin(); // Reset iterator to begin
			}
			else if (math::GetDistance(m_pPlayer->GetPos(), it->GetPos()) < 15.f and it->GetPos()[2] < 9.5f) //Player Collision after 0.5s of firing
			{
				m_pPlayer->LoseHealth(10);
				it = m_Bullets.erase(it);
			}
			else
			{
				bool bulletErased = false;

				// Collisions with enemy
				for (auto enemyIt = m_Enemies.begin(); enemyIt != m_Enemies.end(); ++enemyIt)
				{
					if (math::GetDistance(enemyIt->GetPos(), it->GetPos()) < 15.f)
					{
						enemyIt->LoseHealth(50);
						it = m_Bullets.erase(it); // Delete and go next
						bulletErased = true;
						break; // Go next bullet
					}
				}
				if (!bulletErased)
				{
					++it;
				}
			}
		}
		//Pillar Bullets
		for (auto it = m_PillarBullets.begin(); it != m_PillarBullets.end();)
		{
			it->Update(elapsedSec / SUBSTEPS,m_Bullets);

			if (it == m_PillarBullets.begin() && it->GetLifeTime() < 0.f)
			{
				// if first bullet time is up pop_front
				m_PillarBullets.pop_front();
				it = m_PillarBullets.begin(); // Reset iterator to begin
			}
			else if (math::GetDistance( it->GetLine(), m_pPlayer->GetPos()) < 15.f and it->GetLifeTime() < 9.5f) //Player Collision after 0.5s of firing
			{
				m_pPlayer->LoseHealth(10);
				it = m_PillarBullets.erase(it);
			}
			else
			{
				bool bulletErased = false;

				// Enemy Collision
				for (auto enemyIt = m_Enemies.begin(); enemyIt != m_Enemies.end(); ++enemyIt)
				{
					if (math::GetDistance(it->GetLine(), enemyIt->GetPos()) < 15.f)
					{
						enemyIt->LoseHealth(50);
						it = m_PillarBullets.erase(it); // Delete en go next
						bulletErased = true;
						break; // Go next bullet
					}
				}
				if (!bulletErased)
				{
					++it;
				}
			}
		}
	}
}

void Game::Draw() const
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_pPlayer->DrawPlayer();

	m_Pillar.Draw();

	for (const Enemy& enemy : m_Enemies)
	{
		enemy.Draw();
	}
	for (const Bullet& bullet : m_Bullets)
	{
		bullet.Draw();
	}
	for (const PillarBullet& pillarBullet : m_PillarBullets)
	{
		pillarBullet.Draw();
	}
}
