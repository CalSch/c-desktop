#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <stdio.h>
#include "util.h"
#include "animation.h"
#include "easings.h"

#pragma region vars
int t=0;
sf::Vector2f mousePos;
sf::Vector2f oldMousePos;
sf::Vector2f mouseDelta;
sf::Vector2i realMousePos;

bool mouseLeftDown=false;
bool oldMouseLeftDown=false;
bool mouseLeftPressed=false;
bool mouseLeftReleased=false;

bool mouseRightDown=false;
bool oldMouseRightDown=false;
bool mouseRightPressed=false;
bool mouseRightReleased=false;


float mouseSmoothness=3;
float mouseSize=22;
#pragma endregion

const char* str(int    a) {return std::to_string(a).c_str();}
const char* str(float  a) {return std::to_string(a).c_str();}
const char* str(double a) {return std::to_string(a).c_str();}

float roundNth(float x,float n) {
    return std::roundf(x*n)/n;
}


cal::Animation ani;
cal::Transform aniT;


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

    window.clear(sf::Color::Magenta);
    window.display();

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
    #pragma region animation
    
    ani=cal::Animation(0.075f,{{0,0},cursorSpr.getScale(),0},{{0,0},cursorSpr.getScale()*0.8f,0},&cal::linear);

    #pragma endregion

	firstFrameTime=my_clock.getElapsedTime();
    #pragma endregion
    while (window.isOpen()) {
        #pragma region engine
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
        mouseDelta=mousePos-oldMousePos;

        mouseLeftDown=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        mouseRightDown=sf::Mouse::isButtonPressed(sf::Mouse::Right);
        mouseLeftPressed=!oldMouseLeftDown && mouseLeftDown;
        mouseRightPressed=!oldMouseRightDown && mouseRightDown;
        mouseLeftReleased=oldMouseLeftDown && !mouseLeftDown;
        mouseRightReleased=oldMouseRightDown && !mouseRightDown;

        #pragma endregion

        // ==== Update ====

        ani.update(deltaTime.asSeconds());

		cursorSpr.setPosition({mousePos.x,mousePos.y});
        if (mouseLeftPressed||mouseRightPressed) {
            ani.restart();
            ani.easing=&cal::linear;
        } else if (mouseLeftReleased||mouseRightReleased) {
            ani.restart();
            ani.easing=&cal::rLinear;
        }
        aniT=ani.getCurrentTransform();
        cursorSpr.setScale(aniT.scale);
		text.setString(cal::string_format("%f\n%d",ani.time,sf::Mouse::isButtonPressed(sf::Mouse::Left)));


        // ==== Draw ====


        window.clear();

        window.draw(wallpaperSpr);
        window.draw(text);
        window.draw(cursorSpr);

        window.display();

		t++;
        oldMousePos=mousePos;
        oldMouseLeftDown=mouseLeftDown;
        oldMouseRightDown=mouseRightDown;
    }

    printf("\n\n\n");
    return 0;
}