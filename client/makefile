INC=-I/home/pai/cpprestsdk/Release/include/cpprest
fin : client.o multipart_parser.o
	g++ -o fin client.o multipart_parser.o -lboost_system -lboost_filesystem -lcrypto -lssl -lcpprest -pthread
client.o : client.cpp
	g++ -c client.cpp
multipart_parser.o : multipart_parser.cpp multipart_parser.h
	g++ -c multipart_parser.cpp