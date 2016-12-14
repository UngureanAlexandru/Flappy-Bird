#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define numberOfImages 4

using namespace std;

struct image
{
   SDL_Surface* gameImage;
   SDL_Rect offset;
   SDL_Texture* texture;
};

void ExitGame(image images[],SDL_Renderer* &render)
{
   for (int i=0;i<numberOfImages;i++)
   SDL_FreeSurface(images[i].gameImage);

   SDL_DestroyRenderer(render);

   SDL_Quit();
   IMG_Quit();
}

int ReadKeys(SDL_Event event,int gameScene)
{
    if (SDL_PollEvent(&event))
    {

    if (event.type == SDL_KEYDOWN)
    {
       if (event.key.keysym.sym == SDLK_SPACE && gameScene == 1)
        {
           return 3;
        }

         if (event.key.keysym.sym == SDLK_ESCAPE)
        {
           return 9;
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
}



void FirstTimeSettings(image images[],SDL_Renderer* &render)
{
SDL_Init(SDL_INIT_EVERYTHING);

SDL_Window* screen = SDL_CreateWindow("Flappy Bird",0,0,700,400,SDL_WINDOW_SHOWN);

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


void InGame(image images[],SDL_Event event,SDL_Renderer* render)
{

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

  images[2].offset.x = 100;
  images[2].offset.y = 0;
  images[2].offset.w = 100;
  images[2].offset.h = 70;

   int jumpForce = 0;
   int ResetBirdAngle = 0;

   int BirdRotationAngle = 0;

   while(1)
   {
       TopBackgroundPosition1.x--;
       TopBackgroundPosition2.x--;
       TopBackgroundPosition3.x--;

       BotBackgroundPosition1.x--;
       BotBackgroundPosition2.x--;
       BotBackgroundPosition3.x--;

       TopPillarPosition.x--;
       BotPillarPosition.x--;

       TopPillarPosition2.x--;
       BotPillarPosition2.x--;

       TopPillarPosition3.x--;
       BotPillarPosition3.x--;

  if (jumpForce > 0)
  jumpForce--;

  images[2].offset.y-=jumpForce;



if (images[2].offset.y < 310)
{
   images[2].offset.y += 2;
}
else
{
   cout<<"Ai pierdut"<<endl;
}



       if (ReadKeys(event,1) == 3 && images[2].offset.y > 50)
       {
          jumpForce += 15;
           BirdRotationAngle = -45;
       }

       if (ReadKeys(event,1) == 9)
       {
          //ExitGame(images,render);
           jumpForce += 30;
           BirdRotationAngle = -45;
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


      SDL_RenderPresent( render );

      SDL_Delay(10);
   }

}

void InLeaderboard()
{
}


void InMenu()
{

}



int main()
{

// 0 = Menu, 1 = Game, 2 = Leaderboard
int gameScene = 0;

image images[numberOfImages];
SDL_Event event;
SDL_Renderer* render = NULL;

FirstTimeSettings(images,render);

LoadImages(images,render);

InGame(images,event,render);

    return 0;
}
