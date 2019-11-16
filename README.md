# UDP Server/Client for Windows

 UDP Server/Client for Windows, with winsock 2.2.

# Code Information

 The code were created using "Code :: Blocks IDE" and I used "GNU Compiler for C / C ++".                          
 Libraries: <stdio.h>, <string.h>, <winsock2.h>                                                                                      
 This code is tested on Windows 10 Pro(32/64-bit).                                         

# Recommendations
                                                              
 I recommend download the entire projects(Server/Client) and open it with "Code :: Blocks IDE", for the best performance.
    
# Description

 This is a communication model between Server and Client(s) with User Datagram Protocol(UDP) , that runs on
 Windows operating systems with the help of <winsoc2.h> library.                                             
                                                                                                                     
# Server

 This is a UDP Server, written in C programming language, that can run on Windows operating systems, 
 with the help of <winsoc2.h> library.
 It can accept more than one parallel communications with Clients, sending messages and receiving data packets from them.
 Program is also updates user(Server Administrator), with messages(Success, Error, etc).                                         
 (You can find more information in comments in the source code file "server.c".)                                         
 
 # Client

 This is a UDP Client, written in C programming language, that can run on Windows operating systems, 
 with the help of <winsoc2.h> library.
 It connects with a Server, asks user for data packages(messages) and send them to a receiver(Server).
 Program is also updates user(Client), with messages(Success, Error, etc).                                 
 (You can find more information in comments in the source code file "client.c".)   
