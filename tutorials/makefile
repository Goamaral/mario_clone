all: 02 03

02: System NewWindow NewSurface
	g++ 02_getting_an_image_on_the_screen.cpp System.o NewWindow.o NewSurface.o -o 02_getting_an_image_on_the_screen -lSDL2 -lSDL2_image -Wall

03: System NewWindow NewSurface
	g++ 03_event_driven_programming.cpp System.o NewWindow.o NewSurface.o -o 03_event_driven_programming -lSDL2 -lSDL2_image -Wall

04: System NewWindow NewSurface
	g++ 04_key_presses.cpp System.o NewWindow.o  NewSurface.o -o 04_key_presses -lSDL2 -lSDL2_image -Wall

14:
	g++ 14_animated_sprites_and_vsync.cpp NewWindow.cpp Texture.cpp Surface.cpp -o 14 -lSDL2 -lSDL2_image -Wall

# Components #
System:
	g++ System.cpp -c -Wall

NewWindow:
	g++ NewWindow.cpp -c -Wall

NewSurface:
	g++ NewSurface.cpp -c -Wall