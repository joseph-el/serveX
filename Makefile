NAME = serveX

CC = c++
PREFIX_FOLDER = $(shell pwd)
CPPFLAGS = -Wall -Wextra -Werror -ggdb -std=c++98 -D PREFIX_FOLDER=\"$(PREFIX_FOLDER)\"
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