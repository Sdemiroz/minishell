NAME := minishell
.DEFAULT_GOAL := all
CC := cc
AR := ar
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

LIBFT	:= ./libft/libft.a

OBJ_DIR := _obj

INC_DIRS := Includes \
			libft \
			libft/garbage_collector


SRC_DIRS := src \
			lexer \



# Tell the Makefile where headers and source files are
vpath %.hpp $(INC_DIRS)
vpath %.cpp $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

MAIN_FILE := main.c

# SRC_TEST_MAIN := main_tests.c

SRC_FILES := init_mini.c tests.c signals.c

LEXER_EXPANDER_FILES := lexer.c read_tokens.c expander.c expander_utils.c
LEXER_EXPANDER_REPO := $(addprefix lexer_expander/, $(LEXER_EXPANDER_FILES))

PARSING_FILES := parsing.c parsing_utils.c
PARSING_REPO := $(addprefix parsing/, $(PARSING_FILES))

EXECUTION_FILES := execution.c execution_utils_1.c execution_utils_2.c execution_utils_3.c
EXECUTION_REPO := $(addprefix execution/, $(EXECUTION_FILES))

BUILT_INS_FILES := cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILT_INS_REPO := $(addprefix built_ins/, $(BUILT_INS_FILES))

#Combines all
MELTING_POT :=	$(SRC_REPO) \
				$(SRC_FILES) \
				$(DUMMY_REPO) \
				$(LEXER_EXPANDER_REPO) \
				$(PARSING_REPO) \
				$(EXECUTION_REPO) \
				$(BUILT_INS_REPO)

# SRCS := $(MAIN_FILE) $(addprefix src/, $(MELTING_POT))
SRC_IN_SRC := $(SRC_FILES)
SRCS := $(MAIN_FILE) $(addprefix src/, $(SRC_IN_SRC)) $(LEXER_EXPANDER_REPO) $(PARSING_REPO) $(EXECUTION_REPO) $(BUILT_INS_REPO)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I$(INC_DIRS)
CFLAGS :=	-Wall -Werror -Wextra -Wpedantic -Wshadow -Wno-shadow \
			-Wconversion -Wsign-conversion -g -MMD -MP \
			$(addprefix -I, $(INC_DIRS))
CFLAGS_SAN := $(CFLAGS) -fsanitize=address
LDFLAGS := -lncurses -lreadline
LDFLAGS_SAN := -lncurses -fsanitize=address -lreadline
ARFLAGS := -rcs

# ANSI color codes
GREEN := \033[0;32m
MAGENTA := \033[0;35m
BOLD := \033[1m
NC := \033[0m # Reset

#Test/Playground exec.
NAME_TEST=tests.out

all:  $(LIBFT) $(NAME)

# $(NAME): $(OBJS) $(HDR_CHECK)
$(NAME): $(OBJS) $(LIBFT)
#$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Successful Compilation$(NC)"

# Rule to compile .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the directories exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C ./libft

clean:
	$(RM) $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	$(RM) $(NAME) $(NAME_TEST)
	@make fclean -C ./libft
	@echo "$(MAGENTA)$(BOLD)Executable + Object Files cleaned$(NC)"

re: fclean submodule_update all

submodule_update:
	git submodule update --remote --merge

bonus: all

# san: fclean
# 	make CFLAGS="$(CFLAGS_SAN)" LDFLAGS="$(LDFLAGS_SAN)"
# 	@echo "$(GREEN)$(BOLD)Successful Compilation with fsan$(NC)"
san:
	make CFLAGS="$(CFLAGS_SAN)" LDFLAGS="$(LDFLAGS_SAN)"
	@echo "$(GREEN)$(BOLD)Successful Compilation with fsan$(NC)"

re_sub: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

debug: clean
debug: CFLAGS += -DDEBUG
debug: $(NAME)

redebug: fclean debug

test:
	make $(NAME_TEST) MAIN_FILE="$(SRC_TEST_MAIN)" NAME=$(NAME_TEST)

retest: fclean test

-include $(OBJS:%.o=%.d)

.PHONY: all clean fclean re bonus re_sub submodule_rebuild san debug test
