#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Car Cluster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 520, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load a PNG image into a texture
    SDL_Texture* cluster = IMG_LoadTexture(renderer, ".\\assets\\cluster.png");
    if (!cluster) {
        printf("Failed to load texture: %s\n", IMG_GetError());
    }

    SDL_Texture* needle = IMG_LoadTexture(renderer, ".\\assets\\needle.png");
    if (!needle) {
        printf("Failed to load texture: %s\n", IMG_GetError());
    }

    // Needle position and size
    SDL_Rect rpmNeedle; // This represents the position of the needle
   // rpmNeedle.x = 474 - 75;  // Adjust X position (centered horizontally)
   // rpmNeedle.y = 347 - 75;  // Adjust Y position (centered vertically)
   // rpmNeedle.w = 150;  // Width of the needle image
    //rpmNeedle.h = 150;  // Height of the needle image



  //Mouse Position: (473, 342)
    rpmNeedle.x = 474 - 115;  // X position
    rpmNeedle.y = 347 - 40;  // Y position
    rpmNeedle.w = 150;  // Width
    rpmNeedle.h = 80;  // Height


    // Define the center of rotation for the needle
    SDL_Point needleCenter;
    needleCenter.x = rpmNeedle.w / 2;  // Center horizontally
    needleCenter.y = rpmNeedle.h;       // Set to the bottom of the needle (height)

    int angle = 0;  // Initial rotation angle

    int mouseX, mouseY;

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

        // Print mouse position (for debugging purposes)
        std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ") \n";


        std::this_thread::sleep_for(50ms); // For debugging purposes

        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the cluster background
        SDL_RenderCopy(renderer, cluster, NULL, NULL);

        // Render the rotating needle with the specified center of rotation
        SDL_RenderCopyEx(renderer, needle, NULL, &rpmNeedle, angle, &needleCenter, SDL_FLIP_NONE);

        // Present the updated renderer
        SDL_RenderPresent(renderer);

        // Increment the angle (for testing rotation)
        angle += 1;
        if (angle >= 360) {
            angle = 0;
        }
    }

    // Cleanup
    SDL_DestroyTexture(cluster);
    SDL_DestroyTexture(needle);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
