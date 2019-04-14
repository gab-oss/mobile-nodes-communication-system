mkdir obj
mkdir bin
g++ src/network.cpp -c -o obj/network.o
g++ obj/network.o src/client_app.cpp -o bin/client
g++ obj/network.o src/server_app.cpp -o bin/server