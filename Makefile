NAME = leaktest

COMPILATOR = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -pedantic -g3
OFLAGS = -Wall -Wextra -Werror -I./includes -pedantic -g3
DEBUG_FLAGS = -fsanitize=leak,address,undefined,integer,null,float-divide-by-zero

FILES = main \

SOURCES = $(foreach f, $(FILES), ./$(f).cpp)
OBJECTS = $(foreach f, $(FILES), ./$(f).o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(COMPILATOR) $(CFLAGS) -o $@ $^

./%.o: ./sources/%.cpp
	@mkdir -p $(dir $@)
	$(COMPILATOR) $(OFLAGS) -c $< -o $@

clean:
	rm -rf ./*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: OFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug
