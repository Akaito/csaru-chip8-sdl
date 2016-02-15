// NOTE: Much of the SDL code here is taken from Lazy Foo's SDL tutorials at
// http://lazyfoo.net/tutorials/SDL/

#include <cstdlib>
#include <cstdio>
#include <ctime>

#ifdef __WIN32__
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

#include <csaru-core-cpp/csaru-core-cpp.h>
#include <chip8/chip8.hpp>

//=====================================================================
//
// Constants and helpers
//
//=====================================================================

//=====================================================================
static const int s_pixelScale   = 20;
static const int s_screenWidth  = Chip8::s_renderWidth  * s_pixelScale;
static const int s_screenHeight = Chip8::s_renderHeight * s_pixelScale;

//=====================================================================
static SDL_Window *   g_window       = nullptr;
static SDL_Renderer * g_renderer     = nullptr;

static SDL_Rect g_pixelRect = {
	0,
	0,
	s_screenWidth  / Chip8::s_renderWidth,
	s_screenHeight / Chip8::s_renderHeight
};

//=====================================================================
static bool init () {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::fprintf(
			stderr,
			"SDL failed to initialize.  %s\n",
			SDL_GetError()
		);
		return false;
	}

	// Create main window.
	g_window = SDL_CreateWindow(
		"chip8-sdl",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		s_screenWidth,
		s_screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!g_window) {
		std::fprintf(
			stderr,
			"SDL failed to create a window.  %s\n",
			SDL_GetError()
		);
		return false;
	}

	// Create renderer for main window.
	g_renderer = SDL_CreateRenderer(
		g_window,
		-1 /* rendering driver index; -1 means first available */,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!g_renderer) {
		std::fprintf(
			stderr,
			"SDL failed to create renderer.  %s\n",
			SDL_GetError()
		);
		return false;
	}

	// Set color used when clearing.
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);

	return true;

}

//=====================================================================
static void close () {

	// Destroy window
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

}


//=====================================================================
//
// main program
//
//=====================================================================

//=====================================================================
int main (int argc, const char * argv[]) {

    std::printf("  --%s--\n", argv[0]);

    if (argc < 2) {
        std::fprintf(stderr, "Missing positional param: .c8 filepath.\n");
        return 1;
    }

    // take second param to be random seed; or just use time now
    unsigned randSeed = 0;
    if (argc >= 3)
        randSeed = unsigned(atoi(argv[2]));
    if (randSeed == 0)
        randSeed = std::time(0);

    // initialize chip8
    Chip8 chip8;
    chip8.Initialize(randSeed);

    // load program
    if (!chip8.LoadProgram(argv[1])) {
        std::fprintf(stderr, "Failed to load program {%s}.\n", argv[1]);
        return 1;
    }
    std::printf("Loaded program: %s\n", argv[1]);

	// initalize SDL
	if (!init())
		return 1;

	bool readyToQuit = false;
	SDL_Event e;

	while (!readyToQuit) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: {
					readyToQuit = true;
				} break;

				case SDL_KEYDOWN: {
					switch (e.key.keysym.sym) {
						case SDLK_q:
						case SDLK_ESCAPE: readyToQuit = true; break;
					}
				} break;
			}
		} // end while SDL_PollEvent

		// emulate chip8
		{
			uint16_t pcPre = chip8.m_pc;
			chip8.EmulateCycle();

			if (pcPre == chip8.m_pc) {
				std::printf(
					"\nHalted on opcode {0x%04X} at pc {0x%04X}.\n",
					chip8.m_opcode,
					chip8.m_pc
				);
				readyToQuit = true;
			}
		}

		// sdl render
		if (chip8.m_drawFlag) {
			chip8.m_drawFlag = false;

			SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(g_renderer);

			for (unsigned y = 0; y < chip8.s_renderHeight; ++y) {
				for (unsigned x = 0; x < chip8.s_renderWidth; ++x) {
					if (chip8.m_renderOut[y * chip8.s_renderWidth + x])
						SDL_SetRenderDrawColor(g_renderer, 0xEF, 0xEF, 0xEF, 0xFF);
					else
						SDL_SetRenderDrawColor(g_renderer, 0x40, 0x40, 0x40, 0x00);

					g_pixelRect.x = x * s_pixelScale;
					g_pixelRect.y = y * s_pixelScale;
					SDL_RenderFillRect(g_renderer, &g_pixelRect);
				}
			}
		}

		// note: also using vsync as our frame limiter for now
		SDL_RenderPresent(g_renderer);
	}

	close();

	return 0;

}

