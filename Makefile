# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D

# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# MLX
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
CMLXFLAG = -lXext -lX11 -lm -lbsd
LMLXFLAG = -L $(MLX_DIR) -lmlx

# Include
INCLUDE = -I./include -I$(MLX_DIR)

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
$(MLX_DIR)/mlx.h:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi

$(MLX): $(MLX_DIR)/mlx.h
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft $(LMLXFLAG) $(CMLXFLAG) -o $(NAME)


# Build libft library
$(LIBFT):
	make -C $(LIBFT_PATH) all

# Compile .c to .o
$(OBJ_DIR)/%.o: src/%.c $(MLX_DIR)/mlx.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean object folders
clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR)
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

# Full clean: remove object folders and binary
fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME)
	@if [ -d "$(MLX_DIR)" ]; then rm -rf $(MLX_DIR); fi

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
