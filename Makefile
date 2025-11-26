# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 00:00:00 by haiqbal           #+#    #+#              #
#    Updated: 2025/11/26 02:24:16 by haiqbal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   COLORS                                     #
# ============================================================================ #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# ============================================================================ #
#                                   PROGRAM                                    #
# ============================================================================ #

NAME = cub3D

# ============================================================================ #
#                                   DIRECTORIES                                #
# ============================================================================ #

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

EXEC_DIR = $(SRC_DIR)/execution
PARS_DIR = $(SRC_DIR)/parser
UTL_DIR = $(SRC_DIR)/utils
REND_DIR = $(EXEC_DIR)/rendering
MIN_MAP_DIR = $(EXEC_DIR)/minimap
SAVE_DIR = $(EXEC_DIR)/save

# ============================================================================ #
#                                   SOURCE FILES                               #
# ============================================================================ #

SRCS = $(SRC_DIR)/main.c \
	   $(EXEC_DIR)/execution.c \
	   $(REND_DIR)/render_utils.c \
	   $(EXEC_DIR)/init_player.c \
	   $(EXEC_DIR)/keys.c \
	   $(EXEC_DIR)/movement.c \
	   $(EXEC_DIR)/rotation.c \
	   $(EXEC_DIR)/utils1.c \
	   $(EXEC_DIR)/graphics.c \
	   $(EXEC_DIR)/textures.c \
	   $(SAVE_DIR)/save2.c \
	   $(SAVE_DIR)/bmp_header.c \
	   $(SAVE_DIR)/pixel_utils.c \
	   $(SAVE_DIR)/write_pixels.c \
	   $(SAVE_DIR)/save_bmp.c \
	   $(SAVE_DIR)/offscreen_utils.c \
	   $(MIN_MAP_DIR)/minimap.c \
	   $(MIN_MAP_DIR)/minimap_draw.c \
	   $(MIN_MAP_DIR)/minimap_utils.c \
	   $(MIN_MAP_DIR)/minimap_player.c \
	   $(REND_DIR)/ray_init.c \
	   $(REND_DIR)/ray_dda.c \
	   $(REND_DIR)/wall_calc.c \
	   $(REND_DIR)/texture_calc.c \
	   $(REND_DIR)/draw_stripe.c \
	   $(PARS_DIR)/dup_or_parse.c \
	   $(PARS_DIR)/handle_kind_validate.c \
	   $(PARS_DIR)/handle_so_no_we_ea_s.c \
	   $(PARS_DIR)/handle.c \
	   $(PARS_DIR)/parse_color.c \
	   $(PARS_DIR)/parse_header_till_map.c \
	   $(PARS_DIR)/parse_map.c \
	   $(PARS_DIR)/parse_read.c \
	   $(PARS_DIR)/parse_resolution.c \
	   $(PARS_DIR)/parse_rgb.c \
	   $(PARS_DIR)/parse_texture.c \
	   $(PARS_DIR)/parse_scene.c \
	   $(PARS_DIR)/parser_free.c \
	   $(PARS_DIR)/parser_check.c \
	   $(UTL_DIR)/utils.c \
	   $(UTL_DIR)/free_split.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ============================================================================ #
#                                   LIBRARIES                                  #
# ============================================================================ #

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX Linux
MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

# MiniLibX MacOS (not used on WSL)
# MLX_DIR = minilibx_opengl
# MLX = $(MLX_DIR)/libmlx.a
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# ============================================================================ #
#                                   COMPILATION                                #
# ============================================================================ #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -DGL_SILENCE_DEPRECATION
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

all: $(NAME)

# Create object directory structure
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/execution/save
	@mkdir -p $(OBJ_DIR)/execution/minimap
	@mkdir -p $(OBJ_DIR)/execution/rendering
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/utils

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libraries
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory

# Build MiniLibX
$(MLX):
	@echo "$(YELLOW)Building minilibx-linux...$(RESET)"
	@make -C $(MLX_DIR) --no-print-directory

# Link executable
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@make clean -C $(MLX_DIR) --no-print-directory 2>/dev/null || true
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✓ Object files removed$(RESET)"

# Full clean
fclean: clean
	@echo "$(RED)Cleaning executables and libraries...$(RESET)"
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -f $(NAME)
	@echo "$(RED)✓ All cleaned$(RESET)"

# Rebuild everything
re: fclean all

# Run the program with a test map
run: $(NAME)
	@echo "$(BLUE)Running $(NAME)...$(RESET)"
	@./$(NAME) $(MAPS_DIR)/test.cub

# Memory leak check with valgrind
valgrind: $(NAME)
	@echo "$(BLUE)Running memory leak check...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(MAPS_DIR)/test.cub

# Show help
help:
	@echo "$(GREEN)Available targets:$(RESET)"
	@echo "  $(YELLOW)all$(RESET)      - Build the project"
	@echo "  $(YELLOW)clean$(RESET)    - Remove object files"
	@echo "  $(YELLOW)fclean$(RESET)   - Remove object files and executable"
	@echo "  $(YELLOW)re$(RESET)       - Rebuild everything"
	@echo "  $(YELLOW)run$(RESET)      - Run the program with test map"
	@echo "  $(YELLOW)valgrind$(RESET) - Run with valgrind"
	@echo "  $(YELLOW)help$(RESET)     - Show this help message"

# ============================================================================ #
#                                   PHONY                                      #
# ============================================================================ #

.PHONY: all clean fclean re run valgrind help
