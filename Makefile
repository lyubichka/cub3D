# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 18:52:55 by veronikalub       #+#    #+#              #
#    Updated: 2025/11/14 18:52:56 by veronikalub      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

# compilers and flags
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
INCLUDES	:= -Iinclude -Ilibft

# directories
SRC_DIR		:= src
PARSER_DIR	:= $(SRC_DIR)/parser
UTILS_DIR	:= $(SRC_DIR)/utils

# sources
SRCS		:= \
	$(SRC_DIR)/main.c \
	$(PARSER_DIR)/parse_scene.c \
	$(PARSER_DIR)/parse_read.c \
	$(PARSER_DIR)/parse_header_till_map.c \
	$(PARSER_DIR)/handle.c \
	$(PARSER_DIR)/parse_map.c \
	$(PARSER_DIR)/parse_resolution.c \
	$(PARSER_DIR)/parse_texture.c \
	$(PARSER_DIR)/parse_color.c \
	$(PARSER_DIR)/parse_rgb.c \
	$(PARSER_DIR)/dup_or_parse.c \
	$(PARSER_DIR)/handle_so_no_we_ea_s.c \
	$(PARSER_DIR)/handle_kind_validate.c \
	$(PARSER_DIR)/parser_check.c \
	$(PARSER_DIR)/parser_free.c \
	$(UTILS_DIR)/free_split.c \
	$(UTILS_DIR)/utils.c \
	$(UTILS_DIR)/stub_engine.c

OBJS		:= $(SRCS:.c=.o)

# libraries
LIBFT_DIR	:= libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

MLX_DIR		:= minilibx-linux
MLX_A		:= $(MLX_DIR)/libmlx.a
MLX_FLAGS	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_A) -o $(NAME)

bonus: all

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
