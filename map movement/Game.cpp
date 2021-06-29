#include"stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(this->screenW, this->screenH), "Not a Game!", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(144);
	this->window.setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player(this->screenW, this->screenH);
}
void Game::initHUD()
{
	this->shopOpen = false;
	this->HUD = new PlayerHUD(this->player, this->screenW, this->screenH);
}
void Game::initWorld()
{
	this->B_clockStarted = false;

	if (!this->worldBackgroundTex.loadFromFile("Textures/teste.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->resetWorld();
	this->worldBackground.setTexture(this->worldBackgroundTex);

}

void Game::resetWorld()
{
	this->worldBackground.setPosition(0, -1000);
}

void Game::initVariables()
{
	this->screenW = 1920;
	this->screenH = 1080;
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
	this->initHUD();

}

Game::~Game()
{
	delete this->player;

}


void Game::updateDt()
{
	//updates the dt variable w the time it takes to update and render one frame;
	this->dt = this->dtClock.restart().asSeconds();

	//cout << "Delta time is: " << this->dt;
}

void Game::updatePlayer()
{
	//switch animation with only the mouse movement
	calculateMousePlayer();

	if (this->ev.type == sf::Event::MouseButtonPressed)
	{

		if (this->ev.mouseButton.button == sf::Mouse::Right && !this->shopOpen)
		{
				sf::Vector2i localPosition = sf::Mouse::getPosition(this->window);
				sf::Vector2f mouseCoord = window.mapPixelToCoords(localPosition);
				this->player->move(mouseCoord.x, mouseCoord.y);
		}
	}

	this->player->update();
}

void Game::updateMap()
{
	if (this->player->movingOn)
	{
		if (this->player->dir_y > this->player->getPosition().y) { //up map goes down
			this->worldBackground.move(0, -this->player->movementSpeed / 2);
		}
		else if (this->player->dir_y < this->player->getPosition().y) { //down map goes up
			this->worldBackground.move(0, this->player->movementSpeed / 2);
		}
		if (this->player->dir_x > this->player->getPosition().x) {//right map goes left
			this->worldBackground.move(-this->player->movementSpeed / 2, 0);
		}
		else if (this->player->dir_x < this->player->getPosition().x) {//left map goes right
			this->worldBackground.move(this->player->movementSpeed / 2, 0);
			
		}
	}
	//Collision with window and map movement and player recenter
	//left collision
	if (this->player->getPosition().x - this->player->pixelSize.x <= 0.f) {
		this->player->setPosition(this->screenW/2, this->player->getPosition().y);
		this->worldBackground.setPosition(this->worldBackground.getPosition().x+ this->screenW / 2, this->worldBackground.getPosition().y);
		this->player->movingOn = false;
	}
	//top collision
	if (this->player->getPosition().y - this->player->pixelSize.y <= 0.f) {
		this->player->setPosition(this->player->getPosition().x, 300);
		this->worldBackground.setPosition(this->worldBackground.getPosition().x, this->worldBackground.getPosition().y + 300);
		this->player->movingOn = false;
	}
	//bottom collision
	if (this->player->getPosition().y + this->player->pixelSize.y >= this->screenH - 150) {
		this->player->setPosition(this->player->getPosition().x, this->screenH/2);
		this->worldBackground.setPosition(this->worldBackground.getPosition().x, this->worldBackground.getPosition().y - 300);
		this->player->movingOn = false;
	}
	//right collision
	if (this->player->getPosition().x + this->player->pixelSize.x >= this->screenW) {
		this->player->setPosition(this->screenW / 2, this->player->getPosition().y);
		this->worldBackground.setPosition(this->worldBackground.getPosition().x - 900, this->worldBackground.getPosition().y);
		this->player->movingOn = false;
	}
		
}


void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		//Close with escape button
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();

		//Open shop with P button, close if shop is open
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::P) {
			if (this->shopOpen) this->shopOpen = false;
			else this->shopOpen = true;
		}

		//B for recall to base button
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::B) {
			//std::cout << "\nPlayer is at X: " << this->player->getPosition().x;
			//std::cout << "Player is at Y: " << this->player->getPosition().y;
			this->player->movingOn = false;

			//start clock
			this->B_Clock.restart();
			this->B_clockStarted = true;
			this->player->setAnimationRecall();
			
		}
	}

	//std::cout << "Clock \n" << this->B_SecondsSinceRecallStarted;
	

	//and if recall animation has not stopped
	if (this->B_clockStarted) {
		//get current elapsed time of frame
		this->B_SecondsSinceRecallStarted = this->B_Clock.getElapsedTime().asSeconds();
		if (this->player->movingOn) this->B_clockStarted = false;
	}
	//if 8 seconds have passed since recall started
	if (this->B_SecondsSinceRecallStarted >= 8 && this->B_SecondsSinceRecallStarted <= 10) {
		this->resetWorld();
		this->player->setPosition(700, 480);
		this->B_clockStarted = false;
		this->B_SecondsSinceRecallStarted = 0;
	}

	this->updatePlayer();
	this->updateMap();

}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderWorld()
{
	this->window.draw(this->worldBackground);
}

void Game::renderHUD()
{
	this->HUD->render(this->window,this->shopOpen);
}


void Game::render()
{

	this->window.clear();

	//Draw world
	this->renderWorld();

	//render player
	this->renderPlayer();

	//render HUD
	this->renderHUD();
	
	this->window.display();
}


const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}
