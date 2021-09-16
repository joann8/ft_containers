FT_NAME=ft

STD_NAME = std

NAME= ft_containers

SRCS_2= main_test.cpp common.cpp test_map.cpp test_vector.cpp test_stack.cpp test_set.cpp

SRCS= tests/main.cpp tests/map.cpp tests/vector.cpp tests/stack.cpp tests/set.cpp

OBJS= $(addprefix tests2/, $(SRCS_2:.cpp=.o))

CC= clang++

CFLAGS= -Wall -Wextra -Werror -std=c++98

HEADER= -I ./includes/

.cpp.o: ./includes/*.hpp
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

$(FT_NAME): $(SRCS)
	$(CC) $(HEADER) $(CFLAGS) -DNAMESPACE=ft -o $(FT_NAME) $(SRCS)

$(STD_NAME): $(SRCS)
	$(CC) $(HEADER) $(CFLAGS) -DNAMESPACE=std -o $(STD_NAME) $(SRCS)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	

clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(FT_NAME)
	rm -f $(STD_NAME)
	rm -f $(NAME)

re: fclean all	

.PHONY: all clean fclean re
