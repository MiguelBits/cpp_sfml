#include"stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(this->screenW, this->screenH), "Not a Game!", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}
void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
	this->worldBackground.scale(0.8f,0.8f);
}
void Game::initVariables()
{
	this->screenW = 1200;
	this->screenH = 800;
}


void Game::calculateMousePlayer() {
	//Mouse relative to window position
	sf::Vector2i localPosition = sf::Mouse::getPosition(this->window);
	//std::cout << "mouse X is at: " << localPosition.x << "\n";
	//std::cout << "mouse Y is at: " << localPosition.y << "\n";

	float CO = localPosition.x - this->player->positionX;
	float CA = localPosition.y - this->player->positionY;

	//std::cout << "CO : " << CO << "\n";
	//std::cout << "CA : " << CA << "\n";

	float coca = CO / CA;
	float side = atan(coca) * 100;

	//std::cout << "ANGULO COCA: " << side << "\n";
	if (120 <= side && side <= 160 && CA > 0) {
		this->player->switchAnimationSide(1);
	}
	else if (0.000001 <= side && side <= 120 && CA > 0) {
		this->player->switchAnimationSide(2);
	}
	else if (-0.000001 >= side && side >= -120 && CA > 0) {
		this->player->switchAnimationSide(3);
	}
	else if (-120 >= side && side >= -160 && CA > 0) {
		this->player->switchAnimationSide(4);
	}
	else if (120 <= side && side <= 160 && CA < 0) {
		this->player->switchAnimationSide(5);
	}
	else if (0.000001 <= side && side <= 120 && CA < 0) {
		this->player->switchAnimationSide(6);
	}
	else if (-0.000001 >= side && side >= -120 && CA < 0) {
		this->player->switchAnimationSide(7);
	}
	else if (-120 >= side && side >= -160 && CA < 0) {
		this->player->switchAnimationSide(8);
	}
}
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	//Movement Mouse
	if (this->ev.type == sf::Event::MouseMoved)
	{
		calculateMousePlayer();
	}
	if (this->ev.type == sf::Event::MouseButtonPressed)
	{
		if (this->ev.mouseButton.button == sf::Mouse::Right)
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(this->window);
			this->player->move(localPosition.x, localPosition.y);
		}
	}
	this->player->update();
}


void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
		
	}

	this->updatePlayer();

}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();
	//Draw world
	this->renderWorld();

	//Render game
	this->renderPlayer();

	this->window.display();
}
void Game::renderWorld()
{
	this->window.draw(this->worldBackground);
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
