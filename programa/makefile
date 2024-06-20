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
	./virtualSocket ../tmp/p1 ../tmp/p2
red: 
	./virtualSocket ../tmp/p1 ../tmp/p2 &.
	./virtualSocket ../tmp/p3 ../tmp/p4 &.
	./virtualSocket ../tmp/p5 ../tmp/p6 &.
	./virtualSocket ../tmp/p7 ../tmp/p8 &.
	./virtualSocket ../tmp/p9 ../tmp/p10 &.
run_nodo_A_B:
	./nodo A.A.A.A ../tmp/p1 ../tmp/p2
run_nodo_B_C:
	./nodo A.A.A.A ../tmp/p3 ../tmp/p4
run_nodo_C_D:
	./nodo A.A.A.A ../tmp/p5 ../tmp/p6
run_nodo_D_E:
	./nodo A.A.A.A ../tmp/p7 ../tmp/p8
run_nodo_E_A:
	./nodo A.A.A.A ../tmp/p9 ../tmp/p10
clean:
	rm *.o