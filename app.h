#ifndef APP_H
#define APP_H
 
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "findpath.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;
class App
{
private:
    sf::Event            Event;        // The event
    sf::View            View;          // The view
    sf::RenderWindow        MainWindow;     // The render window

	//Player
	sf::Image PlayerImage;
	sf::Sprite PlayerSprite;
	int PacmanLeft;
	int PacmanRight;
	int PacmanUp;
	int PacmanDown;
	int PacmanX;
	int PacmanY;
	sf::Rect<float> PlayerRect;
	int PlayerNodeX;
	int PlayerNodeY;
	int OldX;
	int OldY;

	//Splash Screen
	sf::Image SplashScreenImage;
	sf::Sprite SplashScreenSprite;
	bool SplashScreenCheck;

	sf::Image GameOverImage;
	sf::Sprite GameOverSprite;
	bool GameOver;

	//Main menu
	sf::Image MenuImage;
	sf::Sprite MenuSprite;
	bool MenuCheck;
	bool MenuDraw;
	bool PlayCheck;
	bool NewLevel;
	sf::Rect<float> playButton;
	sf::Rect<float> exitButton;

	//Game map
	sf::Image GameImage;
	sf::Sprite GameSprite;

	//Player movement
	float xVelocity;
	float yVelocity;
	float ElapsedTime;
		
	//Pills
	/*sf::Image PillImage;
	sf::Sprite PillSprite;
	sf::Rect<float> PillRect;*/
	sf::Sprite PillArray[21][21];
	sf::Rect<float> PillRectArray[21][21];
	sf::Image PillImage;

	//Power Pills
	/*sf::Image PowerPillImage;
	sf::Sprite PowerPillSprite;
	sf::Rect<float> PowerPillRect;*/
	sf::Sprite PowerPillArray[21][21];
	sf::Rect<float> PowerPillRectArray[21][21];
	sf::Image PowerPillImage;
	int PowerPillX;
	int PowerPillY;

	bool bInvulnerable;
	sf::Clock ClockInvulnerable;
	
	//Ghosts
	sf::Image RedGhostImage;
	sf::Sprite RedGhostSprite;
	sf::Rect<float> RedGhostRect;
	int GhostLeft;
	int GhostRight;
	int GhostUp;
	int GhostDown;
	int GhostX;
	int GhostY;

	int RedGhostNodeX;
	int RedGhostNodeY;
	int CyanGhostNodeX;
	int CyanGhostNodeY;
	int PinkGhostNodeX;
	int PinkGhostNodeY;
	int OrangeGhostNodeX;
	int OrangeGhostNodeY;

	sf::Image CyanGhostImage;
	sf::Sprite CyanGhostSprite;
	sf::Rect<float> CyanGhostRect;

	sf::Image PinkGhostImage;
	sf::Sprite PinkGhostSprite;
	sf::Rect<float> PinkGhostRect;

	sf::Image OrangeGhostImage;
	sf::Sprite OrangeGhostSprite;
	sf::Rect<float> OrangeGhostRect;

	//Fruit
	sf::Image FruitImage;
	sf::Sprite FruitSprite;
	sf::Rect<float> FruitRect;

	//Scoring
	int iScore;
	string sScore;

	//Lives
	int iLives;
	string sLives;
	
	//Fonts
	sf::Font Font;
	sf::String ScoreDisplay;
	ostringstream Convert1;
	sf::String LivesDisplay;
	ostringstream Convert2;

	//Sound
	sf::SoundBuffer MoveBuffer;
	sf::Sound MoveSound;
	sf::Music GameMusic;

	//Animation
	sf::Clock Clock;
	float frameCounter;
	float switchFrame;

	float ghostFrameCounter;
	float ghostSwitchFrame;

	

	//int firstNodeX, firstNodeY;

	//Pathfinding
	//MapSearchNode *findPath(int StartNodeX, int StartNodeY, int EndNodeX, int EndNodeY, sf::Sprite AISprite);
	MapSearchNode pathfinding;

	//New Level Screen
	sf::Sprite LevelSplashSprite;
	sf::Image LevelSplashImage;

	int Count;
	int FruitCount;
	int GhostStart;

	//Mapping
	sf::Rect<float> RectArray[21][21];
	int GameArray[21][21];
	//map <sf::Rect<float>, int> RectMap;
	float XCoord;
	float YCoord;

	//Miscellaneous
	int CyanGhostMoveX;
	int CyanGhostMoveY;
	int tempX;
	int tempY;
	int pinkTime;
	int orangeTime;

public:
 
    App( char* Title,                // The constructor
         int   ScreenWidth, 
         int   ScreenHeight,
         int   ScreenBpp );
	
    ~App();                        // The destructor
 
    bool Init();                    // Initializes everything not in the constructor
    void HandleEvents();                // Handles input from the player
    void Draw();                    // Draws the scene
    void Update();                    // Updates variables, game object, etc.
    void Run();
	void PlayerControls();
	void Collision();
	void Rects();
	void Music();
	void redGhost();
	void cyanGhost();
	void pinkGhost();
	void orangeGhost();
	void Map();
	void Death();


};
 
#endif
