all:
	g++ -Wall serial.cpp -c
	g++ -Wall slip.cpp -c
	g++ -Wall chat.cpp -c
	g++ -Wall nodo.cpp -c
	g++ -Wall slip.o serial.o chat.o -o chat
	g++ -Wall slip.o serial.o nodo.o -o nodo
mk_socket:
	g++ -Wall virtualSocket.cpp -o virtualSocket
run_socket_1_2:
	./virtualSocket tmp/p1 tmp/p2
run_nodo_A_B:
	./nodo
run_nodo_B_C:
run_nodo_C_D:
run_nodo_D_E:
clean:
	rm *.o