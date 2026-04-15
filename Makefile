CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = program
TEST_TARGET = tests

SRCS = main.cpp City.cpp Testing.cpp
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = Testing.cpp City.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $(TEST_TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)