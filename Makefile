# Standard
NAME				= minishell

# Directories
LIBFT				= ./libft/libft.a
SRC_DIR				= ./
OBJ_DIR				= obj/
INC					= .

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I $(INC)
RM					= rm -f

# Source Files
SRCS				= $(wildcard $(SRC_DIR)*.c)

# Object Files
OBJ					= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Build rules
all:				$(NAME)

$(NAME):			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
					@echo "$(NAME) created successfully!"

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c minishell.h
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
					@make -C ./libft

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft

fclean:				clean
					@$(RM) $(NAME)
					@make fclean -C ./libft

re:					fclean all

.PHONY:				all clean fclean re
