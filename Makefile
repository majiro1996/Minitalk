# Define the names of the server and client programs
SERVER = server
CLIENT = client

# Compiler flags and variables
CFLAGS = -Wall -Werror -Wextra
CC = gcc
PRINTF = ft_printf
LIBFT = libft

# Compiler flags for building the project
FLAGS = -Wall -Wextra -Werror -I$(PRINTF)/headers -I$(LIBFT)/headers -L$(PRINTF) -lftprintf -L$(LIBFT) -lft

# Names of the object files created when compiling the source code
SERVER_OBJS = server.o
CLIENT_OBJS = client.o

# Default build target
all: $(SERVER) $(CLIENT)
	@echo "Minitalk is ready"

# Bonus target that depends on the "all" target
bonus: all

# Target for building the server program
$(SERVER): $(SERVER_OBJS)
	# Build the ft_printf library
	@make -s -C $(PRINTF)
	# Build the libft library
	@make -s -C $(LIBFT)
	# Link the object files and libraries to create the server executable
	@$(CC) $(FLAGS) $(SERVER_OBJS) -o $(SERVER)

# Target for building the client program
$(CLIENT): $(CLIENT_OBJS)
	# Build the ft_printf library
	@make -s -C $(PRINTF)
	# Build the libft library
	@make -s -C $(LIBFT)
	# Link the object files and libraries to create the client executable
	@$(CC) $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)

# Pattern rule for building object files from source code
%.o: %.c
	# Compile the source code using the C compiler and flags
	@$(CC) $(CFLAGS) -c $< -o $@

# Target for cleaning up build artifacts
clean:
	# Clean up the ft_printf library
	@make fclean -s -C $(PRINTF)
	# Clean up the libft library
	@make fclean -s -C $(LIBFT)
	# Remove the object files
	@rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	@echo "Compiled objects have been removed"

# Target for completely cleaning up build artifacts
fclean: clean
	# Remove the server and client executables
	@rm -f $(SERVER) $(CLIENT)
	@echo "Executables have been removed"

# Target for rebuilding the project from scratch
re: fclean all

# Target for rebuilding the project from scratch, including bonus targets
rebonus: fclean all 

# Specify which targets do not represent actual files
.PHONY: all bonus clean fclean re rebonus
