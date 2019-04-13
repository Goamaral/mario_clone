#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Surface {
  private:
  public:
    Surface(/* args */);
    ~Surface();

    static SDL_Surface* loadOptimized(std::string, SDL_Surface*);
    static SDL_Surface* loadFromImage(std::string);
    static void free(SDL_Surface*);
};