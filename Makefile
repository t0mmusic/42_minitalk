SERVER = server
CLIENT = client
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders

PRINTF_A = printf/libftprintf.a

RM = rm -f

PRINTF_MSG = echo "ft_printf library compiling..."
SERVER_MSG = echo "server compiling"
CLIENT_MSG = echo "client compiling"
COMPLETE_MSG = echo "Ready! run ./server to get server PID, then ./client <PID> <MESSAGE>"
PRINTF_CLEAN_MSG =
PRINTF_FCLEAN_MSG = echo "Removing printf"
LIBFT_CLEAN_MSG =
LIBFT_FCLEAN_MSG = echo "Removing libft"
CLIENT_CLEAN_MSG = echo "Removing client"
SERVER_CLEAN_MSG = echo "Removing server"

all: $(PRINTF_A)
	@make $(SERVER) >/dev/null & $(SERVER_MSG)
	@make $(CLIENT) >/dev/null & $(CLIENT_MSG)
	@$(COMPLETE_MSG)

$(PRINTF_A):
	@$(PRINTF_MSG)
	@$(MAKE) bonus -C ./printf >/dev/null

$(SERVER):
	@$(CC) $(CFLAGS) server.c utils.c $(PRINTF_A) -o $(SERVER)

$(CLIENT):
	@$(CC) $(CFLAGS) client.c utils.c $(PRINTF_A) -o $(CLIENT)

clean:
	@$(MAKE) clean -C ./printf >/dev/null
	@$(MAKE) clean -C ./printf/libft >/dev/null

fclean: clean
	@$(MAKE) fclean -C ./printf >/dev/null & $(PRINTF_FCLEAN_MSG)
	@$(MAKE) clean -C ./printf/libft >/dev/null & $(LIBFT_FCLEAN_MSG)
	@$(RM) $(SERVER) & $(SERVER_CLEAN_MSG)
	@$(RM) $(CLIENT) & $(CLIENT_CLEAN_MSG)

re: fclean all

.PHONY: all clean fclean bonus re
