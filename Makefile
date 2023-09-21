NAME = Webserv

CC = c++

PREFIX_FOLDER := $(shell pwd)
CONFIG_FILE   := $(addsuffix /cfg/wevserv.cfg,$(PREFIX_FOLDER))

CPPFLAGS := -Wall -Wextra -Werror -ggdb -std=c++98 -D DEFAULT_CONF=\"$(CONFIG_FILE)\"

UTILITY :=  source/utility/location_data.cpp \
			source/utility/server_data.cpp

CORE := source/Webserv-core.cpp \
		source/core/config.cpp \
		source/core/optioneer.cpp \
		source/core/server.cpp

SRCS =  $(UTILITY) \
		$(CORE)

OBJS	 := $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(NAME) $^

%.o: %.cpp 
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all