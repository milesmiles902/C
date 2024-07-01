#Import includes
COMMON_INCLUDES = -I../sharedLib/exports

#Sources/objects
SRC_PATH = ./src
OBJECTS = $(SRC_PATH)/main.o

#Libraries
SYSLIBRARIES = -lpthread -lm -ldl

DEMOLIB_PATH = ../deploy
# specifying full or partial path may backfire at runetime!!
DEMO_LIBRARY = ../deploy/libdynamiclinkingdemo.so
LIBS = $(SYSLIBRARIES) $(DEMO_LIBRARY) -wl,-Bdynamic

#Outputs
EXECUTABLE = demoNoMinusL

#COMPILER
INCLUDES = $(COMMON_INCLUDES)
DEBUG_CFLAGS = -Wall -g -Oo
RELEASE_CFLAGS = -Wall -O2

ifeq ($(DEBUG),1)
CFLAGS = $(DEBUG_CFLAGS) $(INCLUDES)
else
CFLAGS = $(RELEASE_CFLAGS) $(INCLUDES)
Endif

COMPILE = g++ $(CFLAGS)

#Linker
RUNTIME_LIB_PATH = -Wl,-R$(DEMOLIB_PATH)
LINK = g++

#BUILD procesdures/target descriptsion
default: $(EXECUTABLE)
	%.o: %.c
	$(COMPILE) -c $< -o $@
$(EXECUTABLE): $(OBJECTS) $(LINK) $(OBJECTS) $(LIBS) $(RUNTIME_LIB_PATH) -o $(EXECUTABLE)
clean:
	rm $(OBJECTS) $(EXECUTABLE)
deploy:
	make clean;make;patchelf --set-r-path ../deploy:./deploy $(EXECUTABLE); cp $(EXECUTABLE) ../;


