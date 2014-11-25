FLAGS = -std=c++0x  -m64 -pipe -g -w -D_REENTRANT -Wall -Wextra -fpermissive -I/usr/include/freetype2
#FLAGS = -D_DEBUG_ -std=c++0x  -m64 -pipe -g -w -D_REENTRANT -Wall -Wextra -fpermissive -I/usr/include/freetype2
LIBS = -L/opt/intel/composerxe/ipp/lib/intel64 -L/usr/X11R6/lib64 -L/usr/lib -lippcore -lippcc -lippi -lipps -ltbb -lcurl -Wno-traditional -lfreetype  -lpng

all: a.out

a.out: main.o feed.o
	g++ $(LIBS) $(FLAGS) $(EFLAGS) main.o feed.o -o a.out

main.o: main.cpp
	g++ $(FLAGS) $(EFLAGS) -c main.cpp

feed.o: feed.cpp
	g++ $(FLAGS) $(EFLAGS) -c feed.cpp

install:
	install -s -m 755 a.out /usr/local/bin/loki
	install loki.1 /usr/local/man/man1

clean:
	-rm -f a.*
	-rm -f *.o
	-rm -f *~ core *.core
	-rm -f out

