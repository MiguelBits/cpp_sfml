#include "stdafx.h"
#include "Player.h"


/// <summary>
/// /////////////////////////////////////////				INIT
/// </summary>
void Player::initVariables()
{
	this->movingOn = false;
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->pixelSize.x = 100;
	this->pixelSize.y = 100;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/riven.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture Sprite
	this->sprite.setTexture(this->textureSheet);

	//set animation frame from texture
	this->currentFrame = sf::IntRect(0, 0, this->pixelSize.x, this->pixelSize.y);

	//Resize the sprite
	this->sprite.scale(1.5f,1.5f);
	
	this->sprite.setTextureRect(this->currentFrame);
	
}

void Player::initAnimations()
{
	this->BAnimation = false;

	this->animationTimer.restart();
	this->animationSwitch = true;
}
void Player::initPhysics()
{
	this->movementSpeed = 0;
	this->positionX = 550;
	this->positionY = 400;	

}
Player::Player(int screenW, int screenH)
{
	this->screenW = screenW;
	this->screenH = screenH;

	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
	this->initAbilities();

	//spawn point
	this->sprite.setPosition(this->pixelSize.x+600, this->screenH - this->pixelSize.y - 500);

}
void Player ::initAbilities() {
	this->Qability.key = PLAYER_ANIMATION_STATES::Q;
	this->Wability.key = PLAYER_ANIMATION_STATES::W;
	this->Eability.key = PLAYER_ANIMATION_STATES::E;
	this->Rability.key = PLAYER_ANIMATION_STATES::R;

	this->Qability.isActive = false;
	this->Wability.isActive = false;
	this->Eability.isActive = false;
	this->Rability.isActive = false;

	this->Qability.isAvailable = true;
	this->Wability.isAvailable = true;
	this->Eability.isAvailable = true;
	this->Rability.isAvailable = true;

	this->Qability.SecondsSinceTimerStarted = 0;
	this->Wability.SecondsSinceTimerStarted = 0;
	this->Eability.SecondsSinceTimerStarted = 0;
	this->Rability.SecondsSinceTimerStarted = 0;

	this->Qability.maxSecondsCooldown = 6.0f;
	this->Wability.maxSecondsCooldown = 6.0f;
	this->Eability.maxSecondsCooldown = 6.0f;
	this->Rability.maxSecondsCooldown = 12.0f;

}
Player::~Player()
{

}

/// <summary>
/// /////////////////////////////////////////				SET GET
/// </summary>
short Player::getAnimState()
{
	return this->animState;
}

void Player::setAnimationB(bool input)
{
	this->BAnimation = input;
}


const bool Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;
	
	return anim_switch;
}


const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Player::getCenter() const
{
	return this->sprite.getPosition();
}


void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::move(const float dir_x, const float dir_y)
{
	this->dir_x = dir_x;
	this->dir_y = dir_y;
	//in update physics
	this->movingOn = true;

}

void Player::useQability(sf::Vector2f mouseCoord)
{
	if (this->Qability.isAvailable) {
		this->Qability.isActive = true;
		this->Qability.direction = mouseCoord;
		this->Qability.isAvailable = false;
	}
	
}
void Player::useWability()
{
	this->Wability.isActive = true;
	this->Wability.isAvailable = false;
}
void Player::useEability(sf::Vector2f mouseCoord)
{
	this->Eability.isActive = true;
	this->Eability.direction = mouseCoord;
	this->Eability.isAvailable = false;
}
void Player::useRability(sf::Vector2f mouseCoord)
{
	this->Rability.isActive = true;
	this->Rability.direction = mouseCoord;
	this->Rability.isAvailable = false;
}

/// <summary>
/// /////////////////////////////////////////				UPDATE
/// </summary>
void Player::updatePhysics()
{
	//origin to center of object, half pixel size
	this->sprite.setOrigin(this->pixelSize.x/2, this->pixelSize.y/2);

	//movement physics
	if (this->dir_x == getPosition().x && this->dir_y == getPosition().y) this->movingOn = false;

	if (movingOn) {
		this->movementSpeed = 1.0f;
	}
	else this->movementSpeed = 0;

	if (this->dir_y > getPosition().y) { //up
		this->sprite.move(0,movementSpeed);
	}
	else if (this->dir_y < getPosition().y) { //down
		this->sprite.move(0, -movementSpeed);
	}
	if (this->dir_x > getPosition().x) {//right
		this->sprite.move(movementSpeed,0);
	}
	else if (this->dir_x < getPosition().x) {//left
		this->sprite.move(-movementSpeed,0);
	}
	//map collision
	if (this->getPosition().y + this->pixelSize.y >= this->screenH - 280 && 
		this->getPosition().x + this->pixelSize.x / 2 >= this->screenW - 280) {
		this->setPosition(this->getPosition().x, this->screenH - 280 - this->pixelSize.y);
	}
}


