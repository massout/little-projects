#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

struct Data{
    float x, y, z, t;
};


//	Dinamik nesne client.
template<typename T> class Client {		// Bu sınıfı --Client<tip_adi> nesne_adi-- şeklinde örnekleyin.
    int sock = 0;
    sockaddr_in serv_addr;
    T buffer;

public:
    Client(std::string addr, uint16_t port){
        char *p_addr = &addr[0];

        if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) printf("1\n");

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = port;
        if(inet_pton(AF_INET, p_addr, &serv_addr.sin_addr) <= 0) printf("2\n");

        if(connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) printf("3\n");
    }

    T read_val(){
        T temp;
        recv(sock, &temp, sizeof(T), 0);
        return temp;
    }

	~Client(){
		close(sock);
	}
};


int main(){
    Client<Data> client("127.0.0.1", 6667);

    Data temp;

    for(int i=0; i<100; i++){
        temp = client.read_val();

        std::cout << "x: " << temp.x << " y: " << temp.y << " z: " << temp.z << " t: " << temp.t << std::endl;
        sleep(1);
    }

    return 0;
}
