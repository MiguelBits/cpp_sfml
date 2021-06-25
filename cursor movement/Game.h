#pragma once
#include"Player.h"

class Game
{
private:
	//Window
	sf::RenderWindow window;
	sf::Event ev;

	//screen
	int screenH;
	int screenW;
	
	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	Player* player;

	void initWindow();
	void initPlayer();
	void initVariables();
	void initWorld();

	void calculateMousePlayer();

public:

	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();
	void renderWorld();
	const sf::RenderWindow& getWindow() const;
};

