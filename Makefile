# Trình biên dịch
CXX = g++
CC = gcc

# Cờ biên dịch
CXXFLAGS = -std=c++17 -I./sql -Wall
CFLAGS = -I./sql -Wall

# File nguồn
CPP_SOURCES = src/main.cpp src/user.cpp src/ui.cpp src/Database.cpp
C_SOURCE = sql/sqlite3.c

# File đối tượng
CPP_OBJECTS = src/main.o src/user.o src/ui.o src/Database.o
C_OBJECT = sql/sqlite3.o

# Tên chương trình
TARGET = app.exe

# Luật mặc định
all: $(TARGET)

# Liên kết đối tượng thành chương trình
$(TARGET): $(CPP_OBJECTS) $(C_OBJECT)
	$(CXX) -o $@ $^

# Biên dịch các file C++
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Biên dịch file C (SQLite)
sql/%.o: sql/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dọn dẹp
clean:
	del /Q src\\*.o sql\\*.o $(TARGET) 2>NUL