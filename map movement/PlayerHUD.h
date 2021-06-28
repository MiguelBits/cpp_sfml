#pragma once
#include "Player.h";
class Player;
class sf::RectangleShape;
class PlayerHUD
{
private:
	Player* player;
	int screenW;
	int screenH;

	//health bar
	sf::Font font;
	sf::RectangleShape HUD;
	sf::RectangleShape shop;
	sf::RectangleShape hpBarInner;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape skillsBar;
	sf::RectangleShape mapBar;

	void initFont();
	void initHUD(int screenW, int screenH);

public:
	PlayerHUD(Player* player, int screenW, int screenH);
	virtual ~PlayerHUD();

	//Functions
	void updateHPBar();
	void update(const float& dt);
	void renderShop(sf::RenderTarget& target);
	void renderHUD(sf::RenderTarget& target);
	void render(sf::RenderTarget& target,bool shopOpen);

};
