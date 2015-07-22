#include "App.h"
#include <iostream>
#include <string>
using namespace std;
//#include "findpath.h"
//#include "findpath.cpp"

//TO DO
//Collision
//Collectible sprites
//Scoring
//Animations
//Sound
//Nodes
//AI


App::App(char *Title, int ScreenWidth, int ScreenHeight, int ScreenBpp)
{
    MainWindow.Create(sf::VideoMode( ScreenWidth, ScreenHeight, ScreenBpp), Title );
 
    MainWindow.SetFramerateLimit(0);
 
    View = MainWindow.GetDefaultView();
 
}
 
App::~App()
{
    // Clean stuff up
}


bool App::Init()
{
	// Initialize stuff
	SplashScreenCheck = true;
	MenuCheck = false;
	MenuDraw = false;
	PlayCheck = false;
	tempX = 0;
	tempY = 0;

	iScore = 0;
	sScore = "NULL";
	pinkTime = 0;
	orangeTime = 0;

	FruitCount = 0;
	Count = 0;
	GhostStart = 0;

	iLives = 3;
	sScore = "NULL";

	MapSearchNode* findPath = new MapSearchNode();
	if (!Font.LoadFromFile("fonts/arial.ttf"))
	{
		cout<<"Error"<<endl;
	}
	ScoreDisplay.SetFont(Font);
	ScoreDisplay.SetSize(50);
	ScoreDisplay.SetColor(sf::Color(255, 255, 255));
	ScoreDisplay.SetPosition(10,950);

	LivesDisplay.SetFont(Font);
	LivesDisplay.SetSize(50);
	LivesDisplay.SetColor(sf::Color(255, 255, 255));
	LivesDisplay.SetPosition(10,10);


	if(!PlayerImage.LoadFromFile("images/PacmanSheet.png"))
	{
	}
	PlayerSprite.SetImage(PlayerImage);
	PlayerSprite.SetPosition(367,671);
	PlayerRect = sf::Rect<float>();

	PacmanLeft = 0;
	PacmanRight = 35;
	PacmanUp = 70;
	PacmanDown = 105;
	PacmanX = 0;
	PacmanY = PacmanLeft;

	frameCounter = 0;
	switchFrame = 10;
	ghostFrameCounter = 0;
	ghostSwitchFrame = 10;
	
	if(!SplashScreenImage.LoadFromFile("images/SplashScreen.png"))
	{
	}
	SplashScreenSprite.SetImage(SplashScreenImage);
    
	if(!GameOverImage.LoadFromFile("images/GameOver.png"))
	{
	}
	GameOverSprite.SetImage(GameOverImage);
	GameOver = false;

	if(!MenuImage.LoadFromFile("images/mainmenu.png"))
	{
	}
	MenuSprite.SetImage(MenuImage);

	/*playButton(0,145,1023,380);
	exitButton(0,383,1023,560);*/

	playButton = sf::Rect<float>();
	exitButton = sf::Rect<float>();

	xVelocity = 0.0f;
	yVelocity = 0.0f;

	if(!LevelSplashImage.LoadFromFile("images/EndLevel.png"))
	{
	}
	LevelSplashSprite.SetImage(LevelSplashImage);

	if(!GameImage.LoadFromFile("images/Background.png"))
	{
	}
	GameSprite.SetImage(GameImage);

	if(!PillImage.LoadFromFile("images/Pill.png"))
	{
	}
	//PillSprite.SetImage(PillImage);
	//PillSprite.SetPosition(200,200);
	//PillRect = sf::Rect<float>();

	if(!RedGhostImage.LoadFromFile("images/ghosts/RedSheet.png"))
	{
	}
	RedGhostSprite.SetImage(RedGhostImage);
	RedGhostSprite.SetPosition(310,480);
	RedGhostRect = sf::Rect<float>();
	
	if(!CyanGhostImage.LoadFromFile("images/ghosts/CyanSheet.png"))
	{
	}
	CyanGhostSprite.SetImage(CyanGhostImage);
	CyanGhostSprite.SetPosition(350,480);
	CyanGhostRect = sf::Rect<float>();

	if(!PinkGhostImage.LoadFromFile("images/ghosts/PinkSheet.png"))
	{
	}
	PinkGhostSprite.SetImage(PinkGhostImage);
	PinkGhostSprite.SetPosition(390,480);
	PinkGhostRect = sf::Rect<float>();

	if(!OrangeGhostImage.LoadFromFile("images/ghosts/OrangeSheet.png"))
	{
	}
	OrangeGhostSprite.SetImage(OrangeGhostImage);
	OrangeGhostSprite.SetPosition(430,480);
	OrangeGhostRect = sf::Rect<float>();

	GhostLeft = 0;
	GhostRight = 35;
	GhostUp = 70;
	GhostDown = 105;
	GhostX = 0;
	GhostY = GhostLeft;

	if(!PowerPillImage.LoadFromFile("images/PowerPill.png"))
	{
	}
	//PowerPillSprite.SetImage(PowerPillImage);
	//PowerPillSprite.SetPosition(400,400);
	//PowerPillRect = sf::Rect<float>();

	if(!FruitImage.LoadFromFile("Fruit.png"))
	{
	}
	FruitSprite.SetImage(FruitImage);
	FruitSprite.SetPosition(2000,2000);
	FruitRect = sf::Rect<float>();

	
	bInvulnerable = false;
    
	
	if (!MoveBuffer.LoadFromFile("sounds/pacman.wav"))
	{
		// Error...
	}
	MoveSound.SetBuffer(MoveBuffer);
	MoveSound.SetLoop(true);
	MoveSound.SetVolume(10.f);

	if (!GameMusic.OpenFromFile("sounds/music1.wav"))
	{
		// Error...
	}

	Map();

	pathfinding = MapSearchNode();
	CyanGhostMoveX = 10;
	CyanGhostMoveY = 50;

	//int* gameMap = pathfinding.initialise();
	//pathfinding.GetMap();

	return true;
}
void App::Death()
{
	PlayerSprite.SetPosition(367,671);
	RedGhostSprite.SetPosition(310,480);
	CyanGhostSprite.SetPosition(350,480);
	PinkGhostSprite.SetPosition(390,480);
	OrangeGhostSprite.SetPosition(430,480);
	iLives--;
	if(iLives < 0)
	{
		GameOver = true;
		PlayCheck = false;
	}
}
void App::Update()
{
    //Update stuff
	ElapsedTime = MainWindow.GetFrameTime();
	PlayerSprite.Move(xVelocity * ElapsedTime, yVelocity * ElapsedTime);

	ostringstream Convert1;
	Convert1 << "Score: ";
	Convert1 << iScore;
	sScore = Convert1.str();
	ScoreDisplay.SetText(sScore);

	ostringstream Convert2;
	Convert2 << "Lives: ";
	Convert2 << iLives;
	sLives = Convert2.str();
	LivesDisplay.SetText(sLives);

	if(FruitCount > 100)
	{
		FruitSprite.SetPosition(367,671);
		FruitCount = 0;
	}

	Rects();
	Collision();

	if(xVelocity == 0 && yVelocity == 0)
	{
		MoveSound.Pause();
		PacmanX = 0;
	}

	if (PlayCheck == true)
	{
		Music();
		for (int i = 0; i < 1; i++)
		{
			//Map();
		}
	}

	if (xVelocity != 0 || yVelocity != 0)
	{
		frameCounter += 100 * ElapsedTime;
	}
	else
	{
		frameCounter = 0;
	}

	ghostFrameCounter += 100 * ElapsedTime;

	
	if(ClockInvulnerable.GetElapsedTime() > 6)
	{
		bInvulnerable = false;
	}

	if(bInvulnerable == false)
	{
		RedGhostImage.LoadFromFile("images/ghosts/RedSheet.png");
		CyanGhostImage.LoadFromFile("images/ghosts/CyanSheet.png");
		PinkGhostImage.LoadFromFile("images/ghosts/PinkSheet.png");
		OrangeGhostImage.LoadFromFile("images/ghosts/OrangeSheet.png");
	}

	//Animate sprites at and even speed
	if(frameCounter >= switchFrame)
	{
		frameCounter = 0;
		Clock.Reset();
		PacmanX += PlayerImage.GetWidth() / 4;
	}

	if(ghostFrameCounter >= ghostSwitchFrame)
	{
		ghostFrameCounter = 0;
		Clock.Reset();
		GhostX += RedGhostImage.GetWidth() / 2;
		PowerPillX += PowerPillImage.GetWidth() / 2;
	}

	//Pacman animation
	if(PacmanX == PlayerImage.GetWidth())
	{
		PacmanX = 0;
	}
	PlayerSprite.SetSubRect(sf::IntRect(PacmanX, PacmanY, PacmanX + PlayerImage.GetWidth() / 4, PacmanY + PlayerImage.GetHeight() / 4));

	//Ghost animation
	if(GhostX == RedGhostImage.GetWidth())
	{
		GhostX = 0;
	}
	if(bInvulnerable == false)
	{
		RedGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + RedGhostImage.GetWidth() / 2, GhostY + RedGhostImage.GetHeight() / 4));
		CyanGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + CyanGhostImage.GetWidth() / 2, GhostY + CyanGhostImage.GetHeight() / 4));
		PinkGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + PinkGhostImage.GetWidth() / 2, GhostY + PinkGhostImage.GetHeight() / 4));
		OrangeGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + OrangeGhostImage.GetWidth() / 2, GhostY + OrangeGhostImage.GetHeight() / 4));
	}
	else if(bInvulnerable == true)
	{
		RedGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + RedGhostImage.GetWidth() / 2, GhostY + RedGhostImage.GetHeight()));
		CyanGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + CyanGhostImage.GetWidth() / 2, GhostY + CyanGhostImage.GetHeight()));
		PinkGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + PinkGhostImage.GetWidth() / 2, GhostY + PinkGhostImage.GetHeight()));
		OrangeGhostSprite.SetSubRect(sf::IntRect(GhostX, GhostY, GhostX + OrangeGhostImage.GetWidth() / 2, GhostY + OrangeGhostImage.GetHeight()));
	}

	//Get ghost position
	RedGhostNodeX = RedGhostSprite.GetPosition().x;
	RedGhostNodeY = RedGhostSprite.GetPosition().y;

	CyanGhostNodeX = CyanGhostSprite.GetPosition().x;
	CyanGhostNodeY = CyanGhostSprite.GetPosition().y;
	
	PinkGhostNodeX = PinkGhostSprite.GetPosition().x;
	PinkGhostNodeY = PinkGhostSprite.GetPosition().y;

	OrangeGhostNodeX = OrangeGhostSprite.GetPosition().x;
	OrangeGhostNodeY = OrangeGhostSprite.GetPosition().y;

	//Get player position
	for(int y = 0; y < 21; y++)
	{

		for(int x = 0; x < 21; x++)
		{
			
			if(PlayerRect.Intersects(RectArray[y][x]))
			{
				PlayerNodeX = x;
				PlayerNodeY = y;
				//cout<<x<<" "<<y<<endl;
			}
			
		}
		
	}

	if(Count == 192)
	{
		FruitCount = 0;
		GhostStart = 0;
		Count = 0;
		PlayCheck = false;
		NewLevel = true;

		PlayerSprite.SetPosition(367,671);
		xVelocity = 0;
		yVelocity = 0;
		
		RedGhostSprite.SetPosition(310,480);
		CyanGhostSprite.SetPosition(350,480);
		PinkGhostSprite.SetPosition(390,480);
		OrangeGhostSprite.SetPosition(430,480);

		Map();
	}

	redGhost();
	cyanGhost();
	pinkGhost();
	orangeGhost();

}
 
