NAME= ft_containers

SRCS= main_test.cpp common.cpp test_vector.cpp test_map.cpp

OBJS= $(addprefix srcs/, $(SRCS:.cpp=.o))

CC= clang++ -g

CFLAGS= -Wall -Wextra -Werror -std=c++98

HEADER= -I includes

.cpp.o: ./includes/*.hpp
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS):

fclean: clean
	rm -f $(NAME)

re: fclean all	

.PHONY: all clean fclean re
