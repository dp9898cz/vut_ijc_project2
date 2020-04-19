#    Daniel Pátek (xpatek08)
#    VUT FIT
#    IJC - Projekt 2
#    19.4.2020
#    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0

C=gcc -std=c99 -pedantic -Wall -Wextra -g -O

all: tail libhtab.a libhtab.so wordcount wordcount-dynamic

#tail program
tail: tail.o
	$(C) tail.o -o tail
tail.o: tail.c
	$(C) -c tail.c -o tail.o

#wordcount program
wordcount: wordcount.o io.o libhtab.a
	$(C) $^ -o $@
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(C) $^ -o $@
wordcount.o: wordcount.c
	$(C) -c $<
io.o: io.c io.h
	$(C) -c $<

#libhtab.a (static library)
libhtab.a: htab_begin.o htab_bucket_count.o htab_clear.o htab_end.o htab_erase.o htab_find.o htab_free.o htab_hash_function.o htab_init.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_next.o htab_iterator_set_value.o htab_lookup_add.o htab_size.o
	ar rcs $@ $^

#libhtab.so (dynamic library)
libhtab.so: htab_begin.o htab_bucket_count.o htab_clear.o htab_end.o htab_erase.o htab_find.o htab_free.o htab_hash_function.o htab_init.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_next.o htab_iterator_set_value.o htab_lookup_add.o htab_size.o
	$(C) -fPIC -shared $^ -o $@

#patter rule for library .o files
%.o: %.c
	$(C) -fPIC -c $< htab.h htab_struct.h

#clean
clean: 
	rm -f *.o *.gch tail libhtab.a libhtab.so wordcount wordcount-dynamic

#pack
pack:
	zip xpatek08.zip *.c *.h Makefile
