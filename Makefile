all: 02 03 04 05 06 07 08

02: System Window Surface Texture Color
	g++ 02_getting_an_image_on_the_screen.cpp System.o Window.o Surface.o Texture.o Color.o -o 02_getting_an_image_on_the_screen -lSDL2 -lSDL2_image -Wall

03: System Window Surface Texture Color
	g++ 03_event_driven_programming.cpp System.o Window.o Surface.o Texture.o Color.o -o 03_event_driven_programming -lSDL2 -lSDL2_image -Wall

04: System Window Surface Texture Color
	g++ 04_key_presses.cpp System.o Window.o Surface.o Texture.o Color.o -o 04_key_presses -lSDL2 -lSDL2_image -Wall

05: System Window Surface Texture Color
	g++ 05_optimized_surface_loading_and_soft_stretching.cpp System.o Window.o Texture.o Surface.o -o 05_optimized_surface_loading_and_soft_stretching -lSDL2 -lSDL2_image -Wall

06: System Window Surface Texture Color
	g++ 06_extension_libraries_and_loading_other_image_formats.cpp System.o Window.o Surface.o Texture.o Color.o -o 06_extension_libraries_and_loading_other_image_formats -lSDL2 -lSDL2_image -Wall

07: System Window Surface Texture Color
	g++ 07_texture_loading_and_rendering.cpp System.o Window.o Surface.o Texture.o Color.o -o 07_texture_loading_and_rendering -lSDL2 -lSDL2_image -Wall

08: System Window Surface Texture Color
	g++ 08_geometry_rendering.cpp System.o Window.o Surface.o Texture.o Color.o -o 08_geometry_rendering -lSDL2 -lSDL2_image -Wall

14:
	g++ 14_animated_sprites_and_vsync.cpp Window.cpp Texture.cpp Surface.cpp -o 14 -lSDL2 -lSDL2_image -Wall

# Components #
System:
	g++ System.cpp -c -Wall

Window: Texture
	g++ Window.cpp -c -Wall

Surface:
	g++ Surface.cpp -c -Wall

Texture:
	g++ Texture.cpp -c -Wall

Color:
	g++ Color.cpp -c -Wall