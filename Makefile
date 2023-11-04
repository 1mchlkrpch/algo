TARGET := sorts/bin_search.cpp
EXECUTABLE := algo

all: $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): $(TARGET)
	g++ -g -Wno-unused-variable -Waggressive-loop-optimizations -Wall -Wextra -Wpedantic $< -o $@
# 
clean:
	@rm $(EXECUTABLE)
