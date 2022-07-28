# CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
INCLUDE = includes
NAME = minitalk
CLIENT_NAME = client
SERVER_NAME = server
CLIENT_SRCS = client.c
SERVER_SRCS = server.c
CLIENT_OBJS = $(addprefix $(OBJDIR)/, $(CLIENT_SRCS:%.c=%.o))
SERVER_OBJS = $(addprefix $(OBJDIR)/, $(SERVER_SRCS:%.c=%.o))
VPATH = srcs
OBJDIR = obj

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

## printf ##
PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
############

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(CLIENT_NAME) $(SERVER_NAME)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)
$(PRINTF):
	make -C $(PRINTF_DIR)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) -o $(CLIENT_NAME) $(LIBFT) $(PRINTF) $(CLIENT_OBJS) 
$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) -o $(SERVER_NAME) $(LIBFT) $(PRINTF) $(SERVER_OBJS) 

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $< 

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	$(RM) $(CLIENT_OBJS)
	$(RM) $(SERVER_OBJS)
fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(PRINTF)
	$(RM) $(CLIENT_NAME)
	$(RM) $(SERVER_NAME)
re: fclean all