#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <string.h>

#define numberOfImages 23

using namespace std;


int key = 0;

struct image
{
   SDL_Surface* gameImage;
   SDL_Rect offset;
   SDL_Texture* texture;
};

void InMenu(image images[],SDL_Event event,SDL_Renderer* render);
void InGame(image images[],SDL_Event event,SDL_Renderer* render);

int CreateNumber(int number,int digitsArray[])
{
   int digits = 0,copyOfNumber = number;

   if (number == 0)
   {
     digitsArray[0] = 0;
     return 1;
   }

   while(copyOfNumber)
   {
      digits++;
      copyOfNumber /= 10;
   }

   for (int i=digits-1;i>=0;i--)
   {
      digitsArray[i] = number%10;
      number /= 10;
   }

   return digits;
}

void ExitGame(image images[],SDL_Renderer* &render)
{
   for (int i=0;i<numberOfImages;i++)
   SDL_FreeSurface(images[i].gameImage);

   SDL_DestroyRenderer(render);

   SDL_Quit();
   exit (EXIT_FAILURE);
}

void ReadKeys(SDL_Event event,int gameScene)
{
    if (SDL_PollEvent(&event))
    {

    if (event.type == SDL_KEYDOWN)
    {


       switch(event.key.keysym.sym)
       {

           case SDLK_d:
           {
              key = 3;
              break;
           }


           case SDLK_w:
           {
              key = 1;
              break;
           }

            case SDLK_s:
           {
               key =  2;
              break;
           }


        case SDLK_ESCAPE:
        {
            key =  9;
           break;
        }

       }
    }


    }

}

void LoadImages(image images[],SDL_Renderer* render)
{
   images[0].gameImage = IMG_Load("TopBackground.png");
   images[0].texture = SDL_CreateTextureFromSurface(render,images[0].gameImage);

   images[1].gameImage = IMG_Load("BotBackground.png");
   images[1].texture = SDL_CreateTextureFromSurface(render,images[1].gameImage);

   images[2].gameImage = IMG_Load("Bird.png");
   images[2].texture = SDL_CreateTextureFromSurface(render,images[2].gameImage);

   images[3].gameImage = IMG_Load("Pillar.png");
   images[3].texture = SDL_CreateTextureFromSurface(render,images[3].gameImage);


   images[4].gameImage = IMG_Load("Speed_2.png");
   images[4].texture = SDL_CreateTextureFromSurface(render,images[4].gameImage);

   images[5].gameImage = IMG_Load("SpeedX2.png");
   images[5].texture = SDL_CreateTextureFromSurface(render,images[5].gameImage);

   images[6].gameImage = IMG_Load("Invincibility.png");
   images[6].texture = SDL_CreateTextureFromSurface(render,images[6].gameImage);

   images[7].gameImage = IMG_Load("Menu.png");
   images[7].texture = SDL_CreateTextureFromSurface(render,images[7].gameImage);

   images[8].gameImage = IMG_Load("Arrow.png");
   images[8].texture = SDL_CreateTextureFromSurface(render,images[8].gameImage);

   images[9].gameImage = IMG_Load("GameOver.png");
   images[9].texture = SDL_CreateTextureFromSurface(render,images[9].gameImage);

   images[10].gameImage = IMG_Load("0.png");
   images[10].texture = SDL_CreateTextureFromSurface(render,images[10].gameImage);

   images[11].gameImage = IMG_Load("1.png");
   images[11].texture = SDL_CreateTextureFromSurface(render,images[11].gameImage);

   images[12].gameImage = IMG_Load("2.png");
   images[12].texture = SDL_CreateTextureFromSurface(render,images[12].gameImage);

   images[13].gameImage = IMG_Load("3.png");
   images[13].texture = SDL_CreateTextureFromSurface(render,images[13].gameImage);

   images[14].gameImage = IMG_Load("4.png");
   images[14].texture = SDL_CreateTextureFromSurface(render,images[14].gameImage);

   images[15].gameImage = IMG_Load("5.png");
   images[15].texture = SDL_CreateTextureFromSurface(render,images[15].gameImage);

   images[16].gameImage = IMG_Load("6.png");
   images[16].texture = SDL_CreateTextureFromSurface(render,images[16].gameImage);

   images[17].gameImage = IMG_Load("7.png");
   images[17].texture = SDL_CreateTextureFromSurface(render,images[17].gameImage);

   images[18].gameImage = IMG_Load("8.png");
   images[18].texture = SDL_CreateTextureFromSurface(render,images[18].gameImage);

   images[19].gameImage = IMG_Load("9.png");
   images[19].texture = SDL_CreateTextureFromSurface(render,images[19].gameImage);

   images[20].gameImage = IMG_Load("LeaderboardText.png");
   images[20].texture = SDL_CreateTextureFromSurface(render,images[20].gameImage);

   images[21].gameImage = IMG_Load("SimpleMenu.png");
   images[21].texture = SDL_CreateTextureFromSurface(render,images[21].gameImage);

   images[22].gameImage = IMG_Load("BiggestScore.png");
   images[22].texture = SDL_CreateTextureFromSurface(render,images[22].gameImage);

}



