#include "mcp3008Spi.h"

using namespace std;

int main(void){

    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

    int a2dVal[8];
    int a2dChannel = 0;

    unsigned char data[3];

    for (a2dChannel = 0; a2dChannel < 8; a2dChannel++)
    {
        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
	data[2] = 0; // third byte transmitted....don't care

        a2d.spiWriteRead(data, sizeof(data));

        a2dVal[a2dChannel] = 0;
        a2dVal[a2dChannel] = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
        a2dVal[a2dChannel] |=  (data[2] & 0xff);
    }

    cout << "CV: " << a2dVal[0]<< ", " << a2dVal[1] << ", " << a2dVal[2]<< ", " << a2dVal[3] << ", " << a2dVal[4]<< ", " << a2dVal[5] << ", " << a2dVal[6]<< ", " << a2dVal[7] << endl;
    char QSStr[16];
    snprintf(QSStr, sizeof(QSStr), "%d %d %d %d %d %d %d %d", a2dVal[0], a2dVal[1], a2dVal[2], a2dVal[3], a2dVal[4], a2dVal[5], a2dVal[6], a2dVal[7]);
    setenv("DATA", QSStr, 1);
    system("echo \"value $DATA;\" | pdsend 9001 localhost udp");
    return 0;
}


