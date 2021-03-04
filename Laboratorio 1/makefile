APP = olupxtest

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
 
# Name of the project
PROJ_NAME=quadrado
 
# .c files
C_SOURCE=$(wildcard *.cpp)
 
# .h files
H_SOURCE=$(wildcard *.h)
 
# Object files
OBJ=$(C_SOURCE:.cpp=.o)
 
# Compiler
CC=gcc

LIBS=-framework GLUT	\
	 -framework OpenGL	\
	 -Wno-deprecated
 
#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) $(LIBS) -o $@ $^
 
%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)
 
clean:
	rm -rf *.o $(PROJ_NAME) *~

run: $(PROJ_NAME)
	./$(PROJ_NAME)