void FirstTimeSettings(image images[],SDL_Renderer* &render)
{
SDL_Init(SDL_INIT_EVERYTHING);

SDL_Window* screen = SDL_CreateWindow("Flappy Bird",300,200,700,400,SDL_WINDOW_SHOWN);

     render = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);
     SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

   for (int i = 0;i < numberOfImages;i++)
   {
      images[i].gameImage = NULL;
      images[i].offset.x = 0;
      images[i].offset.y = 0;
      images[i].texture = NULL;
   }
}

SDL_Rect nullRect;


int CheckCollision(image images[],SDL_Rect pillars[],SDL_Rect powerUp = nullRect)
{
     for (int i=0;i<6;i++)
     {

          if (images[2].offset.x+50 > pillars[i].x && images[2].offset.x < pillars[i].x+100)
         {
          cout<<"Y "<<pillars[i].x<<" "<<pillars[i].y<<" Bird "<<images[2].offset.x<<" "<<images[2].offset.y<<endl;
             if (i%2==0)
             if(images[2].offset.y < pillars[i].y+250)
             return 1;

             if (i%2!=0)
             {

             if(images[2].offset.y+40 > pillars[i].y)
             return 1;
             }


         }

           ///////////////// Speed / 2 /////////

          if ((images[2].offset.x+40 > powerUp.x) && (images[2].offset.x < powerUp.x+100) && (images[2].offset.y < powerUp.y+30) && (images[2].offset.y+40 > powerUp.y))
         {
             return 2;
         }

         /////////////// Add score ////////////////////

           if (images[2].offset.x > pillars[i].x && images[2].offset.x < pillars[i].x + 100)
         {

             if (i%2==0 || i == 0)
             if(images[2].offset.y > pillars[i].y+250)
             return 3;

             if (i%2==1)
             if(images[2].offset.y+40 < pillars[i].y)
             return 3;


             return 3;
         }


         ////////////////// Make getScore = true  //////////////

         if (images[2].offset.x > pillars[i].x + 100)
         {
            return 4;
         }


     }

}

