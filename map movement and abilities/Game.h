#pragma once
#include"Player.h"
#include "PlayerHUD.h"

class Game
{
private:

	//Window
	sf::RenderWindow window;
	sf::RenderWindow* windowPointer;
	sf::Event ev;

	//delta time, for framerates
	sf::Clock dtClock;
	float dt;

	sf::Clock B_Clock;
	// Record elapsed time of
	float B_SecondsSinceRecallStarted;
	bool B_clockStarted;

	//screen
	int screenH;
	int screenW;

	//for the shop event
	bool shopOpen;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Player
	Player* player;
	PlayerHUD* HUD;

	//inits
	void initWindow();
	void initPlayer();
	void initHUD();
	void initVariables();
	void initWorld();
	void resetWorld();
	
	//player interaction functions
	void calculateMousePlayer();
	void animationSkillInput(sf::Event ev);


public:

	Game();
	virtual ~Game();

	//Functions
	
	//updates
	void updateDt();
	void updatePlayer();
	void updateMap();
	void update();
	//render
	void renderPlayer();
	void renderWorld();
	void renderHUD();
	void render();
	
	const sf::RenderWindow& getWindow() const;
};

