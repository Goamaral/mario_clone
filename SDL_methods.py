# Initialize the SDL library
int SDL_Init(Uint32 flags)

# Create a window with the specified position, dimensions, and flags
SDL_Window* SDL_CreateWindow(const char* title, intx, int y, int w, int h, Uint32 flags)
  -> created window : NULL

# Get the SDL surface associated with the window
SDL_Surface* SDL_GetWindowSurface(SDL_Window* window)
  -> window surface : NULL

# Fill of a rectangle with a specific color
int SDL_FillRect(SDL_Surface* dst, const SDL_Rect* rect, Uint32 color)

# Copy the window surface to the screen
int SDL_UpdateWindowSurface(SDL_Window* window)

# Wait a specified number of milliseconds
void SDL_Delay(Uint32 ms)

# Destroy a window
void SDL_DestroyWindow(SDL_Window* window)

# Clean up all initialized subsystems
void SDL_Quit(void)

# Load a surface from a BMP file
SDL_Surface* SDL_LoadBMP(const char* file)
  -> SDL_Surface* : NULL

# Free an RGB surface
void SDL_FreeSurface(SDL_Surface* surface)

# Copy surface to a destination surface
int SDL_BlitSurface(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect)

# Poll for currently pending events
int SDL_PollEvent(SDL_Event* event)
  -> 1 pending event : 0 none available

# Copy surface into a new one optimized for blitting to a surface of a specified pixel format
SDL_Surface* SDL_ConvertSurface(SDL_Surface* src, const SDL_PixelFormat* fmt, Uint32 flags)
  -> SDL_Surface* : NULL

# Copy scaled surface to a destination surface
int SDL_BlitScaled(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect)

