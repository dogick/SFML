#include "stdafx.h"
#include <SFML/Graphics.hpp>

static const int MAX_COUNT_BLOCK = 6;
static const float SPEED = 0.07f;
static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
static const int WINDOW_HEIGHT = 700;
static const int WINDOW_WIDTH = 700;

enum class Direction
{
	RIGHT,
	DIAGONALLY,

};

class ÑRectangle
{
public:
	ÑRectangle(sf::Vector2f const& position, sf::Vector2f const& size, sf::Vector2f const& scale, Direction const& direction);
	void Update(float elapsedTime);
	void Draw(sf::RenderWindow & window);
private:
	sf::RectangleShape m_rectangle;
	Direction m_direction;
	void AnimateRight(float elapsedTime);
	void AnimateDiagonally();
};

ÑRectangle::ÑRectangle(sf::Vector2f const& position, sf::Vector2f const& size, sf::Vector2f const& scale, Direction const& direction)
{
	m_rectangle.setPosition(position);
	m_rectangle.setSize(size);
	m_rectangle.setOrigin(size.x / 2, size.y / 2);
	m_rectangle.setScale(scale);
	m_rectangle.setFillColor(sf::Color(102, 0, 102));
	m_direction = direction;
}

void ÑRectangle::AnimateRight(float elapsedTime)
{
	sf::Vector2f position = m_rectangle.getPosition();
	sf::Vector2f size = m_rectangle.getSize();

	if (position.x + size.x / 2 <= WINDOW_WIDTH)
	{
		//m_rectangle.setRotation(m_rectangle.getRotation() + 0.1);
		m_rectangle.move(SPEED * elapsedTime, 0);
	}
}

void ÑRectangle::AnimateDiagonally()
{

}

void ÑRectangle::Update(float elapsedTime)
{
	switch (m_direction)
	{
	case Direction::RIGHT:
		AnimateRight(elapsedTime);
		break;
	case Direction::DIAGONALLY:
		break;
	default:
		break;
	}
}

void ÑRectangle::Draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
}

void Render(sf::RenderWindow & window, std::vector<ÑRectangle*> & rectangles, float elapsedTime)
{
	window.clear(sf::Color::White);
	for (auto rectangle : rectangles)
	{
		rectangle->Update(elapsedTime);
		rectangle->Draw(window);
	}
	window.display();
}

void HandleEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML!");
	std::vector<ÑRectangle*> rectangles;
	float step = 0;
	for (int i = 0; i != MAX_COUNT_BLOCK; ++i)
	{
		step += 50;
		rectangles.push_back(new ÑRectangle(sf::Vector2f(0, 100 + step) , sf::Vector2f(30, 30), sf::Vector2f(1, 1), Direction::RIGHT));
	}

	sf::Clock clock;
	while (window.isOpen())
	{
		float elapsedTime = clock.getElapsedTime().asMicroseconds(); //äàòü ïðîøåäøåå âðåìÿ â ìèêðîñåêóíäàõ
		clock.restart(); //ïåðåçàãðóæàåò âðåìÿ
		elapsedTime = elapsedTime / 800; //ñêîðîñòü èãðû
		HandleEvents(window);
		Render(window, rectangles, elapsedTime);
			
	}

	return 0;
}