#include <SFML/Graphics.hpp>
#include<sstream>
#include<time.h>
#include<iomanip>
using namespace sf;
using namespace std;

int main()
{
	VideoMode vm(1280,720);
	RenderWindow window(vm,"First game");
	
	//set background
	Texture background;
	background.loadFromFile("background1280.jpg");
	Sprite spritebackground;
	spritebackground.setTexture(background);
	
	//set shooter
	Texture shooter;
	shooter.loadFromFile("shooter 70 55.jpg");
	Sprite shootersprite;
	shootersprite.setTexture(shooter);
	
	shootersprite.setPosition( (1280-70)/2,720-55);
	float shooterspeed=1;
	
	//set enemy
	Texture enemy;
	enemy.loadFromFile("enemy 60 45.jpg");
	Sprite enemysprite[60];
	for(int i=0;i<60;i++)
		enemysprite[i].setTexture(enemy);
	
	int enemyisalive[60];
	for(int i=0;i<60;i++)
		enemyisalive[i]=1;
	
	//Enemy proprities
	float enemyspeed=0.15;
	bool enemymoveright=true;
	bool godown=false;
	
	//background position
	spritebackground.setPosition(0,0);
	
	//set enemies position
	int X_E=0;
	int Y_E=90;
	for(int i=0;i<60;i++)
	{
		enemysprite[i].setPosition(X_E,Y_E);
		if(i%12==11)
		{
			X_E=0;
			Y_E+=45;
		}
		else
		{
			X_E+=60;
		}
	}
		
	Clock clock;
	double time=0;
	
	//time bar
	Text timetext;
	Font font;
	font.loadFromFile("Vazir-Light.ttf");
	timetext.setFont(font);
	timetext.setPosition(0,0);
	
	while(window.isOpen())
	{
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		
		//handle time
		Time dt=clock.restart();
		time+=dt.asSeconds();
		stringstream timebar;
		timebar<<"Time: "<<fixed<<setprecision(2)<<time<<"s";
		timetext.setString(timebar.str());
		
		window.clear();
		
		//Draw background
		window.draw(spritebackground);
		
		//Draw time bar
		window.draw(timetext);
		
		//Draw shooter
		window.draw(shootersprite);
		
		//Draw enemys
		for(int i=0;i<60;i++)
			if(enemyisalive[i]==1)
				window.draw(enemysprite[i]);
		window.display();
		
		/////////////////////////moving shooter
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			if(shootersprite.getPosition().x<=1280-70)
			{
				shootersprite.setPosition(shootersprite.getPosition().x+shooterspeed,shootersprite.getPosition().y);
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			if(shootersprite.getPosition().x>=0)
			{
				shootersprite.setPosition(shootersprite.getPosition().x-shooterspeed,shootersprite.getPosition().y);
			}
		}
		
		/////////////////////////moving enemy
		if(godown==true)
		{
			//srand(time(NULL));
			//enemyspeed=((rand()%20)+20)/100;
			if(enemymoveright==false)
			{
				enemyspeed*=-1;
				enemymoveright=true;
			}
			else
			{
				enemymoveright=false;
			}
			for(int i=0;i<60;i++)
				enemysprite[i].setPosition(enemysprite[i].getPosition().x , enemysprite[i].getPosition().y+10);
				
			godown=false;
		}
		else
		{
			for(int i=0;i<60;i++)
			{
				enemysprite[i].setPosition(enemysprite[i].getPosition().x + enemyspeed , enemysprite[i].getPosition().y);
				if(enemysprite[i].getPosition().x<0 || enemysprite[i].getPosition().x>1280-60)
					godown=true;
			}
		}
		
	}

    return 0;
}
