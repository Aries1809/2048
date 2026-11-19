NAME		= 2048

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -MMD -MP -I$(INC_DIR)
LDFLAGS		=
LDLIBS		= -lncurses
DEBUG		?= 0
RM			= rm -f

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
ifneq ($(wildcard $(LIBFT_DIR)/Makefile),)
LIBS		= $(LIBFT)
CPPFLAGS	+= -I$(LIBFT_DIR)
else
LIBS		=
endif

JOBS		?= $(shell nproc)
MAKEFLAGS	+= -j $(JOBS) -l $(JOBS) --no-print-directory

ifeq ($(DEBUG),1)
CFLAGS		+= -g3
CPPFLAGS	+= -DDEBUG=1
endif

SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS		= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi

fclean: clean
	$(RM) $(NAME)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -C $(LIBFT_DIR) fclean; fi

re:
	$(MAKE) fclean
	$(MAKE) all

debug:
	$(MAKE) re DEBUG=1

-include $(DEPS)

.PHONY: all clean fclean re debug
.DEFAULT_GOAL := all
