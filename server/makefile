INC=-I/home/pai/cpprestsdk/Release/include/cpprest
fin : Main.o MyServer.o stdafx.o multipart_parser.o
	g++ -o fin Main.o MyServer.o stdafx.o multipart_parser.o -lboost_thread -lboost_system -lboost_filesystem -lcrypto -lssl -lcpprest -pthread -lz
Main.o : Main.cpp stdafx.h MyServer.h
	g++ -c Main.cpp
MyServer.o : MyServer.cpp stdafx.h messagetypes.h MyServer.h cmdm.h
	g++ -c MyServer.cpp
stdafx.o : stdafx.cpp stdafx.h
	g++ -c stdafx.cpp
multipart_parser.o : multipart_parser.cpp multipart_parser.h
	g++ -c multipart_parser.cpp