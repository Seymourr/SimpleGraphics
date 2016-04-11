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
vec3 topLeft(1, 0, 0); // red
vec3 topRight(0, 0, 1); // blue
vec3 bottomLeft(1, 1, 0); // yellow
vec3 bottomRight(0, 1, 0); // green
vector<vec3> leftSide(SCREEN_HEIGHT);
vector<vec3> rightSide(SCREEN_HEIGHT);

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Interpolate(float a, float b, vector<float>& result);
void Interpolate(vec3 a, vec3 b, vector<vec3> & result);

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );

	Interpolate(topLeft, bottomLeft, leftSide);
	Interpolate(topRight, bottomRight, rightSide);

	while( NoQuitMessageSDL() )
	{
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{	

	if (SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		vector<vec3> rowColor(SCREEN_WIDTH);
		Interpolate(leftSide[y], rightSide[y], rowColor);

		for( int x=0; x < rowColor.size(); ++x )
		{
			vec3 color = rowColor[x];
			
			PutPixelSDL( screen, x, y, color );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void Interpolate(float a, float b, vector<float>& result) {
	if (result.size() == 0) {
		return;
	}

	if (result.size() == 1) {
		result[0] = a; //Correct?
		return;
	}

	result[0] = a;
	result[result.size() - 1] = b;

	for (int i = 1; i < result.size() - 1; ++i) {
		float step = (float)i / (result.size() - 1);
		step *= (b - a);
		result[i] = a + step;
	}
}	

void Interpolate(vec3 a, vec3 b, vector<vec3> & result) {
	if (result.size() == 0) return;
	if (result.size() == 1) {
		result[0] = a; //Correct??
		return;
	}

	result[0] = a;
	result[result.size() - 1] = b;

	for (int i = 1; i < result.size() - 1; ++i) {
		float step = (float)i / (result.size() - 1);
		vec3 stepV = (b - a) * step;
		result[i] = a + stepV;
	}
}