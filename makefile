db: db.o buffer.o table.o pager.o btree.o
	gcc db.o buffer.o table.o pager.o btree.o -o db

db.o: db.c
	gcc -c db.c -o db.o

buffer.o: buffer.c buffer.h
	gcc -c buffer.c -o buffer.o

pager.o: pager.c pager.h
	gcc -c pager.c -o pager.o

table.o: table.c table.h
	gcc -c table.c -o table.o

btree.o: btree.c btree.h
	gcc -c btree.c -o btree.o

run: db
	./db mydb.db

test: db
	bundle exec rspec

clean:
	rm -f db db.o buffer.o table.o pager.o btree.o *.db

format: *.c
	clang-format -style=Google -i *.c