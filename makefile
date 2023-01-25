cc := g++

all: a.out

a.out: main.o Client.o Publisher.o Film.o System.o Comment.o Notification.o Input.o Error.o
	$(cc) main.o Client.o Publisher.o Film.o System.o Comment.o Notification.o Input.o Error.o -o a.out

main.o: main.cpp System.h Input.h
	$(cc) -c main.cpp

System.o: System.cpp System.h
	$(cc) -c System.cpp

Client.o: Client.cpp Client.h Film.h
	$(cc) -c Client.cpp

Publisher.o: Publisher.cpp Publisher.h Film.h Client.h Notification.h
	$(cc) -c Publisher.cpp

Film.o: Film.cpp Film.h Comment.h
	$(cc) -c Film.cpp

Comment.o: Comment.cpp Comment.h
	$(cc) -c Comment.cpp

Notification.o: Notification.cpp Notification.h
	$(cc) -c Notification.cpp -o Notification.o

Input.o: Input.cpp Input.h Error.h System.h
	$(cc) -c Input.cpp

Error.o: Error.cpp Error.h
	$(cc) -c Error.cpp

.PHONY: clean
clean:
	rm *.o
	rm a.out

