// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;
vector<vec3> stars(1000); //1000 stars in effect
int t; //Time between two frames

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void initStars();
void Update();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	initStars();
	t = SDL_GetTicks();
	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{	
	SDL_FillRect(screen, 0, 0);
	if (SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
	for (size_t s = 0; s < stars.size(); ++s) {
		float f = SCREEN_HEIGHT / 2;
		float xs = stars[s].x;
		float ys = stars[s].y;
		float zs = stars[s].z;
		
		int x = f * (xs / zs) + SCREEN_WIDTH / 2;
		int y = f * (ys / zs) + SCREEN_HEIGHT / 2;
		
		vec3 color = 0.2f * vec3(1, 1, 1) / (stars[s].z*stars[s].z);
		PutPixelSDL(screen, x, y, color);
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);
	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void initStars() {
	for (int i = 0; i < stars.size(); ++i) {
		//Number between -1 and 1
		float randomNumX = (float(rand()) / (float(RAND_MAX) / 2)) - 1;
		//Number between -1 and 1
		float randomNumY = (float(rand()) / (float(RAND_MAX) / 2)) - 1;
		//Number between 0 and 1
		float randomNumZ = float(rand()) / float(RAND_MAX);
		stars[i] = vec3(randomNumX, randomNumY, randomNumZ);
	}
}

void Update() {
	int t2 = SDL_GetTicks();
	float diffTime = float(t2 - t);
	t = t2;

	for (int s = 0; s<stars.size(); ++s)
	{
		float v = 0.001; //Speed
		stars[s].z = stars[s].z - v * diffTime;
		if (stars[s].z <= 0)
			stars[s].z += 1;
		if (stars[s].z > 1)
			stars[s].z -= 1;
	}
}