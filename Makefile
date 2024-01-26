CC = g++ 
CFLAGS = -std=c++17 -Wall -Werror -pedantic
LFLAGS = -lboost_regex -lboost_date_time

all: clean ps7 lint

ps7: ps7.o
	$(CC) -o $@ ps7.o $(LFLAGS)

ps7.o: ps7.cpp 
	$(CC) $(CFLAGS) -c ps7.cpp -o ps7.o

clean:
	rm -f ps7 *.o

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *