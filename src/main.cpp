#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <stdio.h>
#include "util.h"

int t=0;
sf::Vector2f mousePos;
sf::Vector2i realMousePos;
float mouseSmoothness=3;
float mouseSize=36;

const char* str(int    a) {return std::to_string(a).c_str();}
const char* str(float  a) {return std::to_string(a).c_str();}
const char* str(double a) {return std::to_string(a).c_str();}

float roundNth(float x,float n) {
    return std::roundf(x*n)/n;
}


int main() {
    printf("\n\n\n");
    #pragma region init
    #pragma region clock
    sf::Clock my_clock;

    sf::Time startTime=sf::milliseconds(0);
    sf::Time firstFrameTime=sf::milliseconds(0);
    sf::Time lastFrameTime=sf::milliseconds(0);
    sf::Time currentTime=sf::milliseconds(0);
    sf::Time deltaTime=sf::milliseconds(0);
    #pragma endregion

	startTime=my_clock.getElapsedTime();
    #pragma region window init

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Desktop!",sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    #pragma endregion
    #pragma region resources

    sf::Font sysfont;
    if (!sysfont.loadFromFile("resources/font.ttf")) {
        printf("Error loading system font\n");
    }

    sf::Texture wallpaperTex;
    if (!wallpaperTex.loadFromFile("resources/wallpaper.png")) {
        printf("Error loading png wallpaper\n");
        // if (!wallpaperTex.loadFromFile("resources/wallpaper.jpeg")) {
        //     printf("Error loading jpeg wallpaper\n");
        // } else {
        //     printf("Loaded wallpaper successfully!\n");
        // }
    } else {
        printf("Loaded wallpaper successfully!\n");
    }
    wallpaperTex.setSmooth(true);

    sf::Texture cursorTex;
    if (!cursorTex.loadFromFile("resources/cursor.png")) {
        printf("Error loading cursor\n");
    }
    cursorTex.setSmooth(true);

    #pragma endregion
    #pragma region shapes

    sf::CircleShape shape(5);
    shape.setFillColor(sf::Color::Green);

	sf::Text text("",sysfont,16);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(4);

    sf::Sprite wallpaperSpr;
    wallpaperSpr.setTexture(wallpaperTex);
    wallpaperSpr.setScale(
        (1920.0f/wallpaperTex.getSize().x),
        (1080.0f/wallpaperTex.getSize().y)
    );

    sf::Sprite cursorSpr;
    cursorSpr.setTexture(cursorTex);
    cursorSpr.setScale(
        (mouseSize/cursorTex.getSize().x),
        (mouseSize/cursorTex.getSize().y)
    );

    
    #pragma endregion


	firstFrameTime=my_clock.getElapsedTime();
    #pragma endregion
    while (window.isOpen()) {
		currentTime=my_clock.getElapsedTime();
		deltaTime=currentTime-lastFrameTime;
		lastFrameTime=my_clock.getElapsedTime();


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        realMousePos=sf::Mouse::getPosition(window);
        mousePos=sf::Vector2f(mousePos)+sf::Vector2f(sf::Vector2f(realMousePos)-mousePos)/mouseSmoothness;

        window.clear();

        window.draw(wallpaperSpr);

		// shape.setRadius(currentTime.asSeconds()*2);
		shape.setPosition({mousePos.x,mousePos.y});
		cursorSpr.setPosition({mousePos.x,mousePos.y});
		text.setString(string_format("%d,%d\n%.1f",sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y,roundNth(1.0f/deltaTime.asSeconds(),10)));
        window.draw(text);
        window.draw(cursorSpr);

        window.display();

		t++;
    }

    printf("\n\n\n");
    return 0;
}