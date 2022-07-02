SERVER = myserver

CLIENT = myclient

CGI = cgi

CFLAGS = -Wall -Wextra -Werror

SOURCE_SERVER = main_server_in_c.cpp CGIResponse.cpp

SOURCE_CLIENT = main_client_in_c.cpp

SOURCE_CGI = main_cgi_server.cpp

CC = c++

OBJS_SERVER = $(SOURCE_SERVER:.cpp=.o)

OBJS_CLIENT = $(SOURCE_CLIENT:.cpp=.o)

OBJS_CGI = $(SOURCE_CGI:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -std=c++98 -DFOREIGN=0  -c $< -o $(<:.cpp=.o)

server: $(OBJS_SERVER)
	$(CC) $(CFLAGS) -std=c++98 $(OBJS_SERVER) -o $(SERVER)

client: $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -std=c++98 $(OBJS_CLIENT) -o $(CLIENT)

cgi: $(OBJS_CGI)
	$(CC) $(CFLAGS) -std=c++98 $(OBJS_CGI) -o $(CGI)

clean:
	rm -rf $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_CGI)

fclean: clean
	rm -rf $(SERVER) $(CLIENT) $(CGI)

re: fclean server client cgi
