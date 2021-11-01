NAME				=	pipex
NAME_BONUS			=	pipex_bonus

BONUS 				=   bonus

SRC_PATH			= ./srcs/
OBJ_PATH			= bin/
OBJ_BONUS_PATH		= bin/bonus/

MAIN_PATH		= main/
COMMON_PATH		= common/

CFLAGS		+=	-W -Wall -Wextra -D BUFFER_SIZE=32 -g3 #-Werror  -pedantic 		## '+=' allow to keep default flags.

MAIN_FILES				=	
ifdef WITH_BONUS
	CFLAGS	+= -DBONUS -DIF_BONUS=true

	MAIN_FILES				+=	main_bonus.c
	OBJ_PATH	= $(OBJ_BONUS_PATH)
	NAME	=	$(NAME_BONUS)
else
	CFLAGS	+= -DIF_BONUS=false
	MAIN_FILES				+=	main.c main_int.c
endif


OBJ_PATHS_INIT			=	$(addprefix $(OBJ_PATH),$(MAIN_PATH) 	\
													$(COMMON_PATH))
OBJ_PATHS_INIT			+= 	$(OBJ_PATH)
## No need for a \ on the last line
HEADERS_FILES				=	main.h
COMMON_FILES				=	free_array.c \
								ft_putchar_fd.c \
								ft_putendl_fd.c \
								ft_putnbr_fd.c \
								ft_putstr_fd.c \
								ft_split.c \
								ft_strdup.c \
								ft_strjoin.c \
								ft_strlcat.c \
								ft_strlcpy.c \
								ft_strlen.c \
								ft_strncmp.c


SRC_FILES += $(addprefix $(MAIN_PATH), $(MAIN_FILES))
SRC_FILES += $(addprefix $(COMMON_PATH), $(COMMON_FILES))


OBJREGULAR_FILES	= 	$(SRC_FILES:.c=.o)  ## get all .o names from .c names


SRC	= $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ	= $(addprefix $(OBJ_PATH), $(OBJREGULAR_FILES))

CC			=	clang

LDFLAGS		=	

RM			= 	rm -f

all					:	 $(OBJ_PATHS_INIT) $(NAME)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c $(HEADERS_FILES)
	$(CC) -o $@ -c $< $(CFLAGS)  $(INC) 

$(OBJ_PATHS_INIT)	:
	mkdir -p  $@  

$(NAME)			: 	$(OBJ) 
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)  $(INC) 

$(BONUS)		:
	echo $(BONUS) $(WITH_BONUS) $(NAME) $(OBJ_PATHS_INIT) 
	$(MAKE) WITH_BONUS=1 all


clean_local		:									## delete all .o
	$(RM) -rf $(OBJ_PATH) $(OBJ_BONUS_PATH)

clean			: clean_local							## delete all .o

fclean			:	clean_local							## clean + delete executable
	$(RM) $(NAME) $(BONUS) 

re				:	fclean all							## delete all .o and recompile all. Must use when editing a .h

.PHONY			:	all bonus clean fclean re
## voir dependances plus tard 
