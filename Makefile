NAME 	:=	cub3D
FLAGS	:=	-Wall -Wextra -Werror -MMD -g

SRC		:= main.c  parsing/parse.c parsing/parse_color_line.c parsing/parse_texture_line.c \
parsing/parse_util_args.c parsing/parse_util2_args.c exec/exit_parsing.c parsing/parse_map.c \
parsing/parse_map_util.c parsing/store_check_map.c parsing/exit_parsing_util.c \
exec/exit_exec.c exec/mlx_util.c exec/init.c exec/minimap.c exec/raycasting.c \
exec/minimap_util.c exec/raycasting_util.c exec/move_player.c exec/handle_event.c \
exec/init_textures.c exec/draw_log.c


OBJS_DIR:=	./objs/
SRC_DIR := ./srcs/
OBJ		:= $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
DEPS	:= $(OBJ:.o=.d)
CC		:=	cc
LIBFT_DIR := libft-boost/
LIBFT_LIB := $(LIBFT_DIR)libft.a
INCLUDE := -I includes
DEBUG	:= -DDEBUG=1

# ============== MLX ==============

OS	:= $(shell uname)

ifeq ($(OS), Darwin)
	MLX_DIR		:= mlx-opengl
	MLX_FLAGS	:= -I$(MLX_DIR) -I/opt/X11/include
	MLX_PATH	:= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR		:= mlx-linux
	MLX_FLAGS	:= -I/usr/include -I$(MLX_DIR)
	MLX_PATH	:= -L$(MLX_DIR) -lmlx -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz
endif
MLX_LIB		:= $(MLX_DIR)/libmlx.a

# =================================

RED		:=	\033[0;31m
ROSE	:=	\033[0;95m
GREEN	:=	\033[0;32m
BPURPLE	:=	\033[1;35m
NC		:=	\033[0m
YELLOW	:=	\033[0;33m
CYAN	:=	\033[1;34m
ERASE	:=	\033[2K\r
BLUE	:=	\033[34m
END		:=	\033[0m

all: title $(NAME) 

d: FLAGS += $(DEBUG)
d: clean $(NAME)

title:
	@clear
	@echo "$(YELLOW)==== Making $(NAME) Project ====\n$(NC)"   

$(NAME): $(LIBFT_LIB) $(OBJ) $(MLX_LIB)
	@echo "\n > Creating: $(GREEN)$(NAME)...✅$(NC)"
	@$(CC) $(FLAGS) $(OBJ) $(INCLUDE) $(MLX_PATH) -o $(NAME) -L $(LIBFT_DIR) -lft 
	@echo " >$(CYAN) Done 🔥$(NC)"
	@echo "\n => Run the project:$(BPURPLE) ./$(NAME)\n$(NC)"

$(LIBFT_LIB):
	@echo "\n > Compiling: $(ROSE)libft...✅$(NC)"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

$(MLX_LIB):
	@echo "\n > Compiling: $(YELLOW)minilibX...✅$(NC)"
	@make -C $(MLX_DIR)  > /dev/null 2>&1

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "$(ERASE) > Compiling: $(BLUE)$@$(NC)$(END)"    
	@$(CC) $(FLAGS) $(INCLUDE) $(MLX_FLAGS) -c $< -o $@

clean:
	@echo " >$(RED) Deleting objects files...✅$(NC)"
	@rm -rf $(OBJS_DIR)
	@echo " >$(CYAN) Done 🔥\n$(NC)"
	@echo " >$(RED) Deleting libft-boost files...✅$(NC)"
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo " >$(CYAN) Done 🔥\n$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo " >$(RED) Deleting $(NAME) file...✅$(NC)"
	@make clean -C $(MLX_DIR)  > /dev/null 2>&1
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1 
	@echo " >$(CYAN) Done 🔥\n$(NC)"

re: fclean all

t: all 
	@./$(NAME)

-include $(DEPS)

.PHONY: all title clean fclean re debug
