//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "engine.h"
#include "helper.h"

int main () {
  //  Prepare our context and socket
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind ("tcp://*:5555");
  
  // create the engine instance
  Engine engine;

  while (true) {
    zmq::message_t request;

    //  Wait for next request from client
    socket.recv (&request);

    std::string message = std::string(static_cast<char*>(request.data()), request.size());

    std::cout << "received: " << message << std::endl;
  
    std::string output = engine.handleMessage(message);
   
    //  Send reply back to client 
    const char * myStringChars = output.c_str();
    
    // note: here I previously was calling sizeof(output) -> this was returning the size of the data type of string, not the size of the string stored in output 
    int size = output.size();
    std::cout << "data size: " << size << std::endl;
    zmq::message_t reply (size);
    memcpy ((void *) reply.data (), myStringChars, size);
    socket.send (reply);
  }
  
  return 0;
}
