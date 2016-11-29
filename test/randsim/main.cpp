#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

// Setup
bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();

// Our new function for setting uo SDL_TTF
bool SetupTTF(const std::string &fontName);
SDL_Texture *SurfaceToTexture(SDL_Surface *surf);
void CreateTextTextures();

// Update ( happens every frame )
void Render();
void RunSim();

// Stuff for text rendering
TTF_Font *font;
SDL_Color textColor = {255, 255, 255, 255}; // white
SDL_Color backgroundColor = {0, 0, 0, 255}; // black

SDL_Texture *solidTexture;
SDL_Texture *blendedTexture;
SDL_Texture *shadedTexture;

SDL_Rect solidRect;
SDL_Rect blendedRect;
SDL_Rect shadedRect;

SDL_Rect windowRect = {900, 300, 400, 400};
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *args[]) {
    if (!InitEverything())
        return -1;

    RunSim();

    
    // Clean up
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void RunSim() {
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Render();
    }
}

void Render() {
    // Clear the window and make it all red
    SDL_RenderClear(renderer);

    // Render our text objects ( like normal )
    SDL_RenderCopy(renderer, solidTexture, nullptr, &solidRect);
    SDL_RenderCopy(renderer, blendedTexture, nullptr, &blendedRect);
    SDL_RenderCopy(renderer, shadedTexture, nullptr, &shadedRect);

    // Render the changes above
    SDL_RenderPresent(renderer);
}

// Initialization ++
// ==================================================================
bool SetupTTF(const std::string &fontName) {
    // SDL2_TTF needs to be initialized just like SDL2
    if (TTF_Init() == -1) {
        std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
        return false;
    }

    // Load our fonts, with a huge size
    std::string path = std::string(SDL_GetBasePath()) + fontName;
    font = TTF_OpenFont(path.c_str(), 90);

    // Error check
    if (font == nullptr) {
        std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void CreateTextTextures() {
    SDL_Surface *solid = TTF_RenderText_Solid(font, "solid", textColor);
    solidTexture = SurfaceToTexture(solid);

    SDL_QueryTexture(solidTexture, NULL, NULL, &solidRect.w, &solidRect.h);
    solidRect.x = 0;
    solidRect.y = 0;

    SDL_Surface *blended = TTF_RenderText_Blended(font, "blended", textColor);
    blendedTexture = SurfaceToTexture(blended);

    SDL_QueryTexture(blendedTexture, NULL, NULL, &blendedRect.w, &blendedRect.h);
    blendedRect.x = 0;
    blendedRect.y = solidRect.y + solidRect.h + 20;

    SDL_Surface *shaded = TTF_RenderText_Shaded(font, "shaded", textColor, backgroundColor);
    shadedTexture = SurfaceToTexture(shaded);

    SDL_QueryTexture(shadedTexture, NULL, NULL, &shadedRect.w, &shadedRect.h);
    shadedRect.x = 0;
    shadedRect.y = blendedRect.y + blendedRect.h + 20;
}

// Convert an SDL_Surface to SDL_Texture. We've done this before, so I'll keep it short
SDL_Texture *SurfaceToTexture(SDL_Surface *surf) {
    SDL_Texture *text;

    text = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);

    return text;
}

bool InitEverything() {
    if (!InitSDL())
        return false;

    if (!CreateWindow())
        return false;

    if (!CreateRenderer())
        return false;

    SetupRenderer();

    if (!SetupTTF("fonts/Ubuntu-C.ttf"))
        return false;

    CreateTextTextures();

    return true;
}

bool InitSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool CreateWindow() {
    window = SDL_CreateWindow("randsim", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0);

    if (window == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }

    return true;
}

bool CreateRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Failed to create renderer : " << SDL_GetError();
        return false;
    }

    return true;
}

void SetupRenderer() {
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, windowRect.w, windowRect.h);

    // Set color of renderer to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}
