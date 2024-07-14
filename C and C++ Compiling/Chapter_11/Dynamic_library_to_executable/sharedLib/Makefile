g++ -Wall -O0 -fPIC -I./exports/ -c ./src/executableSharedlib.c -o ./src/executableSharedLib.o
g++ -shared -Wl,-e,main ./src/executableSharedLib.o -pthread -lm -ldl -o ../deploy/libexecutablesharedLib.so
cd ../testApp
g++ -Wall -O2 -I../sharedLib/exports/ -c src/main.c -o src/main.o
g++ ./src/main.o -lpthread -lm -ldl -L../deploy -lexecutablesharedLib -Wl,-Bdynamic -Wl,-R../deploy -o demoApp
./demoApp
cd ../deploy/
./libexecutablesharedLib.so

