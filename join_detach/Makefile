# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -pthread

# Список исходных файлов
SRCS = task_a.c task_b.c task_c.c task_d.c task_e.c task_f.c

# Получаем имена исполняемых файлов (заменяем .c на пустоту)
TARGETS = $(SRCS:.c=)

# Цель по умолчанию — собираем все программы
all: $(TARGETS)

# Правило для сборки каждого исполняемого файла из соответствующего .c файла
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Очистка собранных бинарников
clean:
	rm -f $(TARGETS)

.PHONY: all clean