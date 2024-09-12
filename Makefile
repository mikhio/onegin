CXX := clang++

SRC_PATH := ./src
APP_PATH := ./build/onegin
CCH_PATH := ./cpp_cache

SOURCES := $(wildcard $(SRC_PATH)/*.cpp)
OBJECTS := $(addprefix $(CCH_PATH)/, $(patsubst %.cpp, %.o, $(SOURCES)))

CXX_FLAGS := -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
   -Wc++14-compat -Wmissing-declarations -Wcast-qual -Wchar-subscripts                             \
   -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal           \
   -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline                   \
   -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked                     \
   -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
   -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                         \
   -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default               \
   -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast                    \
   -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing            \
   -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation             \
   -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192                  \
   -Wstack-usage=8192 -fPIE -Werror=vla -pedantic -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -fproc-stat-report=log

# Compiling and linking
$(APP_PATH): $(OBJECTS) 
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $^ -o $(APP_PATH)

$(CCH_PATH)/$(SRC_PATH)/%.o: $(SRC_PATH)/%.cpp ./inc/*.h Makefile
	@mkdir -p $(@D)
	$(CXX) -c $< -o $@

# Simplification
.PHONY: build
build: $(APP_PATH)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(DEPENDS) $(APP_PATH)

.PHONY: run
run:
	$(APP_PATH)

.PHONY: docs
docs: Doxyfile
	doxygen Doxyfile

.PHONY: all
all:
	make clean
	make build
	make run

