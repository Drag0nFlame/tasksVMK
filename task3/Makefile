#компилятор, который будет использоваться
CC = gcc

#флаги компиляции (опции)
CFLAGS = -Wall -Wextra -std=c99 -pedantic

#объектные файлы (промежуточные файлы .o)
OBJS = main.o list.o

#имя итогового исполняемого файла
TARGET = word_processor

#цель по умолчанию то, что выполнится при простом вызове 'make'
all: $(TARGET)

#как собрать итоговую программу из объектных файлов
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

#как компилировать main.o
main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

#как компилировать list.o
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

#очистка - удаление всех созданных файлов
clean:
	rm -f $(OBJS) $(TARGET)

#указываем, что эти цели не являются реальными файлами
.PHONY: all clean
