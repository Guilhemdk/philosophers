NAME    = philosophers
CC      = gcc
RM      = rm -rf
CFLAGS  = -Wall -Wextra -fsanitize=thread -D_DEFAULT_SROUCE
GREEN   = "\\033[32m"
YELLOW	= "\\033[33m"
NC      = "\\033[0m"

SRCS = 	main.c \
   		Reaper.c \
		dinner.c \
		errors.c \
		init.c \
		mutex_get_set.c \
		thread_management.c \
		time.c \
		utils.c \
		write.c

SRC_DIR = src/
OBJ_DIR = obj/
OBJS    = $(SRCS:%.c=$(OBJ_DIR)%.o)

INC_DIR 	= includes/
INCS 		= -I$(INC_DIR)

TOTAL_FILES 	:= $(words $(SRCS))
CURRENT_FILE  	:= 0

define progress_bar
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "\r$(YELLOW)Compiling push_swap... [%-$(TOTAL_FILES)s] %d/%d $(NC)" \
	$$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -g -c $< -o $@
	$(call progress_bar)


all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking objects to create executable...$(NC)"
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -fsanitize=thread
	@echo "$(GREEN)Executable $(NAME) created!$(NC)"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
