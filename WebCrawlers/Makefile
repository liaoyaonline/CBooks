#定义编译器
all: main.o mysqlplus.o regexplus.o
	gcc -o bin/regexbook main.o mysqlplus.o regexplus.o -g -lmysqlclient -lcurl
main.o:
	gcc -c -I./include ./src/main.c
mysqlplus.o:
	gcc -c -I./include ./include/mysqlplus/mysqlplus.c
regexplus.o:
	gcc -c -I./include ./include/regexplus/regexplus.c
.PHONY:clean
clean:
	rm ./*.o
