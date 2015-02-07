
import zmq
import json
from bottle import route, run, template

context = zmq.Context()


def parse_response(response):
  print "response: {r}".format(r=response)
  return json.loads(response);

@route('/start')
def index():
    
  # socket to talk to server
  print("Connecting to engine server...")

  socket = context.socket(zmq.REQ)
  socket.connect("tcp://localhost:5555")
  socket.send("0,-1")

  response = parse_response(socket.recv())
  response['choice'] = 0
  return template('choice', data=response)

@route('/<choice>/<index>')
def choose(choice, index):
  
  socket = context.socket(zmq.REQ)
  socket.connect("tcp://localhost:5555")
  socket.send(choice + "," + index)

  response = parse_response(socket.recv())
  response['choice'] = response['choiceindex']
  return template('choice', data=response)

run(host='localhost', port=8080)


