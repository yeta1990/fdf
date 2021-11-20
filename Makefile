SRCS	= fdf.c	srcs/free_fdf.c srcs/get_next_line.c srcs/get_next_line_utils.c srcs/ft_atoi.c srcs/ft_draw_lines.c srcs/ft_window_mgmt.c srcs/ft_memcmp.c srcs/hex_to_int.c srcs/ft_putstr_fd.c srcs/ft_putchar_fd.c srcs/ft_parse_map.c

INCS	= inc

CC		= gcc

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

NAME	= fdf

RM		= rm -f

%.o:%.c
			$(CC) $(CFLAGS) -Imlx -c $< -o $(<:.c=.o) -I$(INCS)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -I$(INCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
