CXX = g++
CXXFLAGS = -std=c++11

SRC = main.cpp
TARGET = myLibrary

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET) library_books.csv

clean:
	rm -f $(TARGET)
