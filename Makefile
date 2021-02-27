CXX=g++
CXXFLAGS=-Wall
LDLIBS=-L./lib -lEngine -I./lib -lSDL2 -lSDL2_image

all: 02 03 04 05 06 07 08

engine:
	(cd ./lib && make)

02: engine
	$(CXX) 02_getting_an_image_on_the_screen.cpp -o 02_getting_an_image_on_the_screen $(LDLIBS) $(CXXFLAGS)

03: engine
	$(CXX) 03_event_driven_programming.cpp -o 03_event_driven_programming $(LDLIBS) $(CXXFLAGS)

04: engine
	$(CXX) 04_key_presses.cpp -o 04_key_presses $(LDLIBS) $(CXXFLAGS)

05: engine
	$(CXX) 05_optimized_surface_loading_and_soft_stretching.cpp -o 05_optimized_surface_loading_and_soft_stretching $(LDLIBS) $(CXXFLAGS)

06: engine
	$(CXX) 06_extension_libraries_and_loading_other_image_formats.cpp -o 06_extension_libraries_and_loading_other_image_formats $(LDLIBS) $(CXXFLAGS)

07: engine
	$(CXX) 07_texture_loading_and_rendering.cpp -o 07_texture_loading_and_rendering $(LDLIBS) $(CXXFLAGS)

08: engine
	$(CXX) 08_geometry_rendering.cpp -o 08_geometry_rendering $(LDLIBS) $(CXXFLAGS)

14: engine
	$(CXX) 14_animated_sprites_and_vsync.cpp Window.cpp Texture.cpp Surface.cpp -o 14 $(LDLIBS) $(CXXFLAGS)