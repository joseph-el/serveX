NAME = Webserv

CC = c++

PREFIX_FOLDER := $(shell pwd)
CONFIG_FILE   := $(addsuffix /cfg/webserv.cfg,$(PREFIX_FOLDER))

CPPFLAGS :=  -D DEFAULT_CONF=\"$(CONFIG_FILE)\" #-fsanitize=address -g


UTILITY :=  source/utility/location_data.cpp\
			source/utility/server_data.cpp \
			source/utility/StringManipulation.cpp \
			source/utility/utils.cpp

HTTP   := source/www/socket.cpp \
		  source/www/request.cpp \
		  source/www/response.cpp \
		  source/www/client.cpp \
		  source/www/Header.cpp \
		  source/www/mimeTypes.cpp \
		  source/www/requestBody.cpp 

		  
CORE := source/Webserv-core.cpp \
		source/core/config.cpp \
		source/core/optioneer.cpp \
		source/core/server.cpp

SRCS =  $(CORE) \
		$(UTILITY) \
		$(HTTP)

# OBJS	 := $(SRCS:%.cpp=%.o)


show :
	clear && echo "Find config file cfg at : $(CONFIG_FILE)" && rm -f $(NAME)

server : $(SRCS)
	@$(CC) -g $(CPPFLAGS) $^ -o $(NAME)

rs : show server
	



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