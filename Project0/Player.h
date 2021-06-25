#pragma once

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	
	void initVariables();
	void initTexture();
	void initSprite();


public:
	Player();
	virtual ~Player();

	void update();
	void render(sf::RenderTarget& target);
};

