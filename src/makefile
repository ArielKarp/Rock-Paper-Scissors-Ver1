COMP = g++
#COMP = g++-5.3.0
#put all your object files here
OBJS = Logger.o BasicPiece.o Joker.o CommandAnalyzer.o MoveCommandAnalyzer.o PositionCommandAnalyzer.o Player.o Game.o main.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
Logger.o: Logger.cpp Logger.h Utilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
BasicPiece.o: BasicPiece.cpp BasicPiece.h Logger.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Joker.o: Joker.h Joker.cpp BasicPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
CommandAnalyzer.o: CommandAnalyzer.h CommandAnalyzer.cpp Joker.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MoveCommandAnalyzer.o: MoveCommandAnalyzer.h MoveCommandAnalyzer.cpp CommandAnalyzer.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PositionCommandAnalyzer.o: PositionCommandAnalyzer.h PositionCommandAnalyzer.cpp CommandAnalyzer.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.h Player.cpp PositionCommandAnalyzer.h PositionCommandAnalyzer.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Game.o: Game.h Game.cpp Player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp Game.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
