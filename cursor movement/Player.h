#pragma once
enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Event ev;
	sf::Vector2f pixelSize;

	//Physics
	sf::Vector2f velocity;
	int screenW;
	int screenH;

	
	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

public:
	Player(int screenW, int screenH);
	virtual ~Player();

	//Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;

	const sf::FloatRect getGlobalBounds() const;

	//Variables
	float movementSpeed;
	float positionX;
	float positionY;
	float dir_x;
	float dir_y;
	bool movingOn;

	//Functions
	void move(const float dirX, const float dirY);
	void resetAnimationTimer();
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void updatePhysics();
	void updateAnimations();
	void updateMovement(int side);
	void update();
	void render(sf::RenderTarget& target);
};

