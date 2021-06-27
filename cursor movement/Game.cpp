#include"stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(this->screenW, this->screenH), "Not a Game!", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Player(this->screenW, this->screenH);
}
void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/rift.jpg"))
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

	//cateto oposto
	float CO = localPosition.x - this->player->getPosition().x;
	//cateto adjacente
	float CA = localPosition.y - this->player->getPosition().y;

	//std::cout << "CO : " << CO << "\n";
	//std::cout << "CA : " << CA << "\n";

	float coca = atan(CO / CA) ;
	float side = coca * 100;


	//h**2 = ca**2 + co**2;
	float hipotenusa = sqrt(pow(CA, 2) + pow(CO, 2));

	float sin = CO / hipotenusa;
	float cos = CA / hipotenusa;

	//std::cout << "cos : " << cos << "\n";
	//std::cout << "sin : " << sin << "\n";
	
	//std::cout << "ANGULO COCA: " << side << "\n";
	if (120 <= side && side <= 160 && CA > 0) {
		this->player->updateMovement(1);
		//right positive
		//this->player->move(cos,sin);
	}
	if (0.000001 <= side && side <= 120 && CA > 0) {
		this->player->updateMovement(2);
		//down positive
		//this->player->move(cos, sin);

	}
	if (-0.000001 >= side && side >= -120 && CA > 0) {
		this->player->updateMovement(3);
		//down negative
		//this->player->move(-cos, -sin);
	}
	if (-60 >= side && side >= -160 && CA > 0) {
		this->player->updateMovement(4);
		//left negative
		//this->player->move(-cos, -sin);
		
	}
	if (120 <= side && side <= 160 && CA < 0) {
		this->player->updateMovement(5);
		//left positive
		//this->player->move(-1.0f,0);
		
	}
	if (0.000001 <= side && side <= 120 && CA < 0) {
		this->player->updateMovement(6);
		//up positive
		//this->player->move(cos, sin);
	}
	if (-0.000001 >= side && side >= -120 && CA < 0) {
		this->player->updateMovement(7);
		//up negative
		//this->player->move(-cos, -sin);

	}
	if (-120 >= side && side >= -160 && CA < 0) {
		this->player->updateMovement(8);
		//right negative
		//this->player->move(-cos, -sin);
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
	//switch animation with mouse movement
	calculateMousePlayer();

	if (this->ev.type == sf::Event::MouseButtonPressed)
	{

		if (this->ev.mouseButton.button == sf::Mouse::Right)
		{
				sf::Vector2i localPosition = sf::Mouse::getPosition(this->window);
				sf::Vector2f mouseCoord = window.mapPixelToCoords(localPosition);
				this->player->move(mouseCoord.x, mouseCoord.y);
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
