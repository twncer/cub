# TODO for myself
#
# 1) complete the gallery integration:
# 1.1) just complete the initiation, not the way of it
# (OK)
#
# 2) make 3 shitty image for minimap:
# 2.1) player, wall, floor
# 2.2) figure out if you gonna rotate the player icon or make various images
# (OK)
# 2.8) center player in the minimap and fog the walls around
# 2.9) blacken the fogged grids. this way I'll keep the minimap small
# (NO)
#
# 3) complete the main menu functionality
# (NO)
#
# 4) embed the png parser to cub3_images module
# (NO)
#
# 4.5) gather config for cub3_images. auto create it maybe?
# (NO)
#
# 5) check out for potential leaks:
# 5.1) at this point just check if there is leaks and are they complex
# (NO)
#
# 6) merge
# (NO)
#
# 7) add mana functionality
# (NO)
#
# 8) fireball is the last and last
# (NO)
#
# 9) for last and last and last, check for the potential null check skips
# (NO)

CC              = cc
CFLAGS          = -Wall -Wextra -I$(INC_DIR) -I$(MLX_DIR) # -Werror

NAME            = cub3d

MLX_DIR         = minilibx
MLX             = $(MLX_DIR)/libmlx.a
MLXFLAGS        = -lmlx -lXext -lX11 -lm -lz

SRC             = $(wildcard *.c) \
                  $(filter-out $(MLX_DIR)/%, $(wildcard */*.c)) \
                  $(filter-out $(MLX_DIR)/%, $(wildcard */*/*.c))

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