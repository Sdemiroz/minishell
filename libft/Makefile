.SILENT:
# Example
NAME := libft.a
.DEFAULT_GOAL := all
CC := cc
AR := ar
RM := rm -rf
################################################################################
###############                  DIRECTORIES                      ##############
################################################################################
OBJ_DIR := _obj
INC_DIRS := garbage_collector
SRC_DIRS := .
# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)
################################################################################
###############                  SOURCE FILES                     ##############
################################################################################
SRCS :=	ft_isalpha.c ft_isdigit.c ft_isalpha.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_isalnum.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_itoa_2.c ft_putstr.c \
		ft_px.c ft_ux.c ft_sx.c ft_bx.c ft_putchar.c ft_strjoin_gnl.c get_next_line.c \
		garbage_collector/collector.c garbage_collector/exit.c garbage_collector/utils.c \
		ft_isspace.c ft_strcmp.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

BONUS_OBJS := $(addprefix $(OBJ_DIR)/, $(BONUS:.c=.o))
################################################################################
########                         COMPILING                      ################
################################################################################
CFLAGS := -Wextra -Wall -Werror -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS := <add linker flags here>
ARFLAGS := -rcs

# ANSI color codes
GREEN := \033[0;32m
MAGENTA := \033[0;35m
BOLD := \033[1m
NC := \033[0m # Reset

all: $(NAME)
$(NAME): $(OBJS) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BONUS)
	@echo "$(GREEN)$(BOLD)Successful $(NAME) Compilation$(NC)"
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR):
	mkdir -p $@
clean:
	$(RM) $(OBJ_DIR) $(BONUS_OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
-include $(OBJS:%.o=%.d)
.PHONY: all fclean clean re bonus
