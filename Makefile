NAME = ft_ls
LIB = libftprintf.a
CC = gcc
C_FLAGS = -Wall -Wextra -Werror

PATH_SRCS = ./srcs/
PATH_HEADERS = ./includes/
PATH_LIB = ../ft_printf/

SRCS_NAME = main.c create_option.c find_start_path.c create_entities.c \
			rights_in_char.c deal_one_dir.c print_one_rep.c sort_base.c \
			deal_sort.c compare_time.c free_rep.c put_name_colored.c \
			find_type.c to_display.c print_l.c

SRCS = $(addprefix $(PATH_SRCS), $(SRCS_NAME))
OBJS = $(SRCS_NAME.c=.o)

all : $(NAME)

$(PATH_LIB)$(LIB) :
	make -C $(PATH_LIB)

$(NAME) : $(PATH_LIB)$(LIB) $(SRCS)
	$(CC) $(C_FLAGS) -o $@ -g $^

OBJS : $(SRCS) $(PATH_HEADERS)%.h
	$(CC) $(C_FLAGS) - c $^ -o $@

.PHONY : clean fclean re

clean :
	make clean -C $(PATH_LIB)
	rm -rf $(OBJS)

fclean : clean
	make fclean -C $(PATH_LIB)
	rm -rf $(NAME)

re : fclean all
