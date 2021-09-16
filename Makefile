NAME= ft_containers

SRCS= main_test.cpp common.cpp test_map.cpp test_vector.cpp test_stack.cpp

SRCS_BONUS = test_set_bonus.cpp

SRCS_TESTS = vector.cpp map.cpp stack.cpp set.cpp main.cpp

OBJS= $(addprefix srcs/, $(SRCS:.cpp=.o))

OBJS_BONUS= $(addprefix srcs/, $(SRCS_BONUS:.cpp=.o))

OBJS_TESTS= $(addprefix srcs/, $(SRCS_TESTS:.cpp=.o))

CC= clang++ -g

CFLAGS= -Wall -Wextra -Werror -std=c++98

HEADER= -I includes

.cpp.o: ./includes/*.hpp
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

tests: $(OBJS_TESTS)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)
	

re: fclean all	

.PHONY: all clean fclean re
