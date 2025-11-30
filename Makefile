# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3d

# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# MLX
CMLXFLAG = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

# Include
INCLUDE = -I./include

# Source files
SRCS =  src/main.c \
        src/cleanup/exit.c \
        src/parser/parser.c \
        src/parser/parser_utils.c \
        src/validator/flood_fill.c \
        src/validator/validator_map.c \
        src/validator/validator_map_utils.c \
        src/validator/validator_colors.c \
        src/validator/validator_colors_utils.c \
        src/validator/validator_textures.c \
        src/validator/validator_textures_utils.c \
        src/validator/validator.c \
        src/render/draw.c \
        src/render/move.c \
        src/render/rotate.c \
        src/render/raycasting.c \
        src/render/raycasting_init.c \
        src/render/raycasting_texture.c \
        src/render/raycasting_draw.c \
        src/render/hook.c \
        src/render/mouse.c \
        src/render/render.c \
        src/utils/utils.c \
        src/cleanup/free.c

# Object files
OBJ_DIR = obj
OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(NAME)

# Build Cub3D binary
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft $(CMLXFLAG) -o $(NAME)


# Build libft library
$(LIBFT):
	make -C $(LIBFT_PATH) all

# Compile .c to .o
$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean object folders
clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR)

# Full clean: remove object folders and binary
fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