void App::Draw()
{
    MainWindow.Clear();
 
    MainWindow.SetView( View );
	
    //Draw stuff needed
	if (SplashScreenCheck == true)
	{
		MainWindow.Draw(SplashScreenSprite);
		
	}

	if (MenuCheck == true)
	{
		MainWindow.Draw(MenuSprite);
		MenuDraw = true;
	}

	if (PlayCheck == true)
	{
			MainWindow.Draw(GameSprite);
			//MainWindow.Draw(PowerPillSprite);
			//MainWindow.Draw(PillSprite);
			MainWindow.Draw(PlayerSprite);
			//MainWindow.Draw(GhostSprite);
			MainWindow.Draw(ScoreDisplay);
			MainWindow.Draw(LivesDisplay);
			MainWindow.Draw(RedGhostSprite);
			MainWindow.Draw(CyanGhostSprite);
			MainWindow.Draw(PinkGhostSprite);
			MainWindow.Draw(OrangeGhostSprite);

			if(Count > 100)
			{
				MainWindow.Draw(FruitSprite);
			}

			MainWindow.Draw(ScoreDisplay);
			for(int x = 0; x < 21; x++)
			{
				for(int y = 0; y < 21; y++)
				{
					if(GameArray[x][y] == 1)
					{
						MainWindow.Draw(PillArray[x][y]);
					}
					else if(GameArray[x][y] == 2)
					{
						MainWindow.Draw(PowerPillArray[x][y]);
					}
				}
			}
	}

	if (GameOver == true)
	{
		MainWindow.Draw(GameOverSprite);
	}

	if (NewLevel == true)
	{
		MainWindow.Draw(LevelSplashSprite);
	}

    MainWindow.Display();

}

