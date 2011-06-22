// Boost
#include <boost/asio.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

//#define NO_STDIO_REDIRECT
#define _SCL_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE

//#include <stdlib.h>
#include <csignal>
#include <SDL.h>
#include <SDL_main.h>

#include <adobe/any_regular.hpp>
#include <adobe/array.hpp>
#include <adobe/dictionary.hpp>
#include <adobe/eve.hpp>
#include <adobe/eve_evaluate.hpp>
#include <adobe/eve_parser.hpp>
#include <adobe/iomanip_asl_cel.hpp>
#include <adobe/name.hpp>

#include "filters/audio_encoder/audio_encoder.h"
#include "filters/video_encoder/video_encoder.h"
#include "filters/multiplexer/multiplexer.h"
#include "filters/transmitter/transmitter.h"


using namespace std;
using boost::asio::ip::tcp;
using namespace boost::posix_time;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32
#define SCREEN_LIMIT_HEIGHT SCREEN_HEIGHT - SPRITE_SIZE
#define SCREEN_LIMIT_WIDTH SCREEN_WIDTH - SPRITE_SIZE


SDL_Surface *screen, *back, *packman, *sprite;


SDL_Rect Sprite, src;

int pos = 0, colorkey;

std::string container;
std::string server;
int stream_bitrate;
std::string username;

video_encoder* video_encoder_block;
multiplexer* multiplexer_block;
transmitter* transmitter_block;

AVFrame* frame;
AVFrame* readyFrame;
URLContext* StreamToUrl;

void LoadImages()
{
	back = SDL_LoadBMP("assets/bg_640x480.bmp");
	packman = SDL_LoadBMP("assets/sprite.bmp");
	sprite = SDL_DisplayFormat(packman);
	SDL_FreeSurface(packman);
	/* setup sprite colorkey and turn on RLE */
	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

void DrawIMG(SDL_Surface *img, int x, int y)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(img, NULL,screen, &rect);
	SDL_BlitSurface(sprite, &Sprite, screen, &src);
}

void DrawScene()
{
	DrawIMG(back, 0, 0);
	if(pos == 0) //RIGHT
	{
		Sprite.x +=1;
	}

	if(pos == 1) // LEFT
	{
		Sprite.x -=1;
	}

	if(pos == 2) //UP
	{
		Sprite.y -= 1;
	}
	if(pos == 3) // DOWN
	{
		Sprite.y += 1;
	}

	if(Sprite.y > SCREEN_LIMIT_HEIGHT)
	{
		Sprite.y = SCREEN_LIMIT_HEIGHT - 3;
	}
	if(Sprite.x > SCREEN_LIMIT_WIDTH)
	{
		Sprite.x = SCREEN_LIMIT_WIDTH - 3;
	}

	/* draw the sprite */
	SDL_BlitSurface(back, NULL, screen, &src);
	SDL_BlitSurface(sprite, NULL, screen, &Sprite);
	/* update the screen */

	SDL_Flip(screen);
}
int main(int argc, char *argv[])
{
	Uint8 *keys;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "error! no SDL!" << endl;
		cin.get();
		return 1;
	}
	SDL_WM_SetCaption("SDL Move", "SDL Move");
	screen = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_EnableKeyRepeat(100, 100);

	if(screen == NULL)
	{
		cout << "error! no screen found!" << endl;
		cin.get();
		return 1;
	}

	LoadImages();

	Sprite.x = 150;
	Sprite.y  = 120;

	src.x = 0;
	src.y = 0;
	src.w = SPRITE_SIZE;
	src.h = SPRITE_SIZE;

	bool done = false;
	while(done == false)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if((event.type == SDL_QUIT)||(event.key.keysym.sym == SDLK_q)||(event.key.keysym.sym == SDLK_ESCAPE)) done = true;
		}

		keys = SDL_GetKeyState(NULL);
		if(keys[SDLK_RIGHT]){ pos = 0;}
		else if(keys[SDLK_LEFT]) {pos = 1;}
		else if(keys[SDLK_UP]) {pos = 2;}
		else if(keys[SDLK_DOWN]) {pos = 3;}
		else {pos = 4;}


		DrawScene();
		SDL_UpdateRect(screen,0,0,0,0);
	}
	/* clean up */
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(back);
	SDL_Quit();

	return 0;
}