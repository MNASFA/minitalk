CC = CC
CFLAGS = -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER)

clean: 
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all
