# irc
Simple IRC chat program.

# Setting up the server
Using python3, just simply use the code
```
sudo python3 server.py
```
or
```
sudo python3 server.py -l logfile.txt
```
if you want it to log connections.
Also if you are hosting the server for outside connections, port-forward on port 8080.

# Compiling and running the client.
You can compile it with
```
gcc client.c -lpthread -w
```
and then run it.
It will ask for your handle (username), and the server to connect to.
Once running it should show you all the chat history. You can simply type and hit enter to send messages.
