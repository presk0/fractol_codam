NAME := fractol

# Compiler and flags
CC := clang
CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -Ofast

LIBFT_DIR := ./lib/libft
LIBMLX_DIR := ./lib/MLX42
LIB_MLX := $(LIBMLX_DIR)/build/libmlx42.a
LIBFT := $(LIBFT_DIR)/libft.a
LIBS := $(LIB_MLX) $(LIBFT)
HEADERS := -I ./include -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)

# Source and object files
SRCS := $(shell find ./src -iname "*.c")
OBJS := $(SRCS:.c=.o)

# OS-specific MLX flags
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

# Main target
all: make_libft make_libmlx $(NAME)

# Build MLX
make_libmlx:
	@cmake -S $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@cmake --build $(LIBMLX_DIR)/build -j4

# Build Libft
make_libft:
	@make -C $(LIBFT_DIR)

# Object file compilation
%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Link the final binary
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

# Clean object files
clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@cmake --build $(LIBMLX_DIR)/build --target clean

# Clean everything
fclean: clean
	rm -rf $(LIBMLX_DIR)/build
	cmake -S $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re make_libmlx make_libft
