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


	//settings stuff
	std::map<std::string, int> supportedKeys;
	float gridSize;

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
	void initShop();

	void calculateMousePlayer();


public:

	Game();
	virtual ~Game();

	//Functions
	void endApplication();
	//updates
	void updateDt();
	void updatePlayer();
	void updateMap();
	void update();
	//render
	void renderPlayer();
	void renderWorld();
	void renderHUD();
	void renderShop();
	void render();
	
	const sf::RenderWindow& getWindow() const;
};

