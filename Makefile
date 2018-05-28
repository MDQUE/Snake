SOURCES = Smain.c Superlib.h side_menu.c Timing.c Draw.c

TARGET  = SnakeEvo

RESOURCE = SnakeEvo_res

CXX      = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g 
CPPFLAGS = -I.
LDFLAGS  = -lm -lrt

#-------------------------------------------------------------

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)
	
$(RESOURCE).c: $(RESOURCE).gresource.xml
	glib-compile-resources --sourcedir=. $(RESOURCE).gresource.xml --generate-source

.PHONY: clean
clean:
	@rm -rf $(OBJECTS) $(TARGET) core *~
	@rm -rf $(RESOURCE).c