void InGame(image images[],SDL_Event event,SDL_Renderer* render)
{



SDL_Rect GameOverPos;
GameOverPos.x = 175;
GameOverPos.y = 100;
GameOverPos.w = 300;
GameOverPos.h = 100;


SDL_Rect TopBackgroundPosition1;
TopBackgroundPosition1.x = 0;
TopBackgroundPosition1.y = 0;
TopBackgroundPosition1.w = 700;
TopBackgroundPosition1.h = 400;

SDL_Rect TopBackgroundPosition2;
TopBackgroundPosition2.x = 460;
TopBackgroundPosition2.y = 0;
TopBackgroundPosition2.w = 700;
TopBackgroundPosition2.h = 400;

SDL_Rect TopBackgroundPosition3;
TopBackgroundPosition3.x = 920;
TopBackgroundPosition3.y = 0;
TopBackgroundPosition3.w = 700;
TopBackgroundPosition3.h = 400;

////////////////

SDL_Rect BotBackgroundPosition1;
BotBackgroundPosition1.x = 0;
BotBackgroundPosition1.y = 350;
BotBackgroundPosition1.w = 700;
BotBackgroundPosition1.h = 100;

SDL_Rect BotBackgroundPosition2;
BotBackgroundPosition2.x = 460;
BotBackgroundPosition2.y = 350;
BotBackgroundPosition2.w = 700;
BotBackgroundPosition2.h = 100;

SDL_Rect BotBackgroundPosition3;
BotBackgroundPosition3.x = 920;
BotBackgroundPosition3.y = 350;
BotBackgroundPosition3.w = 700;
BotBackgroundPosition3.h = 100;


///////////////

SDL_Rect TopPillarPosition;
TopPillarPosition.x = 500;
TopPillarPosition.y = -200;
TopPillarPosition.w = 100;
TopPillarPosition.h = 250;

SDL_Rect BotPillarPosition;
BotPillarPosition.x = 500;
BotPillarPosition.y = 200;
BotPillarPosition.w = 100;
BotPillarPosition.h = 250;


//////////////////////////////////

SDL_Rect TopPillarPosition2;
TopPillarPosition2.x = 800;
TopPillarPosition2.y = -200;
TopPillarPosition2.w = 100;
TopPillarPosition2.h = 250;

SDL_Rect BotPillarPosition2;
BotPillarPosition2.x = 800;
BotPillarPosition2.y = 200;
BotPillarPosition2.w = 100;
BotPillarPosition2.h = 250;

////////////////////////

SDL_Rect TopPillarPosition3;
TopPillarPosition3.x = 1100;
TopPillarPosition3.y = -200;
TopPillarPosition3.w = 100;
TopPillarPosition3.h = 250;

SDL_Rect BotPillarPosition3;
BotPillarPosition3.x = 1100;
BotPillarPosition3.y = 200;
BotPillarPosition3.w = 100;
BotPillarPosition3.h = 250;

////////////////

SDL_Rect PowerUpPos;
PowerUpPos.x = 1100;
PowerUpPos.y = 150;
PowerUpPos.w = 100;
PowerUpPos.h = 30;

//////////////////

SDL_Rect InGameScore;
InGameScore.x = 20;
InGameScore.y = 20;
InGameScore.w = 50;
InGameScore.h = 80;



  images[2].offset.x = 100;
  images[2].offset.y = 0;
  images[2].offset.w = 50;
  images[2].offset.h = 40;

   int jumpForce = 0;
   int ResetBirdAngle = 0;

   int BirdRotationAngle = 0;

   bool alive = true,bugFixer = false,invincible = false;
   int seconds = 0,timer = 0,powerUpIndex = -1,speed = 1,delayTime = 10;

   int invincibleStopTime = 0;
   int lastRandom = -1;
   int lock = 0;

   bool getScore = true;
   int score = 0;


   while(1)
   {

   if (invincibleStopTime == seconds && seconds > 1)
   {
      invincible = false;
      invincibleStopTime = 0;
      powerUpIndex = -1;
   }


   if (bugFixer && seconds % 5 != 0)
   bugFixer = false;

   if (alive)
   {
   int timerLimit = 100 / (delayTime / 10);

   timer++;
   if (timer >= timerLimit)
   {
      timer = 0;
      seconds++;
      cout<<seconds<<endl;
   }

   if (seconds % 5 == 0 && powerUpIndex == -1 && bugFixer == false && seconds != 0)
   {

   PowerUpPos.x = 1100;

   int x = rand()%3+4;

   while(x == lastRandom)
   {
   x = rand()%3+4;
   }
      powerUpIndex = x;

      lastRandom = x;
   }

       TopBackgroundPosition1.x -= speed;
       TopBackgroundPosition2.x -= speed;
       TopBackgroundPosition3.x -= speed;

       BotBackgroundPosition1.x -= speed;
       BotBackgroundPosition2.x -= speed;
       BotBackgroundPosition3.x -= speed;

       TopPillarPosition.x -= speed;
       BotPillarPosition.x -= speed;

       TopPillarPosition2.x -= speed;
       BotPillarPosition2.x -= speed;

       TopPillarPosition3.x -= speed;
       BotPillarPosition3.x -= speed;
   }


SDL_Rect pillars[6] = {
TopPillarPosition,BotPillarPosition,
TopPillarPosition2,BotPillarPosition2,
TopPillarPosition3,BotPillarPosition3
};

if (CheckCollision(images,pillars) == 1 && alive == true && invincible == false)
{
   alive = false;
}


if (CheckCollision(images,pillars) == 3 && getScore == true)
{
   getScore = false;
   score++;
}

if (CheckCollision(images,pillars) == 4 && getScore == false)
{
   getScore = true;
}


if (CheckCollision(images,pillars,PowerUpPos) == 2 && powerUpIndex != -1)
{

   if (powerUpIndex == 4)
   {
     delayTime *= 2;
     cout<<"Delay "<<delayTime<<endl;
   }

   if (powerUpIndex == 5)
   {
      speed *= 2;
      cout<<"Speed "<<speed<<endl;
   }

   if (powerUpIndex == 6)
   {
     invincible = true;
     invincibleStopTime = seconds + 10;
   }
  powerUpIndex = -1;


  if (seconds % 5 == 0)
  {
     bugFixer = true;
  }
}





  if (jumpForce > 0)
  jumpForce--;

  images[2].offset.y-=jumpForce;



if (images[2].offset.y < 310)
{
   images[2].offset.y += 2;
}
else if (images[2].offset.y >= 310)
{
   alive = false;
}


ReadKeys(event,1);
       if (key == 3 && images[2].offset.y > 30 && alive)
       {
       key = 0;
          jumpForce += 15;
           BirdRotationAngle = -45;
       }

       if (key == 9)
       {
         alive = false;
         key = 0;
         InMenu(images,event,render);
       }

       if (ResetBirdAngle < 10 && BirdRotationAngle != 0)
       {
          ResetBirdAngle++;
       }
       else if (ResetBirdAngle >= 10 && BirdRotationAngle != 0)
       {
          ResetBirdAngle = 0;
          BirdRotationAngle = 0;
       }


if (alive == true)
      SDL_RenderClear( render );

      SDL_RenderCopy( render, images[0].texture, NULL, &TopBackgroundPosition1);
      SDL_RenderCopy( render, images[0].texture, NULL, &TopBackgroundPosition2);
      SDL_RenderCopy( render, images[0].texture, NULL, &TopBackgroundPosition3);

      SDL_RenderCopyEx( render, images[3].texture, NULL, &TopPillarPosition,180,NULL,SDL_FLIP_NONE );
      SDL_RenderCopyEx( render, images[3].texture, NULL, &BotPillarPosition,0,NULL,SDL_FLIP_NONE );

      SDL_RenderCopyEx( render, images[3].texture, NULL, &TopPillarPosition2,180,NULL,SDL_FLIP_NONE );
      SDL_RenderCopyEx( render, images[3].texture, NULL, &BotPillarPosition2,0,NULL,SDL_FLIP_NONE );

      SDL_RenderCopyEx( render, images[3].texture, NULL, &TopPillarPosition3,180,NULL,SDL_FLIP_NONE );
      SDL_RenderCopyEx( render, images[3].texture, NULL, &BotPillarPosition3,0,NULL,SDL_FLIP_NONE );


      SDL_RenderCopy( render, images[1].texture, NULL, &BotBackgroundPosition1);
      SDL_RenderCopy( render, images[1].texture, NULL, &BotBackgroundPosition2);
      SDL_RenderCopy( render, images[1].texture, NULL, &BotBackgroundPosition3);

      if (alive && powerUpIndex != -1)
      {
          PowerUpPos.x -= speed;
          images[powerUpIndex].offset = PowerUpPos;
          SDL_RenderCopy( render, images[powerUpIndex].texture, NULL, &PowerUpPos);
      }

      if (TopBackgroundPosition1.x < -700)
      {
         TopBackgroundPosition1.x += 1400;
         BotBackgroundPosition1.x += 1400;
      }



      if (TopBackgroundPosition2.x < -700)
      {
         TopBackgroundPosition2.x += 1400;
         BotBackgroundPosition2.x += 1400;
      }


      if (TopBackgroundPosition3.x < -700)
      {
         TopBackgroundPosition3.x += 1400;
         BotBackgroundPosition3.x += 1400;
      }

      if (TopPillarPosition.x < -100)
      {
           TopPillarPosition.x += 900;
           BotPillarPosition.x += 900;

           BotPillarPosition.y = rand() %200 + 150;
           TopPillarPosition.y = BotPillarPosition.y - 400;
      }


      if (TopPillarPosition2.x < -100)
      {
           TopPillarPosition2.x += 900;
           BotPillarPosition2.x += 900;

           BotPillarPosition2.y = rand() %200 + 150;
           TopPillarPosition2.y = BotPillarPosition2.y - 400;
      }

      if (TopPillarPosition3.x < -100)
      {
           TopPillarPosition3.x += 900;
           BotPillarPosition3.x += 900;

           BotPillarPosition3.y = rand() %200 + 150;
           TopPillarPosition3.y = BotPillarPosition3.y - 400;
      }


      SDL_RenderCopyEx( render, images[2].texture, NULL, &images[2].offset,BirdRotationAngle,NULL,SDL_FLIP_NONE );

      int numberOfDigits = 0, arrayOfDigits[100];
      numberOfDigits = CreateNumber(score,arrayOfDigits);

      InGameScore.x = 20;

      for (int i=0;i<numberOfDigits;i++)
      {
          SDL_RenderCopy(render, images[arrayOfDigits[i]+10].texture, NULL, &InGameScore);
          InGameScore.x += 50;
      }


      if (alive == false)
      {

         if (lock == 0)
         {

         int maxScore=0,numberOfGames=0,games[1000];


         fstream file;
         file.open ("Data.txt");

         file>>maxScore>>numberOfGames;

         for (int i=numberOfGames;i>=1;i--)
         {
            file>>games[i];
         }

         file.seekg(ios::beg);

            lock = 1;
            numberOfGames++;


            if (score > maxScore)
            file<<score<<endl;
            else
            file<<maxScore<<endl;

            file<<numberOfGames<<endl;

            games[numberOfGames] = seconds;

            for (int i=numberOfGames;i>=1;i--)
            {
               file<<games[i]<<endl;
            }


            file.close();

         }



      SDL_RenderCopy(render,images[9].texture,NULL,&GameOverPos);
      SDL_RenderPresent(render);
      SDL_Delay(2000);



      InMenu(images,event,render);


      //ExitGame(images,render);
      }



      if (alive == true)
         SDL_RenderPresent(render);

      SDL_Delay(delayTime);

   }

}

