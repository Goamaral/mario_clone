all: main 02 03

main: main.cpp Window.cpp Surface.cpp Texture.cpp
	g++ main.cpp Window.cpp Surface.cpp Texture.cpp -o main -lSDL2 -lSDL2_image -Wall

02: 02_getting_an_image_on_the_screen.cpp NewWindow.cpp
	g++ 02_getting_an_image_on_the_screen.cpp NewWindow.cpp -o 02 -lSDL2 -lSDL2_image -Wall

03: 03_event_driven_programming.cpp NewWindow.cpp
	g++ 03_event_driven_programming.cpp NewWindow.cpp -o 03 -lSDL2 -lSDL2_image -Wall

14: 14_animated_sprites_and_vsync.cpp
	g++ 14_animated_sprites_and_vsync.cpp -o 14 -lSDL2 -lSDL2_image -Wall