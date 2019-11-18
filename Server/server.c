#include <winsock2.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

     WSADATA wsaData;
     SOCKET ReceivingSocket;
     SOCKADDR_IN ReceiverAddr;
     int Port = 8888;
     char ReceiveBuf[1024];
     int BufLength = 1024;
     SOCKADDR_IN SenderAddr;
     int SenderAddrSize = sizeof(SenderAddr);
     int ByteReceived = 5;

   // Initialize Winsock version 2.2

   if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0){

        printf("Server: WSAStartup failed with error: %ld\n", WSAGetLastError());

        return -1;
   }
   else{
        printf("Server: The Winsock DLL status is: %s.\n", wsaData.szSystemStatus);
   }

     // Create a new socket to receive datagrams on.

     ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

     if (ReceivingSocket == INVALID_SOCKET){

          //Print error message
          printf("Server: Error at socket(): %ld\n", WSAGetLastError());

          // Clean up
          WSACleanup();

          // Exit with error
          return -1;
     }
     else{
          printf("Server: socket() is OK!\n");
     }

     /*Set up a SOCKADDR_IN structure that will tell bind that
     we want to receive datagrams from all interfaces using port 5150.*/


     // The IPv4 family
     ReceiverAddr.sin_family = AF_INET;

     // Port no. (8888)
     ReceiverAddr.sin_port = htons(Port);

     // From all interface (0.0.0.0)
     ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);



   // Associate the address information with the socket using bind.

   // At this point you can receive datagrams on your bound socket.

   if (bind(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR){

        // Print error message
        printf("Server: Error! bind() failed!\n");

        // Close the socket
        closesocket(ReceivingSocket);

        // Do the clean up
        WSACleanup();

        // and exit with error
        return -1;
     }
     else{
        printf("Server: bind() is OK!\n");
     }


   // Print some info on the receiver(Server) side...
   getsockname(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));


   printf("Server: Receiving IP(s) used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));

   printf("Server: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));

   printf("Server: I\'m ready to receive data packages. Waiting...\n\n");


   // At this point you can receive datagrams on your bound socket.
   while (1){ // Server is receiving data until you will close it.(You can replace while(1) with a condition to stop receiving.)

        ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);

        if (ByteReceived > 0){ //If there are data
            //Print information for received data
            printf("Server: Total Bytes received: %d\n", ByteReceived);
            printf("Server: The data is: %s\n", ReceiveBuf);
            printf("\n");
        }
        else if (ByteReceived <= 0){ //If the buffer is empty
            //Print error message
            printf("Server: Connection closed with error code: %ld\n", WSAGetLastError());
        }
        else{ //If error
            //Print error message
            printf("Server: recvfrom() failed with error code: %d\n", WSAGetLastError());
        }
   }


   // Print some info on the sender(Client) side...
   getpeername(ReceivingSocket, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
   printf("Server: Sending IP used: %s\n", inet_ntoa(SenderAddr.sin_addr));
   printf("Server: Sending port used: %d\n", htons(SenderAddr.sin_port));


   // When your application is finished receiving datagrams close the socket.
   printf("Server: Finished receiving. Closing the listening socket...\n");
   if (closesocket(ReceivingSocket) != 0){
        printf("Server: closesocket() failed! Error code: %ld\n", WSAGetLastError());
   }
   else{
        printf("Server: closesocket() is OK\n");
   }


   // When your application is finished call WSACleanup.
   printf("Server: Cleaning up...\n");

   if(WSACleanup() != 0){
        printf("Server: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
   }
   else{
        printf("Server: WSACleanup() is OK\n");
   }

   // Back to the system
   return 0;
}
