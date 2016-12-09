#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <thread>

//WINDOWS_KEY_WORD -> pentru windows

using namespace std;

void RefreshGameMap(char gameMap[20][70])
{
cout<<endl<<endl;
    for (int i = 0;i < 20;i++)
    {
        for (int j=0;j<70;j++)
        cout<<gameMap[i][j];
        cout<<endl;
    }
}

void clearGameMap(char gameMap[20][70])
{
    for (int i = 1;i < 19;i++)
    {
        for (int j=0;j<70;j++)
       gameMap[i][j] = ' ';
    }
}


char readKey()
{
   int key;
   cin>>key;
   return key;
}

void Start()
{

bool gameIsActive = true;

int posX = 5,posY = 10;

char gameMap[20][70];

 for (int i = 0;i < 20;i++)
        for (int j=0;j<70;j++)
        gameMap[i][j] = ' ';

for (int i=0;i<70;i++)
{
   gameMap[0][i] = '#';
   gameMap[19][i] = '#';
}


gameMap[posY][posX] = '@';


while(gameIsActive)
{

//thread GetKey(readKey);

if (posY < 18)
posY++;
clearGameMap(gameMap);
           gameMap[posY][posX] = '@';
            RefreshGameMap(gameMap);
char key;
cin>>key;

    if (key == 'f')
    {

       for (int i=0;i< 5 && posY > 1;i++)
       {
           posY--;
           usleep(100000);


           clearGameMap(gameMap);
           gameMap[posY][posX] = '@';
            RefreshGameMap(gameMap);
       }

        for (int i=0;i< 5 && posY < 18;i++)
       {
           posY++;
           usleep(100000);

            clearGameMap(gameMap);
           gameMap[posY][posX] = '@';
            RefreshGameMap(gameMap);
       }


    }

 RefreshGameMap(gameMap);

}



}

void Leaderboard()
{

}

int  Exit()
{

}





void Menu()
{


char menuText[10][100] = {{"Start"},{"Leaderboard"},{"Exit"}};
bool menuIsActive = true;

char key;

int menuIndex = -1,OptionsNumber = 3,menuOptionsLength[3] = { strlen(menuText[0]),strlen(menuText[1]),strlen(menuText[2])};


while(menuIsActive)
{
cin>>key;





//a = 0 etc...
if (key == 'a' || key == 's' || key == 'd')
   {

   for (int i = 0;i<OptionsNumber;i++)
       {
            menuText[i][menuOptionsLength[i] + 1] = ' ';
       }

    if (key == 'a')
    {
       menuIndex = 0;
    }
    else if (key == 's')
    {
       menuIndex = 1;
    }
    else if (key == 'd')
    {
       menuIndex = 2;
    }

 menuText[menuIndex][menuOptionsLength[menuIndex] + 1] = '#';



cout<<endl<<endl<<endl<<endl<<endl;
cout<<"                      ===> Flappy Bird <==="<<endl;
cout<<endl<<endl<<endl;

       for (int i=0;i<10;i++)
       {
       cout<<"                      ";
           for (int j=0;j<100;j++)
           cout<<menuText[i][j];
           cout<<endl;
       }
   }
   else if (key == 'w')
   {
   menuIsActive = false;

      if (menuIndex == 0)
      Start();

      if (menuIndex == 1)
      Leaderboard();

      if (menuIndex == 2)
      Exit();
   }


//loop end here
}

}




int main()
{
    Menu();
    return 0;
}
