CXX = g++
OBJS = ./build/Archer.o ./build/LoadMedia.o ./build/Obj.o ./build/Board.o ./build/Button.o ./build/GoldTower.o ./build/main.o ./build/Knight.o ./build/Soldier.o ./build/Status.o ./build/Tower.o ./build/Unit.o
INC = ./include 
LIB = ./lib 
OBJDIR = ./build
EXEDIR = ./bin


LDFLAGS = -lmingw32 -lSDL2_image -lSDL2_mixer -lSDL2main -lSDL2_ttf -lSDL2


all: directories $(EXEDIR)/ConquEEror

directories: $(OBJDIR) $(EXEDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(OBJDIR)/%.o: ./src/%.cpp
	$(CXX) -c -o $@ $< -g -I$(INC) -L$(LIB) $(LDFLAGS)

$(EXEDIR)/ConquEEror: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ./bin/ConquEEror $(OBJS) -L$(LIB) $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/*
	rm -f $(EXEDIR)/*.exe
