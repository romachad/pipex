NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_SRC = ft_strdup ft_strlen ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_memset \
	ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
	ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strlcat ft_substr ft_strjoin ft_strtrim \
	ft_split ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd
LIB_BONUS = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap
HEADERS_FILES = libft
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(LIB_SRC)))
BONUS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(LIB_BONUS)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(LIB_SRC)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(LIB_BONUS)))
HEADERS = $(addprefix $(HEADERS_DIR), $(addsuffix .h, $(HEADERS_FILES)))
SRCS_DIR = srcs/
OBJS_DIR = objs/
HEADERS_DIR = headers/

all:
	make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(HEADERS) $(OBJS)
	ar -crs $@ $^

bonus: $(HEADERS) $(NAME) $(OBJS_B)
	ar -crs $(NAME) $(OBJS_B)

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS_DIR)

re: fclean all


.PHONY: all clean fclean re
