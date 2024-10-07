HEADER		=	./includes

SRC			=	src/main.cpp \
				src/Map.cpp \
				src/Player.cpp \
				src/Utils.cpp \

OBJ			=	$(patsubst src%, obj%, $(SRC:.cpp=.o))

CC			=	c++

CXXFLAGS	=	-I${HEADER} -Wall -Wextra -Werror -g
LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system

NAME		=	raycast

all:		obj $(NAME) run

$(NAME):	$(OBJ)
			@$(CC) $(OBJ) -o $@ $(LDFLAGS)

obj:
			@mkdir -p obj

obj/%.o:	src/%.cpp
			@$(CC) $(CXXFLAGS) -o $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

run:
			./$(NAME)
            
clean:
			@rm -rf $(OBJ) obj
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)
			@echo "$(NAME) $(RED)removed.$(RESET)"

re:			fclean all