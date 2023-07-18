# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 17:21:24 by mmaqbour          #+#    #+#              #
#    Updated: 2023/02/11 17:21:26 by mmaqbour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client.c utils.c
CLIENT_NAME = client
OBJ_CLI = $(CLIENT:.c=.o)

SERVER = server.c utils.c
SERVER_NAME = server
OBJ_SER = $(SERVER:.c=.o)

CLIENT_B = client_bonus.c utils_bonus.c
CLIENT_NAME_B = client_bonus
OBJ_CLI_B = $(CLIENT_B:.c=.o)

SERVER_B = server_bonus.c utils_bonus.c
SERVER_NAME_B = server_bonus
OBJ_SER_B = $(SERVER_B:.c=.o)

HEADERS = minitalk.h
HEADERS_BONUS = minitalk_bonus.h

CC = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

%.o: %.c 
	$(CC) $(FLAGS) -c $< -o $@

all: $(CLIENT_NAME) $(SERVER_NAME)

$(SERVER_NAME): $(OBJ_SER) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ_SER) -o $(SERVER_NAME)

$(CLIENT_NAME): $(OBJ_CLI) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ_CLI) -o $(CLIENT_NAME)

$(SERVER_NAME_B): $(OBJ_SER_B) $(HEADERS_BONUS)
	$(CC) $(FLAGS) $(OBJ_SER_B) -o $(SERVER_NAME_B)

$(CLIENT_NAME_B): $(OBJ_CLI_B) $(HEADERS_BONUS)
	$(CC) $(FLAGS) $(OBJ_CLI_B) -o $(CLIENT_NAME_B)

bonus: $(CLIENT_NAME_B) $(SERVER_NAME_B)

clean:
	$(RM) $(OBJ_CLI) $(OBJ_SER)
	$(RM) $(OBJ_CLI_B) $(OBJ_SER_B)

fclean: clean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME)
	$(RM) $(SERVER_NAME_B) $(CLIENT_NAME_B)
	
re: fclean all

.PHONY:	all clean fclean re