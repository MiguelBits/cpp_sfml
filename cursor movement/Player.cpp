#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->positionX = 550;
	this->positionY = 300;
	this->movementSpeed = 10;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/akali.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture Sprite
	this->sprite.setTexture(this->textureSheet);
	//Resize the sprite
	this->sprite.scale(0.3f,0.3f);
	//center of screen?
	this->sprite.setPosition(this->positionX, this->positionY);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

}

Player::~Player()
{

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

void Player::switchAnimationSide(int side)
{
	//std::cout << "tan: " << side << "\n";
	
}

void Player::update()
{
	this->sprite.setPosition(this->positionX, this->positionY);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
