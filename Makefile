# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long

# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# MLX
CMLXFLAG = -lmlx -lX11 -lXext -lm

# Include
INCLUDE = -I./include

# Source files
SRCS =  src/main.c \
		src/exit.c \
		src/parser.c \
		src/validator.c \

# Object files
OBJ_DIR = obj
OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(NAME)

# Build pipex binary (regular)
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft $(CMLXFLAG) -o $(NAME)


# Build libft library if needed
$(LIBFT):
	make -C $(LIBFT_PATH) all

# Compile .c to .o
$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean object files
clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

# Full clean: remove objects and binary
fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re