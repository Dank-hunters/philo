NAME	= philo

SRCS	=	philo.c \
			init.c \
			atoit.c	\
			utils.c


SRCS_DIR	=	srcs

OBJS_DIR	=	objs

OBJS	=  $(SRCS:.c=.o)

OBJS_P	= $(addprefix $(OBJS_DIR)/, $(OBJS))

INC	=	include

CFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror -I $(INC)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INC)/philo.h
			gcc $(CFLAGS) -c $< -o $@

all: create_obj_dir  $(NAME)


$(NAME) :    $(OBJS_P)
			gcc  $(CFLAGS) $(OBJS_P) -o $(NAME)
			printf "Push_swap compilation completed"


create_obj_dir :
				rm -f objs || true
				mkdir -p objs

clean:
				rm -f $(OBJS_P)

fclean:
	           rm -f $(OBJS_P)
	           rm -f $(NAME)
	           rm -rf objs

re:            fclean all

.PHONY:        all  create_obj_dir clean fclean re \
