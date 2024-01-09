
# ---------------------------------------------------------------------------- #
#                                    Config                                    #
# ---------------------------------------------------------------------------- #

NAME			:= miniRT
CC				:= cc
RPP				:= 10
WIDTH			:= 1000
HEIGHT			:= 1000
CFLAGS			:= -I./includes -Wall -Wextra -Werror -DRPP=$(RPP) -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
LINKS			= -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
LINKS			+= -framework Cocoa -framework OpenGL -framework IOKit
LINKS			+= -pthread
LIBFT_DIR		:= ./libraries/libft
LIBFT			:= ./libraries/libft/libft.a
MLX_DIR			:= ./libraries/mlx
MLX				:= ./libraries/mlx/build/libmlx42.a

# ---------------------------------------------------------------------------- #
#                                 Source Files                                 #
# ---------------------------------------------------------------------------- #

OBJ_DIR			:= ./objs
VPATH			:= ./src/ ./src/parser/ ./src/utils/ ./src/debugging/ ./src/input/
VPATH			+= ./src/free/ ./src/render/ ./src/vec_utils.c

SRC				:= main.c
PARSER_SRC		:= parser.c init_scene.c parser_utils.c init_objects.c input_check.c
UTIL_SRC		:= progress_bar.c split_line.c colour_utils.c ft_dabs.c rand.c
FREE_SRC		:= free_objects.c
INPUT_SRC		:= input.c
RENDER_SRC		:= render_scene.c pixel_colour.c amb_light.c intersection.c ray_calculations.c \
					mlx.c anti_aliasing.c
DEBUGGING_SRC	:= t_printing.c
VEC_UTILS_SRC	:= vector_operations.c vector_operations2.c

SRCS			:= $(SRC) $(PARSER_SRC) $(UTIL_SRC) $(DEBUGGING_SRC) $(INPUT_SRC)
SRCS			+= $(FREE_SRC) $(RENDER_SRC) $(VEC_UTILS_SRC)
OBJS			:= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# ---------------------------------------------------------------------------- #
#                                     Rules                                    #
# ---------------------------------------------------------------------------- #

all: .submodules_initialized $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX) $(LINKS)
	@echo $(GREEN)"Linking MiniRT"$(DEFAULT);

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	@cd libraries/mlx && cmake -B build && cmake --build build -j4

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: re

nflag: CFLAGS = -I./includes
nflag: all

.submodules_initialized:
	git submodule init $(LIBFT_DIR)
	git submodule update $(LIBFT_DIR)
	git submodule init $(MLX_DIR)
	git submodule update $(MLX_DIR)
	@touch .submodules_initialized

wsl: LINKS := -ldl -lglfw -pthread -lm
wsl: all
# wsl: CFLAGS += -g

clean:
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) .submodules_initialized

re: fclean all

.PHONY: all clean fclean re

# Colours to make it look nice :)
DEFAULT	= "\033[39m"
GREEN	= "\033[32m"