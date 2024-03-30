
NAME		=	main
CC			=	g++
FLAGS		=	-std=c++11   -Wall -Wextra  -Isrc -Iinclude -O3 #-fsanitize=address -fsanitize=undefined -g3 

SRCS		= src/main.cpp


				
OBJS		=	$(SRCS:.cpp=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)
			./$(NAME)
			rm -f main.o



clean	:	
				@rm -rf $(OBJS)


fclean	:	clean
				@rm -rf $(NAME)


re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.cpp
			$(CC) $(FLAGS) -o $@ -c $<
