SRC =	src/main.cpp					\
		src/character/Character.cpp		\
		src/window/SfmlDrawer.cpp		\

CC = g++

NAME = sudoku_solver

OBJ = $(SRC:.cpp=.o)

SFMLFLAG = -lsfml-graphics -lsfml-window -lsfml-system

CPPFLAGS	=	-W -Wall -Wextra

all : $(NAME)

$(NAME) :	$(OBJ)
	$(CC) $(CPPFLAGS) $(SFMLFLAG) $(SRC) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean :
	$(RM) $(OBJ)
	$(RM) $(NAME)

re :	fclean all