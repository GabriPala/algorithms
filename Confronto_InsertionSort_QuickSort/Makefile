CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test bin/sorted_array_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/sorted.o: src/sorted.c include/sorted.h
	$(CC) $(CFLAGS) -c src/sorted.c -o build/sorted.o

bin/sorted_array_app: include/sorted.h build/sorted.o sorted_array_app/sorted_array_app.c
	$(CC) $(CFLAGS) -o bin/sorted_array_app build/sorted.o sorted_array_app/sorted_array_app.c

bin/test: test/sorted_tests.c build/sorted.o include/sorted.h
	$(CC) $(CFLAGS)  test/sorted_tests.c build/sorted.o Resources/C/Unity/unity.c -o bin/test
