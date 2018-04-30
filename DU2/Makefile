CC = clang
CXX = clang++

CFLAGS = -std=c99 -pedantic -Wall -Wextra -g
CPPFLAGS = -std=c++11 -pedantic -Wall -g

all: tail tail2 wordcount wordcount-dynamic

tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

tail2: tail2.cc
	$(CXX) $(CPPFLAGS) -o tail2 tail2.cc

wordcount: wordcount.c io.c htab.h htab_private.h htab_bucket_count.c htab_find.c htab_free.c htab_init.c htab_move.c htab_remove.c htab_clear.c htab_foreach.c htab_hash_function.c htab_lookup_add.c htab_size.c
	$(CC) $(CFLAGS) -c htab_bucket_count.c   
	$(CC) $(CFLAGS) -c htab_find.c
	$(CC) $(CFLAGS) -c htab_free.c           
	$(CC) $(CFLAGS) -c htab_init.c           
	$(CC) $(CFLAGS) -c htab_move.c           
	$(CC) $(CFLAGS) -c htab_remove.c
	$(CC) $(CFLAGS) -c htab_clear.c          
	$(CC) $(CFLAGS) -c htab_foreach.c        
	$(CC) $(CFLAGS) -c htab_hash_function.c  
	$(CC) $(CFLAGS) -c htab_lookup_add.c     
	$(CC) $(CFLAGS) -c htab_size.c
	ar rcs libhtab.a htab_bucket_count.o htab_find.o htab_free.o htab_init.o htab_move.o htab_remove.o htab_clear.o htab_foreach.o htab_hash_function.o htab_lookup_add.o htab_size.o
	$(CC) $(CFLAGS) -o wordcount wordcount.c -L. -lhtab

wordcount-dynamic:wordcount.c io.c htab.h htab_private.h htab_bucket_count.c htab_find.c htab_free.c htab_init.c htab_move.c htab_remove.c htab_clear.c htab_foreach.c htab_hash_function.c htab_lookup_add.c htab_size.c
	$(CC) $(CFLAGS) -c -fPIC htab_bucket_count.c   
	$(CC) $(CFLAGS) -c -fPIC htab_find.c
	$(CC) $(CFLAGS) -c -fPIC htab_free.c           
	$(CC) $(CFLAGS) -c -fPIC htab_init.c           
	$(CC) $(CFLAGS) -c -fPIC htab_move.c           
	$(CC) $(CFLAGS) -c -fPIC htab_remove.c
	$(CC) $(CFLAGS) -c -fPIC htab_clear.c          
	$(CC) $(CFLAGS) -c -fPIC htab_foreach.c        
	$(CC) $(CFLAGS) -c -fPIC htab_hash_function.c  
	$(CC) $(CFLAGS) -c -fPIC htab_lookup_add.c     
	$(CC) $(CFLAGS) -c -fPIC htab_size.c	
	$(CC) -shared -o libhtab.so htab_bucket_count.o htab_find.o htab_free.o htab_init.o htab_move.o htab_remove.o htab_clear.o htab_foreach.o htab_hash_function.o htab_lookup_add.o htab_size.o
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.c -L. -lhtab

clean:
	rm -f *.o *.a *.so tail tail2 wordcount wordcount-dynamic
