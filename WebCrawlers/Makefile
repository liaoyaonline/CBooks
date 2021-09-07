#定义编译器
all: regexbook4.o mysqlplus.o
	gcc -o bin/regexbook regexbook4.o mysqlplus.o -g -lmysqlclient -lcurl
regexbook4.o:
	gcc -c -I./include ./src/regexbook4.c
mysqlplus.o:
	gcc -c -I./include ./include/mysqlplus/mysqlplus.c
.PHONY:clean
clean:
	rm ./*.o
