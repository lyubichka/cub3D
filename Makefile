# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 00:00:00 by haiqbal           #+#    #+#              #
#    Updated: 2025/11/06 17:50:38 by haiqbal          ###   ########.fr        #
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
MAPS_DIR = $(SRC_DIR)/maps

# ============================================================================ #
#                                   SOURCE FILES                               #
# ============================================================================ #

SRCS = $(SRC_DIR)/main.c \
       $(EXEC_DIR)/render_utils.c \
       $(EXEC_DIR)/rendering.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ============================================================================ #
#                                   LIBRARIES                                  #
# ============================================================================ #

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

# ============================================================================ #
#                                   COMPILATION                                #
# ============================================================================ #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

all: $(NAME)

# Create object directory structure
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/execution

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libraries
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory

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

# Debug with valgrind
valgrind: $(NAME)
	@echo "$(BLUE)Running valgrind...$(RESET)"
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
