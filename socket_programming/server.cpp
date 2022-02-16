#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <arpa/inet.h>

struct Data {
    float x, y, z, t;
};


//	Dinamik nesne server.
template<typename T> class Server {		// Bu sınıfı --Server<tip_adi> nesne_adi-- şeklinde örnekleyin. 
    int server_fd, new_socket;
    sockaddr_in address;
    T buffer;
    int opt = 1;
    int addrlen;

public:
    Server(std::string addr, uint16_t port){
        char *p_addr = &addr[0];

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
		
        if(server_fd < 0) printf("1\n");
    
        //if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) printf("2\n");

        address.sin_family = AF_INET;
        inet_aton(p_addr, &(address.sin_addr));
        address.sin_port = port;

        if(bind(server_fd, (sockaddr *) &address, sizeof(address)) < 0) printf("2\n");

        if(listen(server_fd, 3) < 0) printf("3\n");

        addrlen = sizeof(address);
        if((new_socket = accept(server_fd, (sockaddr *) &address, (socklen_t *) &addrlen)) < 0) printf("4\n");       
    }

    void send_val(T data){
        write(new_socket, &data, sizeof(T));
        bzero(&data, sizeof(data));
    }
};

int main(){
    Data buffer;
    
    buffer.x = buffer.y = buffer.z = buffer.t = 0;

    Server<Data> server("127.0.0.1", 6667);

    for(int i = 0; i<100; i++){
        std::cout << "x: " << buffer.x++ << " y: " << buffer.y-- << " z: " << buffer.z++ << " t: " << buffer.t++ <<  std::endl;
        server.send_val(buffer);       
        sleep(1);
    }

    return 0;
}