void RenderScore(image images[],SDL_Event event,SDL_Renderer* render,SDL_Rect leaderboardRects[])
{

    fstream file;
    file.open ("Data.txt");

    int maxScore = 0,numberOfGames = 0,time;
    int arrayOfDigits[100],numberOfDigits;

     file>>maxScore>>numberOfGames;

     SDL_RenderClear(render);

     SDL_RenderCopy(render,images[21].texture,NULL,&leaderboardRects[3]);

     SDL_RenderCopy(render,images[22].texture,NULL,&leaderboardRects[4]);

      numberOfDigits = CreateNumber(maxScore,arrayOfDigits);

      for (int i=0;i<numberOfDigits;i++)
         {
            SDL_RenderCopy(render,images[arrayOfDigits[i]+10].texture,NULL,&leaderboardRects[5]);
            leaderboardRects[5].x += 10;
         }

     for (int i=numberOfGames;i>=1;i--)
     {
         SDL_RenderCopy(render,images[20].texture,NULL,&leaderboardRects[0]);
         leaderboardRects[0].y += 50;



         leaderboardRects[1].x = 60;

         numberOfDigits = CreateNumber(i,arrayOfDigits);

         for (int j=0;j<numberOfDigits;j++)
         {
            SDL_RenderCopy(render,images[arrayOfDigits[j]+10].texture,NULL,&leaderboardRects[1]);
            leaderboardRects[1].x += 10;
         }
         leaderboardRects[1].y += 50;

         int time;
         file>>time;

         numberOfDigits = CreateNumber(time,arrayOfDigits);

         leaderboardRects[2].x = 160;

         for (int j=0;j<numberOfDigits;j++)
         {
            SDL_RenderCopy(render,images[arrayOfDigits[j]+10].texture,NULL,&leaderboardRects[2]);
            leaderboardRects[2].x += 10;
         }
         leaderboardRects[2].y += 50;

     }
file.close();
     SDL_RenderPresent(render);
}