void App::Rects()
{
	//Player
	PlayerRect.Left = PlayerSprite.GetPosition().x + 10;
	PlayerRect.Right = PlayerSprite.GetPosition().x + 25;
	PlayerRect.Top= PlayerSprite.GetPosition().y + 10;
	PlayerRect.Bottom = PlayerSprite.GetPosition().y + 25;


	//Ghosts
	RedGhostRect.Left = RedGhostSprite.GetPosition().x;
	RedGhostRect.Right = RedGhostSprite.GetPosition().x + RedGhostSprite.GetSize().x;
	RedGhostRect.Top = RedGhostSprite.GetPosition().y;
	RedGhostRect.Bottom = RedGhostSprite.GetPosition().y + RedGhostSprite.GetSize().y;

	CyanGhostRect.Left = CyanGhostSprite.GetPosition().x;
	CyanGhostRect.Right = CyanGhostSprite.GetPosition().x + CyanGhostSprite.GetSize().x;
	CyanGhostRect.Top = CyanGhostSprite.GetPosition().y;
	CyanGhostRect.Bottom = CyanGhostSprite.GetPosition().y + CyanGhostSprite.GetSize().y;

	PinkGhostRect.Left = PinkGhostSprite.GetPosition().x;
	PinkGhostRect.Right = PinkGhostSprite.GetPosition().x + PinkGhostSprite.GetSize().x;
	PinkGhostRect.Top = PinkGhostSprite.GetPosition().y;
	PinkGhostRect.Bottom = PinkGhostSprite.GetPosition().y + PinkGhostSprite.GetSize().y;

	OrangeGhostRect.Left = OrangeGhostSprite.GetPosition().x;
	OrangeGhostRect.Right = OrangeGhostSprite.GetPosition().x + OrangeGhostSprite.GetSize().x;
	OrangeGhostRect.Top = OrangeGhostSprite.GetPosition().y;
	OrangeGhostRect.Bottom = OrangeGhostSprite.GetPosition().y + OrangeGhostSprite.GetSize().y;
	

	//Pills
	for(int x = 0; x < 21; x++)
	{
		for(int y = 0; y < 21; y++)
		{
			if(GameArray[x][y] == 1)
			{
			PillRectArray[x][y].Left = PillArray[x][y].GetPosition().x;
			PillRectArray[x][y].Right = PillArray[x][y].GetPosition().x + PillArray[x][y].GetSize().x;
			PillRectArray[x][y].Top= PillArray[x][y].GetPosition().y;
			PillRectArray[x][y].Bottom = PillArray[x][y].GetPosition().y + PillArray[x][y].GetSize().y;
			}
		}
	}

	//PowerPills
	for(int x = 0; x < 21; x++)
	{
		for(int y = 0; y < 21; y++)
		{
			if(GameArray[x][y] == 2)
			{
			PowerPillRectArray[x][y].Left = PowerPillArray[x][y].GetPosition().x;
			PowerPillRectArray[x][y].Right = PowerPillArray[x][y].GetPosition().x + PowerPillArray[x][y].GetSize().x;
			PowerPillRectArray[x][y].Top= PowerPillArray[x][y].GetPosition().y;
			PowerPillRectArray[x][y].Bottom = PowerPillArray[x][y].GetPosition().y + PowerPillArray[x][y].GetSize().y;
			}
		}
	}

	//Fruit
	FruitRect.Left = FruitSprite.GetPosition().x;
	FruitRect.Right = FruitSprite.GetPosition().x + FruitSprite.GetSize().x;
	FruitRect.Top = FruitSprite.GetPosition().y;
	FruitRect.Bottom = FruitSprite.GetPosition().y + FruitSprite.GetSize().y;

}
void App::Music()
{
	if(PlayCheck)
	{
		GameMusic.Pause();
		GameMusic.Play();
	}
}
void App::redGhost()
{
	pathfinding.findPath(RedGhostNodeX, RedGhostNodeY, PlayerNodeX, PlayerNodeY, RedGhostSprite);
	if (bInvulnerable == false)
	{
		if (GhostStart > 1)
		{
			RedGhostSprite.Move((PlayerSprite.GetPosition().x+10-RedGhostSprite.GetPosition().x)/25, (PlayerSprite.GetPosition().y-10-RedGhostSprite.GetPosition().y)/25);
		}
	}
	if (bInvulnerable == true)
	{
		RedGhostSprite.Move(0,0);
	}
}
void App::cyanGhost()
{
	pathfinding.findPath(CyanGhostNodeX, CyanGhostNodeY, PlayerNodeX, PlayerNodeY, CyanGhostSprite);
	if (bInvulnerable == false)
	{
		if (GhostStart > 3)
		{
			CyanGhostSprite.Move((PlayerSprite.GetPosition().x+10-CyanGhostSprite.GetPosition().x)/50, (PlayerSprite.GetPosition().y+10-CyanGhostSprite.GetPosition().y)/50);
		}
	}
	if (bInvulnerable == true)
	{
		CyanGhostSprite.Move(0,0);
	}
	
}
void App::pinkGhost()
{
	
	pathfinding.findPath(PinkGhostNodeX, PinkGhostNodeY, PlayerNodeX, PlayerNodeY, PinkGhostSprite);
	if (bInvulnerable == false)
	{
		if (GhostStart > 6)
		{
		PinkGhostSprite.Move((PlayerSprite.GetPosition().x-10-PinkGhostSprite.GetPosition().x)/50, (PlayerSprite.GetPosition().y+10-PinkGhostSprite.GetPosition().y)/50);
		}
	}
	if (bInvulnerable == true)
	{
		PinkGhostSprite.Move(0,0);
	}
}
void App::orangeGhost()
{
	pathfinding.findPath(OrangeGhostNodeX, OrangeGhostNodeY, PlayerNodeX, PlayerNodeY, OrangeGhostSprite);
	if (bInvulnerable == false)
	{
		if (GhostStart > 10)
		{
			OrangeGhostSprite.Move((PlayerSprite.GetPosition().x-10-OrangeGhostSprite.GetPosition().x)/50, (PlayerSprite.GetPosition().y-10-OrangeGhostSprite.GetPosition().y)/50);	
		}
	}
	if (bInvulnerable == true)
	{
		OrangeGhostSprite.Move(0,0);
	}
}
void App::Map()
{
	XCoord = 17;
	YCoord = 146;

	for(int x = 0; x < 21; x++)
	{

		for(int y = 0; y < 21; y++)
		{
			PillArray[x][y].SetImage(PillImage);
			PillArray[x][y].SetPosition(XCoord + 12, YCoord + 12);
			XCoord += 35;
		}
		YCoord += 35;
		XCoord = 17;
	}

	YCoord = 146;

	for(int x = 0; x < 21; x++)
	{

		for(int y = 0; y < 21; y++)
		{
			PowerPillArray[x][y].SetImage(PowerPillImage);
			PowerPillArray[x][y].SetPosition(XCoord + 7, YCoord + 7);
			PowerPillRectArray[x][y] = sf::Rect<float>();
			XCoord += 35;
		}
		YCoord += 35;
		XCoord = 17;
	}

	YCoord = 146;
	int TempArray[21][21] = 
	{
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,	
		9,2,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,2,9,	
		9,1,9,9,9,1,9,9,9,1,9,1,9,9,9,1,9,9,9,1,9,	
		9,1,9,9,9,1,9,9,9,1,9,1,9,9,9,1,9,9,9,1,9,	
		9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,	
		9,1,9,9,9,1,9,1,9,9,9,9,9,1,9,1,9,9,9,1,9,	
		9,1,1,1,1,1,9,1,1,1,9,1,1,1,9,1,1,1,1,1,9,	
		9,9,9,9,9,1,9,9,9,1,9,1,9,9,9,1,9,9,9,9,9,	
		9,9,9,9,9,1,9,1,1,1,1,1,1,1,9,1,9,9,9,9,9,	
		9,9,9,9,9,1,9,1,9,9,9,9,9,1,9,1,9,9,9,9,9,	
		1,1,1,1,1,1,1,1,9,9,9,9,9,1,1,1,1,1,1,1,1,	
		9,9,9,9,9,1,9,1,1,1,1,1,1,1,9,1,9,9,9,9,9,	
		9,9,9,9,9,1,9,1,9,9,9,9,9,1,9,1,9,9,9,9,9,	
		9,9,9,9,9,1,9,1,1,1,9,1,1,1,9,1,9,9,9,9,9,	
		9,1,1,1,1,1,1,1,9,1,9,1,9,1,1,1,1,1,1,1,9,	
		9,1,9,9,1,9,9,9,9,1,3,1,9,9,9,9,1,9,9,1,9,	
		9,1,9,9,1,1,1,1,1,1,9,1,1,1,1,1,1,9,9,1,9,	
		9,1,9,9,1,9,9,9,9,1,9,1,9,9,9,9,1,9,9,1,9,	
		9,1,9,9,1,9,9,9,9,1,9,1,9,9,9,9,1,9,9,1,9,	
		9,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,9,	
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,  
	};
	
	for(int x = 0; x < 21; x++)
	{
		for(int y = 0; y < 21; y++)
		{
			GameArray[x][y] = TempArray[x][y];
		}
	}

	for(int x = 0; x < 21; x++)
	{

		for(int y = 0; y < 21; y++)
		{
			RectArray[x][y] = sf::Rect<float>(XCoord, YCoord, (XCoord + 35), (YCoord + 35));
			XCoord += 35;
		}
		YCoord +=35;
		XCoord = 17;
	}
}
void App::PlayerControls()
{
	if( ( Event.Type == sf::Event::KeyPressed ) && ( Event.Key.Code == sf::Key::Down ) )
	{
		MoveSound.Pause();
		MoveSound.Play();
		yVelocity = 300.0f;
		xVelocity  = 0.0f;

		PacmanY = PacmanDown;
	}

	if( ( Event.Type == sf::Event::KeyPressed ) && ( Event.Key.Code == sf::Key::Up ) )
	{
		MoveSound.Pause();
		MoveSound.Play();
		yVelocity = -300.0f;
		xVelocity = 0.0f;

		PacmanY = PacmanUp;
	}

	if( ( Event.Type == sf::Event::KeyPressed ) && ( Event.Key.Code == sf::Key::Left ) )
	{
		MoveSound.Pause();
		MoveSound.Play();
		xVelocity = -300.0f;
		yVelocity = 0.0f;

		PacmanY = PacmanLeft;
	}

	if( ( Event.Type == sf::Event::KeyPressed ) && ( Event.Key.Code == sf::Key::Right ) )
	{
		MoveSound.Pause();
		MoveSound.Play();
		xVelocity = 300.0f;
		yVelocity = 0.0f;

		PacmanY = PacmanRight;
	}
}

