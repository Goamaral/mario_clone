all: main 02 03

main:
	g++ main.cpp Window.cpp Surface.cpp Texture.cpp -o main -lSDL2 -lSDL2_image -Wall

02: System NewWindow NewSurface
	g++ 02_getting_an_image_on_the_screen.cpp System.o NewWindow.o NewSurface.o -o 02 -lSDL2 -lSDL2_image -Wall

03:
	g++ 03_event_driven_programming.cpp NewWindow.cpp -o 03 -lSDL2 -lSDL2_image -Wall

14:
	g++ 14_animated_sprites_and_vsync.cpp NewWindow.cpp Texture.cpp Surface.cpp -o 14 -lSDL2 -lSDL2_image -Wall

System:
	g++ System.cpp -c -Wall

NewWindow:
	g++ NewWindow.cpp -c -Wall

NewSurface:
	g++ NewSurface.cpp -c -Wall