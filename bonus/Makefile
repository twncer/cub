CC              = cc
CFLAGS          = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR)

NAME            = cub3d

MLX_DIR         = minilibx
MLX             = $(MLX_DIR)/libmlx.a
MLXFLAGS        = -lmlx -lXext -lX11 -lm -lz

SRC             = $(wildcard *.c) \
                  $(filter-out $(MLX_DIR)/%, $(wildcard */*.c))

OBJ             = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(MLX_DIR) $(MLXFLAGS) -o $(NAME)

$(MLX):
	@make -C $(MLX_DIR)

run: all
	make clean && ./cub3d testmaps/valid_basic.cub

run_valgrind: all
	make clean && valgrind ./cub3d testmaps/valid_basic.cub

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)
	@make -C $(MLX_DIR) clean 2>/dev/null || true

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re