void InLeaderboard(image images[],SDL_Event event,SDL_Renderer* render)
{

SDL_Rect textPosition;
textPosition.x = 10;
textPosition.y = 50;
textPosition.w = 150;
textPosition.h = 30;

SDL_Rect gameID;
gameID.x = 60;
gameID.y = 55;
gameID.w = 10;
gameID.h = 20;

SDL_Rect gameTime;
gameTime.x = 160;
gameTime.y = 55;
gameTime.w = 10;
gameTime.h = 20;

SDL_Rect MenuPosition;
MenuPosition.x = 0;
MenuPosition.y = 0;
MenuPosition.w = 700;
MenuPosition.h = 400;

SDL_Rect MaxScoreTextPosition;
MaxScoreTextPosition.x = 5;
MaxScoreTextPosition.y = 5;
MaxScoreTextPosition.w = 200;
MaxScoreTextPosition.h = 30;

SDL_Rect MaxScorePosition;
MaxScorePosition.x = 210;
MaxScorePosition.y = 15;
MaxScorePosition.w = 10;
MaxScorePosition.h = 20;


SDL_Rect leaderboardRects[6] = {textPosition,gameID,gameTime,MenuPosition,MaxScoreTextPosition,MaxScorePosition};
RenderScore(images,event,render,leaderboardRects);

    bool active = true;

    fstream file;
    file.open ("Data.txt");

    int maxScore,numberOfgames;

    file>>maxScore>>numberOfgames;
                                                                                                                                                          //Ungurean Alexandru Florin
    file.close();

 int listLimit1 = 50,listLimit2 = (numberOfgames-8) * 50 * -1;

   while(active)
   {

     ReadKeys(event,2);

     if (key == 9)
     {
        active = false;

        key = 0;
        InMenu(images,event,render);
     }

     if (key == 1 &&  textPosition.y < listLimit1)
     {
        key = 0;
        textPosition.y += 50;
        gameID.y += 50;
        gameTime.y += 50;
        MaxScoreTextPosition.y += 50;
        MaxScorePosition.y += 50;

        SDL_Rect leaderboardRects[6] = {textPosition,gameID,gameTime,MenuPosition,MaxScoreTextPosition,MaxScorePosition};
        RenderScore(images,event,render,leaderboardRects);
     }

     if (key == 2 && textPosition.y > listLimit2)
     {
        key = 0;
        textPosition.y -= 50;
        gameID.y -= 50;
        gameTime.y -= 50;
        MaxScoreTextPosition.y -= 50;
        MaxScorePosition.y -= 50;

        SDL_Rect leaderboardRects[6] = {textPosition,gameID,gameTime,MenuPosition,MaxScoreTextPosition,MaxScorePosition};
        RenderScore(images,event,render,leaderboardRects);
     }


   }

}