//Where you specify the frame sizes for the animation transition
void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left > 600.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	//MOVEMENT
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			if (BAnimation) {
				this->currentFrame.top = 200.f;
				this->currentFrame.left = 700.f;
			}
			else {
				this->currentFrame.top = 200.f;
				this->currentFrame.left += 100.f;
				if (this->currentFrame.left > 600.f)
					this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->lastAnimState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			if (BAnimation) {
				this->currentFrame.top = 300.f;
				this->currentFrame.left = 700.f;
			}
			else {
				this->currentFrame.top = 300.f;
				this->currentFrame.left += 100.f;
				if (this->currentFrame.left > 600.f)
					this->currentFrame.left = 0;

			}
			
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

			
		}
		this->lastAnimState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWN)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			if (BAnimation) {
				this->currentFrame.top = 0.f;
				this->currentFrame.left = 700.f;
			}
			else {
				this->currentFrame.top = 0.f;
				this->currentFrame.left += 100.f;
				if (this->currentFrame.left > 600.f)
					this->currentFrame.left = 0;
			}
			

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->lastAnimState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_UP)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			if (BAnimation) {
				this->currentFrame.top = 100.f;
				this->currentFrame.left = 700.f;
			}
			else {
				this->currentFrame.top = 100.f;
				this->currentFrame.left += 100.f;
				if (this->currentFrame.left > 600.f)
					this->currentFrame.left = 0;
			}
			
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->lastAnimState = PLAYER_ANIMATION_STATES::MOVING_UP;
	}
	//ABILITIES
	else if (this->animState == PLAYER_ANIMATION_STATES::Q)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 400.f;
			this->currentFrame.left += 100.f;
	
			if (this->currentFrame.left > 600.f) {
				this->currentFrame.left = 0;

				this->Qability.isActive = false;
				//return to last animation displayed
				this->animState = this->lastAnimState;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::W)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 100.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left > 600.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::E)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 100.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left > 600.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::R)
	{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
	{
		this->currentFrame.top = 100.f;
		this->currentFrame.left += 100.f;
		if (this->currentFrame.left > 600.f)
			this->currentFrame.left = 0;

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
	}
	else
		this->animationTimer.restart();
}

void Player::updateMovement(int side)
{
	if (side == 4 || side == 5) { //4,5 //LEFT
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	if (side == 3 || side == 2) { //3,4 // DOWN
		this->animState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
		//cout << "DOWN";
	}

	if (side == 1 || side == 8) { //1,8 //RIGHT
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		//cout << "RIGHT";
	}
	if (side == 6 || side == 7) { //6,7 // UP
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UP;
		//cout << "UP";
	}
}

void Player::updateAbilities()
{
	//set animations for abilities, start cooldown
	std::cout << "clock is \n" << this->Qability.SecondsSinceTimerStarted;
	//Q was pressed
	if (this->Qability.isActive) {
		this->animState = this->Qability.key;
		this->Qability.cooldownTimer.restart();
	}
	//Q is on cooldown
	else if(!this->Qability.isAvailable){
		this->Qability.SecondsSinceTimerStarted = this->Qability.cooldownTimer.getElapsedTime().asSeconds();
		if (this->Qability.maxSecondsCooldown <= this->Qability.SecondsSinceTimerStarted) {
			this->Qability.isAvailable = true;
			this->Qability.SecondsSinceTimerStarted = 0;
		}
	}

	if (this->Wability.isActive) {
		this->Wability.cooldownTimer.restart();
		this->animState = this->Wability.key;
	}
	if (this->Eability.isActive) {
		this->Eability.cooldownTimer.restart();
		this->animState = this->Eability.key;
	}
	if (this->Rability.isActive) {
		this->Rability.cooldownTimer.restart();
		this->animState = this->Rability.key;
	}
}

void Player::update()
{

	this->updateAnimations();
	this->updatePhysics();
	this->updateAbilities();
}

/// <summary>
/// /////////////////////////////////////////				RENDER
/// </summary>
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	
	//CIRCLE FOR FIXING POSITION
	/*sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(150);
	circ.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y-150);
	target.draw(circ);*/
}
