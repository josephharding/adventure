I used brew to install zmq: brew install zeromq
but had to download a zmq.hpp from github: https://github.com/zeromq/cppzmq/blob/master/zmq.hpp
and copy it into /usr/local/include
to compile the cpp: g++ server.cpp -lzmq -o server
to compile the engine: g++ engine.cpp -std=c++11

to compile everything: g++ server.cpp engine.cpp -o server -lzmq -std=gnu++11