void InMenu(image images[],SDL_Event event,SDL_Renderer* render)
{

SDL_Rect MenuPosition;
MenuPosition.x = 0;
MenuPosition.y = 0;
MenuPosition.w = 700;
MenuPosition.h = 400;

SDL_Rect ArrowPosition;
ArrowPosition.x = 100;
ArrowPosition.y = 100;
ArrowPosition.w = 70;
ArrowPosition.h = 100;



int ArrowPositionIndex = 0;
bool canSwich = true;
bool active = true;



   while(active)
   {
   canSwich = true;
   SDL_RenderClear(render);

   SDL_RenderCopy(render,images[7].texture,NULL,&MenuPosition);

   ReadKeys(event,0);

      if (key == 9)
          ExitGame(images,render);


      if (key == 1 && ArrowPositionIndex > 0 && canSwich)
      {
      key = 0;
         ArrowPositionIndex--;
         canSwich = false;
      }

      if (key == 2 && ArrowPositionIndex < 2 && canSwich)
      {
      key = 0;
         ArrowPositionIndex++;
         canSwich = false;
      }

      if (key == 3)
      {
        key = 0;

        if (ArrowPositionIndex == 0)
        {
           active = false;
           InGame(images,event,render);
        }

        if (ArrowPositionIndex == 1)
        {
           active = false;
           InLeaderboard(images,event,render);
        }

        if (ArrowPositionIndex == 2)
        {
        active = false;
           ExitGame(images,render);
        }


      }

      if (ArrowPositionIndex == 0)
      {
         ArrowPosition.x = 160;
         ArrowPosition.y = 150;
         ArrowPosition.w = 100;
         ArrowPosition.h = 70;
      }

       if (ArrowPositionIndex == 1)
      {
         ArrowPosition.x = 80;
         ArrowPosition.y = 240;
         ArrowPosition.w = 100;
         ArrowPosition.h = 70;
      }

       if (ArrowPositionIndex == 2)
      {
         ArrowPosition.x = 190;
         ArrowPosition.y = 320;
         ArrowPosition.w = 100;
         ArrowPosition.h = 70;
      }

       SDL_RenderCopy(render,images[8].texture,NULL,&ArrowPosition);

      SDL_RenderPresent(render);

      SDL_Delay(10);
   }

}



int main(int argc,  char** argv)
{

// 0 = Menu, 1 = Game, 2 = Leaderboard

nullRect.x = 0;
nullRect.y = 0;
nullRect.w = 0;
nullRect.h = 0;

image images[numberOfImages];
SDL_Event event;
SDL_Renderer* render = NULL;

FirstTimeSettings(images,render);

LoadImages(images,render);

InMenu(images,event,render);

    return 0;
}
