#pragma once
enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT };
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

public:
	Player();
	virtual ~Player();

	//Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;

	//Variables
	float movementSpeed;
	float positionX;
	float positionY;

	//Functions
	void move(const float dirX, const float dirY);
	void resetAnimationTimer();
	void switchAnimationSide(int side);
	void updateAnimations();
	void updateMovement();
	void update();
	void render(sf::RenderTarget& target);
};