void App::Collision()
{
	//Wall
	if(PlayerSprite.GetPosition().x + PlayerSprite.GetSize().x > 768 + PlayerSprite.GetSize().x)
	{
		PlayerSprite.SetPosition(-PlayerSprite.GetSize().x, PlayerSprite.GetPosition().y);
	}
	if(PlayerSprite.GetPosition().x < -PlayerSprite.GetSize().x)
	{
		PlayerSprite.SetPosition(768, PlayerSprite.GetPosition().y);
	}
	//if(PlayerSprite.GetPosition().y + PlayerSprite.GetSize().y >= 768)
	//{
	//	xVelocity = 0.0f;
	//	yVelocity = 0.0f;
	//}
	//if(PlayerSprite.GetPosition().y <= 0)
	//{
	//	xVelocity = 0.0f;
	//	yVelocity = 0.0f;
	//}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if(PlayerRect.Intersects(RectArray[i][j]))
			{
				//cout<<"Collision"<<endl;
				if(GameArray[i][j] == 9)
				{
					xVelocity = 0.0f;
					yVelocity = 0.0f;
					//cout<<"You hit a wall."<<endl;
					tempX = PlayerSprite.GetPosition().x;
					tempY =  PlayerSprite.GetPosition().y;
					PlayerSprite.SetPosition(OldX, OldY);
				
				}
			}
		}
	}

	OldX = PlayerSprite.GetPosition().x;
	OldY = PlayerSprite.GetPosition().y;

	//Ghost when Pacman vulnerable
	if(bInvulnerable == false)
	{
		if(RedGhostRect.Intersects(PlayerRect))
		
		{
			Death();
			GhostStart = 0;
			//Kill pacman
		}
		if(CyanGhostRect.Intersects(PlayerRect))
		{
			Death();
			GhostStart = 0;
		}
		if(PinkGhostRect.Intersects(PlayerRect))
		{
			Death();
			GhostStart = 0;
		}
		if(OrangeGhostRect.Intersects(PlayerRect))
		{
			Death();
			GhostStart = 0;
		}
		
	}
	
	//Ghost when Pacman invulnerable
	if(bInvulnerable == true)
	{
		if(RedGhostRect.Intersects(PlayerRect))
		{
			RedGhostSprite.SetPosition(310,480);
		}
		if(CyanGhostRect.Intersects(PlayerRect))
		{
			CyanGhostSprite.SetPosition(350,480);
		}
		if(PinkGhostRect.Intersects(PlayerRect))
		{
			PinkGhostSprite.SetPosition(390,480);
		}
		if(OrangeGhostRect.Intersects(PlayerRect))
		{
			OrangeGhostSprite.SetPosition(430,480);
		}
		
	}

	//Pills
	for(int x = 0; x < 21; x++)
	{
		for(int y = 0; y < 21; y++)
		{
			if(PlayerRect.Intersects(PillRectArray[x][y]))
			{
				PillArray[x][y].SetPosition(2000,2000);
				iScore += 20;
				Count++;
				FruitCount++;
				GhostStart++;
			}
		}
	}
	
	//Power Pills
	for(int x = 0; x < 21; x++)
	{
		for(int y = 0; y < 21; y++)
		{
			if(PlayerRect.Intersects(PowerPillRectArray[x][y]))
			{
				PowerPillArray[x][y].SetPosition(2000,2000);
				iScore += 50;
				Count++;
				FruitCount++;
				GhostStart++;
				bInvulnerable = true;
				ClockInvulnerable.Reset();
				for(int z = 0; z < 4; z++)
				{
					RedGhostImage.LoadFromFile("images/ghosts/ScaredSheet.png");
					CyanGhostImage.LoadFromFile("images/ghosts/ScaredSheet.png");
					PinkGhostImage.LoadFromFile("images/ghosts/ScaredSheet.png");
					OrangeGhostImage.LoadFromFile("images/ghosts/ScaredSheet.png");
				}
			}
		}
	}

	//Fruit
	if(PlayerRect.Intersects(FruitRect))
	{
		FruitSprite.SetPosition(2000,2000);
		iScore +=200;
	}
	
}

