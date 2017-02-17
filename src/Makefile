OBJS = main.o EventLoop.o TcpServer.o Acceptor.o InetAddress.o
CXX = g++
CXXFLAGS = -std=c++11

main : $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: EventLoop.h TcpServer.h
EventLoop.o: EventLoop.h
Acceptor.o: Acceptor.h EventLoop.h
TcpServer.o: TcpServer.h Acceptor.h EventLoop.h


.PHONY : clean
clean :
	-rm main $(OBJS)
