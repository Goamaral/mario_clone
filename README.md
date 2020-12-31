# Learning SDL2

# Dependencies
- SDL2
- SDL2_image

# My C++ rules
- $variables represent private class variables
- Use SDL_assert for code that when compiled should always run
- Use SDL_LogCritical for code dependent on external resources, that when unexpected behaviour occurs, the program should stop
- Use SDL_LogInfo for code dependent on external resources, that when unexpected behaviour occurs, there is a workaround