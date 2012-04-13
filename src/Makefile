TARGET=mysqlcsv
CC=clang
CFLAGS=-g -DDEBUG -I../include -I/usr/local/include
LDFLAGS=-Wl,-L/usr/local/lib/mysql -lmysqlclient
SRCS=main.c sql.c misc.c
OBJS=main.o sql.o misc.o

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${LDFLAGS} ${OBJS}

clean:
	rm -f *.o ${TARGET}
