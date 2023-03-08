NAME = containers

HEADERS = ./_Rb_tree.hpp ./iterators.hpp ./map.hpp ./pair.hpp ./reverse_iterator.hpp ./set.hpp ./stack.hpp ./utility.hpp ./vector.hpp
MAIN	= ./main.cpp

$(NAME): $(HEADERS) $(MAIN)
	c++ --std=c++98 $(MAIN) -o $(NAME)

all: $(NAME)

clean :
	rm -rf containers

re : clean all


