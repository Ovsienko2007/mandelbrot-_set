CC = g++

CFLAGS = -O3 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef \
         -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations \
         -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ \
         -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion \
         -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
         -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
         -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo \
         -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits \
         -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE -I$(DIR_INCLUDE)

DIR_INCLUDE = Include
DIR_SOURCE  = Source
DIR_BUILD   = Build
DIR_DUMP    = DUMP


# Флаги для SDL2
SDL_FLAGS = `sdl2-config --cflags --libs`

# SIMD флаг
SIMD_FLAGS = -msse2

# Находим все .cpp файлы
SOURCES = $(wildcard $(DIR_SOURCE)/*.cpp)
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

EXECUTABLE = sdl_rect.exe

# Цели
.PHONY: all clean start dump

all: make_folder $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(addprefix $(DIR_BUILD)/, $(OBJECTS)) -o $(DIR_BUILD)/$@ $(SDL_FLAGS)
	@echo "Готово! Запустите: make start"

# Правило для .cpp файлов
$(OBJECTS): %.o: $(DIR_SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(SIMD_FLAGS) $(SDL_FLAGS) -c $< -o $(DIR_BUILD)/$@

make_folder:
	mkdir -p $(DIR_BUILD)
	mkdir -p $(DIR_DUMP)
	@echo "Папки созданы!"

start:
	./$(DIR_BUILD)/$(EXECUTABLE)

dump:
	@for file_dot in $(wildcard $(DIR_DUMP)/*.dot); do \
		dot -Tpng $$file_dot -o $${file_dot%.dot}.png; \
	done

clean:
	rm -rf $(DIR_BUILD)