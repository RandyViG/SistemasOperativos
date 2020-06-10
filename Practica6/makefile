run:	productor.c consumidor.c
	gcc productor.c -lpthread -lrt -o productor
	gcc consumidor.c -lpthread -lrt -o consumidor
	echo -e " Productor 1: aaa "
	./productor 1 &
	echo -e " Productor 2: aaa "
	./productor 2 &
	echo -e " Productor 3: aaa "
	./productor 3 &
	echo -e " Productor 4: aaa "
	./productor 4 &
	echo -e " Consumidor 1"
	./consumidor 4 &
	echo -e " Consumidor 2"
	./consumidor 4 &
	echo -e " Consumidor 3"
	./consumidor 4 &
	echo -e " Consumidor 4"
	./consumidor 4 &

clean:
	rm -f productor consumidor *.txt
