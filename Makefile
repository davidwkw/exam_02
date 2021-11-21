SRCS 	=	ft_printf.c \

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

RM = rm -f

AR = ar rcs

all : $(NAME)

$(NAME) :$(OBJS)
	@echo "Creating $(NAME)"
	@$(AR) $(NAME) $(OBJS)

bonus : all

clean :
	@echo "Cleaning up $(OBJS)"
	@$(RM) $(OBJS)

fclean : clean
	@echo "Cleaning up $(NAME)"
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