void App::HandleEvents()
{
     const sf::Input& Input = MainWindow.GetInput();

	 if (SplashScreenCheck == true)
	 {	
		if(Event.Type == sf::Event::KeyPressed
			|| Event.Type == sf::Event::MouseButtonPressed
			|| Event.Type == sf::Event::Closed )
		{
			SplashScreenCheck = false;
			MenuCheck = true;
		}
	 }

	 
	if(MenuDraw == true)
	{
	if(Event.Type == sf::Event::MouseButtonPressed 
		&& (Input.GetMouseX() < 1023 && Input.GetMouseX() > 0) 
		&& (Input.GetMouseY() < 419 && Input.GetMouseY() > 245))
	{
		MenuDraw = false;
		MenuCheck = false;
		PlayCheck = true;
	}
		
	if(Event.Type == sf::Event::MouseButtonPressed 
		&& (Input.GetMouseX() < 1023 && Input.GetMouseX() > 0) 
		&& (Input.GetMouseY() < 620 && Input.GetMouseY() > 446))
		{
			MainWindow.Close();
		}
	}

     if( Event.Type == sf::Event::Closed )
          MainWindow.Close();
 
     if( ( Event.Type == sf::Event::KeyPressed ) && ( Event.Key.Code == sf::Key::Escape ) )
          MainWindow.Close();
	
	 if(PlayCheck == true)
	 {
		 
		//PUT PLAYER SPRITE RECT HERE FOR COLLISION DETECTION
		//COLLISION DETECTION FOR WALL
		//COLLISION DETECTION FOR MAZE
		//COLLISION DETECTION FOR GHOSTS
		//COLLISION DETECTION FOR COLLECTIBLES
		
		//Possibly other classes for collision detection
		PlayerControls();
		
	 }
	
      if (NewLevel == true)
	 {	
		if(Event.Type == sf::Event::KeyPressed
			|| Event.Type == sf::Event::MouseButtonPressed
			|| Event.Type == sf::Event::Closed )
		{
			NewLevel = false;
			PlayCheck = true;
		}
	 }
}

 
void App::Run()
{
    while(MainWindow.IsOpened())

    {
        while(MainWindow.GetEvent(Event))
        {
            HandleEvents();
        }
        Update();
        Draw();
    }
}


