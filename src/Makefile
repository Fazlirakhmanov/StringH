CHECK =  $(shell pkg-config --libs --cflags check)
#$(shell pkg-config --libs --cflags check) - позволяет получить путь к библиотеке check.h и её заголовочному файлу,  а также её имя 
CFLAGS = -Wall -Werror -Wextra -std=c11 -g 
SRCS = $(wildcard *.c)
EXCLUDE = s21_string_tests.c main.c
SOURCES = $(filter-out $(EXCLUDE), $(SRCS))
OBJECTS = $(SOURCES:.c=.o)
TESTS = s21_string_tests.o
S21LIB = s21_string.a
# пишет название текущей ОС
UNAME = $(shell uname -s)
FLAGS = -lcheck

#если ОС - Linux
ifeq ($(UNAME), Linux)
	FLAGS +=  -lm -lsubunit
  	OPEN=xdg-open
#если ОС - Darvin
else
	FLAGS += -fprofile-arcs -ftest-coverage
 	OPEN=open
endif

all: test

# $^ -  всё что идет после цели 
# $< - то что идет сразу после цели 
test: $(TESTS) $(S21LIB)
# связывание тестов с библиотекой
	gcc  $^ -o test $(CFLAGS) $(CHECK) $(FLAGS)  
	rm -rf *.o 
	./test
# $@ -  название цели 
$(TESTS): $(TESTS:.o=.c)
	gcc $(CFLAGS) -c $^  -o $@  $(CHECK)


mytest: 
	gcc $(CFLAGS) -o string $(SOURCES) main.c -lm


#создание стат. библиотеки	
$(S21LIB): $(OBJECTS)
	gcc $(CFLAGS) -c $(SOURCES) 
# Опция c заставляет создавать (от create) библиотеку, если ее нет,
# а опция r (от replace) заменяет старые объектные файлы новыми версиями.
	ar rc $@ $^
#Пока у нас есть лишь архивный файл libfs.a. 
#Чтобы из него сделать полноценную библиотеку объектных файлов надо добавить к этому архиву
# индекс символов, т.е. список вложенных в библиотеку функций и переменных, 
#чтобы линковка происходила быстрее	
	ranlib $@

style:
	clang-format -n -style=Google *.c *.h
	clang-format -i -style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h	

rebuild: clean all
#очищение предыдущих результатов тестов
gcov_report: clean $(TESTS)
#переделать
	gcc -o test $(FLAGS) --coverage $(TESTS) $(SOURCES)
	./test
#Сбор информации о покрытии кода
#-c указывает, что lcov должен использовать существующие данные о coverage
#-d <путь> устанавливает каталог, в котором надо искать данные о coverage, и мы передаём текущий каталог “.”
	lcov -t "a.out" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf test *.o *.a *gcda *gcno *info

clean:
	rm -rf test *.o *.a *.gch *.gcda report *.gcno *.info

.PHONY: all, test, style, rebuild, gcov_report, clean
