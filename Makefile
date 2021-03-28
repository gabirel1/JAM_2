SRC =	src/main.cpp					\
		src/character/Character.cpp		\
		src/window/SfmlDrawer.cpp		\

CC = g++

NAME = gpasvu

OBJ = $(SRC:.cpp=.o)

SFMLFLAG = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CPPFLAGS	=	-W -Wall -Wextra

all : $(NAME)

$(NAME) :	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(SFMLFLAG)

clean :
	$(RM) $(OBJ)

fclean :
	$(RM) $(OBJ)
	$(RM) $(NAME)

re :	fclean all