NAME = webserv

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation de $(NAME) terminée!$(RESET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@echo "Objects supprimés."

fclean: clean
	rm -rf $(NAME)
	@echo "Exécutable supprimé."

re: fclean all

.PHONY: all clean fclean re
