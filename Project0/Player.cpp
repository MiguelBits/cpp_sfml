#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	//this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
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


void Player::update()
{
	
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
