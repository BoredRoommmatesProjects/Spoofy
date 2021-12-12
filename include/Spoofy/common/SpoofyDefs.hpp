#ifndef _SPOOFY_SPOOFYDEFS_HPP_
#define _SPOOFY_SPOOFYDEFS_HPP_

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "common/GameDefs.hpp"

#define REFRESH_RATE 16 // Refresh rate of the screen in main while loop
#define FPS 60

#define PLAYER_SPEED          4
#define PLAYER_BULLET_SPEED   16
#define ALIEN_BULLET_SPEED    5

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

struct App {
	//SDL_Renderer* renderer;
	sf::RenderTexture* textureRenderer;
	sf::RenderWindow* windowRenderer;
	int keyboard[sf::Keyboard::Key::KeyCount];
};

struct Entity {
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	int side;
	sf::Texture* texture;
	Entity* next;
};

#endif // !_SPOOFY_SPOOFYDEFS_HPP_