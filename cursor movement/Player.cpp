#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->movingOn = false;
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
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
	this->currentFrame = sf::IntRect(0, 0, 100, 100);

	//Resize the sprite
	this->sprite.scale(1.5f,1.5f);
	
	this->sprite.setTextureRect(this->currentFrame);
	//center of screen?
	//this->sprite.setPosition(this->positionX, this->positionY);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}
void Player::initPhysics()
{
	this->movementSpeed = 0;
	this->positionX = 550;
	this->positionY = 400;	

}
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();

	this->sprite.setPosition(this->positionX, this->positionY);

}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
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

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::move(const float dir_x, const float dir_y)
{
	this->dir_x = dir_x;
	this->dir_y = dir_y;
	this->movingOn = true;

}

void Player::updatePhysics()
{
	if (movingOn) {
		this->movementSpeed = 1.0f;
	}
	else this->movementSpeed = 0;

	if (this->dir_y > getPosition().y) {
		this->sprite.move(0,movementSpeed);
	}
	else if (this->dir_y < getPosition().y) {
		this->sprite.move(0, -movementSpeed);
	}
	if (this->dir_x > getPosition().x) {
		this->sprite.move(movementSpeed,0);
	}
	else if (this->dir_x < getPosition().x) {
		this->sprite.move(-movementSpeed,0);
	}
	
	if (this->dir_x == getPosition().x && this->dir_y == getPosition().y) this->movingOn = false;
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
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left > 600.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(1.5f, 1.5f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left > 600.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
		}

		this->sprite.setScale(-1.5f, 1.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.5f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWN)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left > 600.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_UP)
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

void Player::update()
{

	this->updateAnimations();
	this->updatePhysics();
	
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	//CIRCLE FOR FIXING POSITION
	//sf::CircleShape circ;
	//circ.setFillColor(sf::Color::Red);
	//circ.setRadius(2.f);
	//circ.setPosition(this->sprite.getPosition());
	//target.draw(circ);
}
