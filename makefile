all:
	g++ -Wall serial.cpp -c
	g++ -Wall slip.cpp -c
	g++ -Wall chat.cpp -c
	g++ -Wall slip.o serial.o chat.o -o chat
mk_socket:
	g++ -Wall virtualSocket.cpp -o virtualSocket
run_socket_1_2:
	./virtualSocket tmp/p1 tmp/p2
clean:
	rm *.o