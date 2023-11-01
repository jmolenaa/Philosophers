RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

NAME = philo
SRC = main.c error.c utils.c parse.c init.c time.c simulation.c philo_life_cycle.c big_brother.c
OBJ = $(SRC:%.c=obj/%.o)
OBJ_DIR = obj
HEADERS = includes/philo.h

# compilation variables
CC = gcc
INCLUDES = -I includes
ifdef DEBUG
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
else
CFLAGS = 
endif
ifdef COLOUR
COLOUR_FLAG = -D COLOUR=0
else
COLOUR_FLAG = 
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo "${YELLOW}Compiling $@${END}"
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "${GREEN}Done compiling${END}"

obj/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $(<:src/%=%)$(END)"
	@$(CC) $(COLOUR_FLAG) $(CFLAGS) $(INCLUDES) $< -o $@ -c

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@echo "${RED}Removing obj files${END}"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "${RED}Removing binary${END}"
	@rm -rf $(NAME)

re: fclean all

d: fclean
	@$(MAKE) DEBUG=1

c: fclean
	@$(MAKE) COLOUR=1
