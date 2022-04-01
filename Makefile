SERVER = server
CLIENT = client
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders

PRINTF_A = printf/libftprintf.a

RM = rm -f

OBJS = $(SRCS:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER):
	@$(MAKE) bonus -C ./printf >/dev/null
	$(CC) $(CFLAGS) server.c $(PRINTF_A) -o $(SERVER)

$(CLIENT):
	$(MAKE) bonus -C ./printf >/dev/null
	$(CC) $(CFLAGS) client.c $(PRINTF_A) -o $(CLIENT)

clean:
	$(MAKE) clean -C ./printf >/dev/null
	$(MAKE) clean -C ./printf/libft >/dev/null
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./printf >/dev/null
	$(MAKE) clean -C ./printf/libft >/dev/null
	$(RM) $(SERVER)
	$(RM) $(CLIENT)

re: fclean all

.PHONY: all clean fclean bonus re