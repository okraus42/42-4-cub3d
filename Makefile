# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 15:40:17 by okraus            #+#    #+#              #
#    Updated: 2024/05/09 12:22:19 by tlukanie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef ECHO
HIT_TOTAL	!=	${MAKE} ${MAKECMDGOALS} --dry-run ECHO="HIT_MARK" | grep -c "HIT_MARK"
HIT_COUNT1	=	$(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
HIT_COUNT2	=	$(eval HIT_M != expr ${HIT_M} + 1)${HIT_M}
HIT_COUNT3	=	$(eval HIT_O != expr ${HIT_O} + $(BAR_LENGTH))${HIT_O}
PERC		=	$(shell expr $(HIT_COUNT3) / $(HIT_TOTAL) | bc)
ECHO		=	echo "[`expr ${HIT_COUNT1} '*' 100 / ${HIT_TOTAL}`%]"
endif

NAME		=	cub3D
LIBFT_F		=	libft/
LIBFT		=	libft.a
HEADER		=	header/cub3d.h header/menu.h
LIBMLX		=	./.MLX42
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LHEADERS	=	-I ./include -I $(LIBMLX)/include
CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -O2
CMFLAGS		=	-DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -B build
OBJ_DIR		=	objs/
SLEEP		=	#sleep 0.5

#CCC		:= cc
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
#


#all: libmlx $(NAME)

#libmlx:
#	@cmake $(LIBMLX) $(CMFLAGS) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
#%.o: %.c
#	@$(CCC) $(CFLAGS) -o $@ -c $< $(LHEADERS) && printf "Compiling: $(notdir $<)"
#$(NAME): $(OBJS)
#	@$(CCC) $(OBJS) $(LIBS) $(LHEADERS) -o $(NAME)
# SOURCES

SRC			=	$(addprefix $(SRC_DIR), $(SRC_S))

# Source directories

SRC_DIR		=	src/
HOOK_DIR	=	hooks/
PARSER_DIR	=	parser/
CUB3D_DIR	=	cub3d/
MENU_DIR	=	menu/
BUTTONS_DIR =	buttons/

# cub3d functions

SRC_S		=	$(BUTTONS_DIR)ft_buttons.c \
				$(CUB3D_DIR)ft_cub3d.c \
				$(CUB3D_DIR)ft_cub3d_2.c \
				ft_doors.c \
				ft_free.c \
				ft_game.c \
				ft_game_bonus.c \
				ft_gameplay.c \
				ft_gamestart.c \
				ft_halloffame.c \
				$(HOOK_DIR)ft_hook.c \
				ft_keyhook.c \
				ft_line.c \
				ft_listfield.c \
				ft_map.c \
				$(MENU_DIR)ft_menu.c \
				$(MENU_DIR)ft_menu_2.c \
				$(MENU_DIR)ft_menu_3.c \
				$(MENU_DIR)ft_menu_4.c \
				$(MENU_DIR)ft_menu_5.c \
				$(MENU_DIR)ft_menu_6.c \
				$(MENU_DIR)ft_menu_7.c \
				$(MENU_DIR)ft_menu_8.c \
				$(MENU_DIR)ft_menu_9.c \
				$(MENU_DIR)ft_menu_10.c \
				$(MENU_DIR)ft_menu_11.c \
				$(MENU_DIR)ft_menu_12.c \
				$(MENU_DIR)ft_menu_13.c \
				$(MENU_DIR)ft_menu_14.c \
				$(MENU_DIR)ft_menu_15.c \
				$(MENU_DIR)ft_menu_16.c \
				ft_minimap.c \
				ft_mousehook.c \
				ft_overlay.c \
				$(PARSER_DIR)ft_parser.c \
				$(PARSER_DIR)ft_parser_2.c \
				$(PARSER_DIR)ft_parser_3.c \
				$(PARSER_DIR)ft_parser_4.c \
				$(PARSER_DIR)ft_parser_5.c \
				$(PARSER_DIR)ft_parser_6.c \
				ft_randommap.c \
				ft_rays.c \
				ft_saveload.c \
				ft_screen2d.c \
				ft_screen2dquad.c \
				ft_screen3d.c \
				ft_settings.c \
				ft_sprite.c \
				ft_text.c \
				ft_textfield.c

# Formating

NRM_FORMAT	=	\033[0m

GREEN		=	\033[1;32m
YELLOW		=	\033[1;93m
RED			=	\033[1;31m
REVERSE		=	\033[7m
RETURN		=	\033[1F\r\033[2K

# Printing

BAR_LENGTH	:=	50
PRINT1		=	printf "[$(HIT_COUNT2)/$(HIT_TOTAL)]" ;
PRINT2		=	for num in `seq 1 $(BAR_LENGTH)` ; do \
					if [ $$num -le $(PERC) ] ; then \
						printf "$(REVERSE) $(NRM_FORMAT)" ; \
					else \
						printf " " ; \
        			fi \
    			done

# Objects

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_S:.c=.o))

# RULES

all:			announce libmlx $(LIBFT) $(NAME)
				@echo "$(RETURN)$(RETURN)$(GREEN)CUB3D compiled! $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)
				@echo "$(GREEN)Amazing <<$(REVERSE)CUB3D$(NRM_FORMAT)$(GREEN)>> compiled!$(NRM_FORMAT)"
				

bonus:			all

# MESSAGES 

announce: 
				@echo "$(RED)Magic in progress...\n$(NRM_FORMAT)"

#LIBMLX

libmlx:
				@cmake $(LIBMLX) $(CMFLAGS) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j4
				@echo "$(GREEN)The <<$(REVERSE)MLX42$(NRM_FORMAT)$(GREEN)>> compiled!$(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# COMPILATION

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADER)
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(OBJ_DIR)$(HOOK_DIR)
				@mkdir -p $(OBJ_DIR)$(PARSER_DIR)
				@mkdir -p $(OBJ_DIR)$(CUB3D_DIR)
				@mkdir -p $(OBJ_DIR)$(MENU_DIR)
				@mkdir -p $(OBJ_DIR)$(BUTTONS_DIR)
				@$(SLEEP)
				@echo "$(RETURN)$(RETURN)$(YELLOW)Compiling CUB3D: $< $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(CC) $(CFLAGS) -c $< -o $@
				@$(ECHO)

$(NAME): 		$(OBJ)
				@echo "$(RETURN)$(RETURN)$(GREEN)Libft compilation complete!$(NRM_FORMAT)"
				@$(CC) $(CFLAGS) $(SRC) libft.a $(LIBS) $(LHEADERS) -o $(NAME)
				@echo "$(RETURN)$(RETURN)$(GREEN)CUB3D compiled!$(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

$(LIBFT):
				@echo "$(RETURN)$(RETURN)$(YELLOW)Compiling LIBFT: $< $(NRM_FORMAT)"
				@make -s -C $(LIBFT_F)
				@cp libft/libft.a .
				@echo "$(YELLOW)Compiling CUB3D: $< $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# clean library

clean:
				@rm -rf $(OBJ_DIR)
				@rm -f $(LIBFT)
				@make fclean -s -C $(LIBFT_F)
				@rm -rf $(LIBMLX)/build
				@echo "$(RED)Objects removed!$(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# Remove the program after running clean

fclean:			clean
				@rm -f $(NAME)
				@echo "$(RETURN)$(RED)Library and program deleted!$(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# Remove stuff and make it all again

re: 			fclean all
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# Phony stuff for rules

.PHONY: all announce clean fclean re bonus
