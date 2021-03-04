CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test bin/hashMap_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/hash.o: src/hash.c include/hash.h
	$(CC) $(CFLAGS) -c src/hash.c -o build/hash.o

bin/hashMap_app: include/hash.h build/hash.o hashMap_app/hashMap_app.c
	$(CC) $(CFLAGS) -o bin/hashMap_app build/hash.o hashMap_app/hashMap_app.c

bin/test: test/hashMap_tests.c build/hash.o include/hash.h
	$(CC) $(CFLAGS)  test/hashMap_tests.c build/hash.o Resources/C/Unity/unity.c -o bin/test
