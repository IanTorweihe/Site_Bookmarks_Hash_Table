CC = g++
CPPFLAGS = -std=c++11 -g -Wall
OBJS = app.o website.o table.o

app: $(OBJS)
	$(CC) $(CPPFLAGS) -o app $(OBJS)

app.o: website.h table.h

website.o: website.h

table.o: table.h website.h

valgrind: app
	valgrind --leak-check=full ./app

clean:
	rm -f app $(OBJS)
