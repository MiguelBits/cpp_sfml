#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->positionX = 550;
	this->positionY = 300;
	this->movementSpeed = 5;
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/fita.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture Sprite
	this->sprite.setTexture(this->textureSheet);

	//set animation frame from texture
	this->currentFrame = sf::IntRect(0, 0, 35, 100);

	//Resize the sprite
	this->sprite.scale(2.0f,2.0f);
	
	//center of screen?
	this->sprite.setPosition(this->positionX, this->positionY);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();

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


void Player::move(const float dirX, const float dirY)
{
	//cout << "\nmouseX is at " << dirX;
	//cout << "\nmouseY is at " << dirY;
	//cout << "\nplayerX is at " << this->positionX;
	//cout << "\nplayerY is at " << this->positionY;

	if (dirY > this->positionY) {
		this->positionY += this->movementSpeed;
	}
	else if (dirY < this->positionY) {
		this->positionY -= this->movementSpeed;
	}
	if (dirX > this->positionX) {
		this->positionX += this->movementSpeed;
	}
	else if (dirX < this->positionX) {
		this->positionX -= this->movementSpeed;
	}
	
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}


void Player::switchAnimationSide(int side)
{	
	if (side == 4 || side == 5 ) { //4,5 //LEFT
		//this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		cout << "LEFT";
	}
	else if (side == 3 || side == 4) { //3,4 // DOWN
		this->animState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
		cout << "DOWN";
	}
	
	if (side == 1 || side == 8) { //1,8 //RIGHT
		//this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		cout << "RIGHT";
	}
	else if (side == 6 || side == 7) { //6,7 // UP
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UP;
		cout << "UP";
	}
	
	

	
	
	
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 160.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(2.f, 2.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(-2.f, 2.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWN)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 190.f;
			this->currentFrame.left += 50.f;
			if (this->currentFrame.left > 80.f)
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
			this->currentFrame.left += 50.f;
			if (this->currentFrame.left > 80.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
}

void Player::update()
{
	this->updateAnimations();
	this->sprite.setPosition(this->positionX, this->positionY);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
