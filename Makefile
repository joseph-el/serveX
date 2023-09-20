NAME = webserv

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -ggdb -std=c++98
OBJS = $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(NAME) $^ -fsanitize=address

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all