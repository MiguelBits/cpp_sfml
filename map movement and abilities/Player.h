#ifndef _PLAYER_H_
#define _PLAYER_H_
enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN, Q, W, E, R};
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Event ev;

	//Abilities / Skills
	//doing animation?
	bool BAnimation;

	//Physics
	int screenW;
	int screenH;

	
	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();
	void initAbilities();


	//Animation
	sf::IntRect currentFrame;
	bool animationSwitch;
	short animState;
	short lastAnimState;
	


public:
	struct Ability {
		bool isActive;
		PLAYER_ANIMATION_STATES key;
		//cooldown
		sf::Clock cooldownTimer;
		float SecondsSinceTimerStarted;
		float maxSecondsCooldown;
		bool isAvailable;
		//direction of mouse
		sf::Vector2f direction;
	};

	Ability Qability;
	Ability Wability;
	Ability Eability;
	Ability Rability;
	//Animation
	short getAnimState();
	void setAnimationB(bool input);
	void ClickToUseAbility();
	

	Player(int screenW, int screenH);
	virtual ~Player();

	//Accessors
	const bool getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getCenter() const;
	const sf::FloatRect getGlobalBounds() const;

	//Variables
	sf::Vector2f pixelSize;
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

	//set abilites
	void useQability(sf::Vector2f mouseCoord);
	void useWability();
	void useEability(sf::Vector2f mouseCoord);
	void useRability(sf::Vector2f mouseCoord);

	void updatePhysics();
	void updateAnimations();
	void updateMovement(int side);
	void updateAbilities();
	void update();

	void render(sf::RenderTarget& target);
};

#endif