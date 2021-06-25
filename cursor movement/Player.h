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
	//Variables
	float movementSpeed;
	float positionX;
	float positionY;

	//Functions
	void move(const float dirX, const float dirY);
	void switchAnimationSide(int side);
	void update();
	void render(sf::RenderTarget& target);
};

