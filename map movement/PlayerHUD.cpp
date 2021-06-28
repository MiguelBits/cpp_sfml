#include "stdafx.h"
#include "PlayerHUD.h"


void PlayerHUD::initFont()
{
	this->font.loadFromFile("Fonts\open-sans\OpenSans-Regular.ttf");
}

void PlayerHUD::initHUD(int screenW, int screenH)
{
	//HUD SIZE
	float width = 800.0f;
	float height = 80.0f;

	//Shop Rectangle
	this->shop.setSize(sf::Vector2f(width, height));
	this->shop.setFillColor(sf::Color(sf::Color::Red));
	this->shop.setPosition(screenW/10, screenH/8);
	this->shop.scale(2,8);

	//Black HUD Bar
	this->HUD.setSize(sf::Vector2f(width,height));
	this->HUD.setFillColor(sf::Color(50,50,50,200));
	this->HUD.setPosition(this->screenW/3, this->screenH - 130);

	//HP BAR
	//red bar
	this->hpBarInner.setSize(sf::Vector2f(width - 100, height / 4));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->HUD.getPosition().x + 50, this->HUD.getPosition().y + 50);
	//white bar
	this->hpBarBack.setSize(sf::Vector2f(width-100, height / 4));
	this->hpBarBack.setFillColor(sf::Color(sf::Color::White));
	this->hpBarBack.setPosition(this->HUD.getPosition().x + 50, this->HUD.getPosition().y + 50);
	

	//Skills bar
	this->skillsBar.setSize(sf::Vector2f(width - 100, height/1.25f));
	this->skillsBar.setFillColor(sf::Color(sf::Color::Green));
	this->skillsBar.setPosition(this->HUD.getPosition().x+50, this->HUD.getPosition().y - 30);

	//Map bar
	int mapScale = 250;
	this->mapBar.setSize(sf::Vector2f(mapScale,mapScale));
	this->mapBar.setFillColor(sf::Color(sf::Color::Green));
	this->mapBar.setPosition(this->screenW-mapScale-50, this->screenH-mapScale-50);
}

PlayerHUD::PlayerHUD(Player* player, int screenW, int screenH)
{
	this->screenW = screenW;
	this->screenH = screenH;

	this->player = player;
	this->initFont();
	this->initHUD(this->screenW, this->screenH);
}

PlayerHUD::~PlayerHUD()
{
}

void PlayerHUD::updateHPBar()
{
}

void PlayerHUD::update(const float& dt)
{
}

void PlayerHUD::renderShop(sf::RenderTarget& target)
{
	target.draw(this->shop);
}

void PlayerHUD::renderHUD(sf::RenderTarget& target)
{
	//order to draw matters
	target.draw(this->HUD);
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->skillsBar);
	target.draw(this->mapBar);
}

void PlayerHUD::render(sf::RenderTarget& target, bool shopOpen)
{
	this->renderHUD(target);
	if (shopOpen) this->renderShop(target);
}
