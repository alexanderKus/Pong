CPP=g++
CPPFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SRC=src
OBJ=obj

SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
HDRS=$(wildcard $(SRC)/*.h)
BIN=game

all: $(BIN)

$(BIN): $(OBJS) $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $@

clean:
	$(RM) -r $(OBJ)
	$(RM) $(BIN)
