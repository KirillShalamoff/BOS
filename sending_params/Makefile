CC = gcc
CFLAGS = -Wall -Wextra -pthread -g

# Имена исполняемых файлов
TARGETS = 1_3a 1_3b

all: $(TARGETS)

1_3a: 1_3a.c
	$(CC) $(CFLAGS) $< -o $@

1_3b: 1_3b.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean