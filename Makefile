NAME := fractol

CC := cc
CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -Ofast

LIBFT_DIR := ./lib/libft
LIBMLX_DIR := ./lib/MLX42
LIB_MLX := $(LIBMLX_DIR)/build/libmlx42.a
LIBFT := $(LIBFT_DIR)/libft.a
LIBS := $(LIB_MLX) $(LIBFT)
HEADERS := -I ./include -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)

SRCS := $(shell find ./src -iname "*.c")
OBJS := $(SRCS:.c=.o)

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    MLX_FLAGS := -ldl -lglfw -pthread -lm
else ifeq ($(UNAME), Darwin) # macOS
    MLX_FLAGS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(OS), Windows_NT)
    MLX_FLAGS := -lglfw3 -lopengl32 -lgdi32
else
    $(error Unsupported OS: $(UNAME))
endif

all: make_libft make_libmlx $(NAME)

make_libmlx:
	@cmake -S $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@cmake --build $(LIBMLX_DIR)/build -j4

make_libft:
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

debug: $(OBJS)
	@$(CC) -g $(HEADERS) src/*.c $(LIBS) $(MLX_FLAGS) -o pouet
	lldb pouet
	rm pouet

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@cmake --build $(LIBMLX_DIR)/build --target clean

fclean: clean
	rm -rf $(LIBMLX_DIR)/build
	cmake -S $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_libmlx make_libft
