NAME= ft_containers

SRCS= main_test.cpp common.cpp test_map.cpp test_vector.cpp test_stack.cpp test_set.cpp

OBJS= $(addprefix test/, $(SRCS:.cpp=.o))

CC= clang++

CFLAGS= -Wall -Wextra -Werror -std=c++98

HEADER= -I ./includes/

.cpp.o: ./includes/*.hpp
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

all : $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)	

clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all	

.PHONY: all clean fclean re
