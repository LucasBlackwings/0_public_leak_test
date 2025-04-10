NAME = leak_test
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -fsanitize=leak,address,undefined,integer,null,float-divide-by-zero

SOURCES =	main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean:
	rm -f $(NAME) $(OBJECTS)

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: OFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug