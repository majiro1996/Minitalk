SERVER = server
CLIENT = client

CFLAGS = -Wall -Werror -Wextra
CC = gcc
PRINTF = ft_printf
LIBFT = libft
FLAGS = -Wall -Wextra -Werror -I$(PRINTF)/headers -I$(LIBFT)/headers -L$(PRINTF) -lftprintf -L$(LIBFT) -lft

SERVER_OBJS = server.o
CLIENT_OBJS = client.o

all: $(SERVER) $(CLIENT)
	@echo "Minitalk is ready"

bonus: all

$(SERVER): $(SERVER_OBJS)
	@make -s -C $(PRINTF)
	@make -s -C $(LIBFT)
	@$(CC) $(FLAGS) $(SERVER_OBJS) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS)
	@make -s -C $(PRINTF)
	@make -s -C $(LIBFT)
	@$(CC) $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make fclean -s -C $(PRINTF)
	@make fclean -s -C $(LIBFT)
	@rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	@echo "Compiled objects have been removed"

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@echo "Executables have been removed"

re: fclean all

rebonus: fclean all 

.PHONY: all bonus clean fclean re rebonus
