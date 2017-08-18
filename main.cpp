#include "gpio.h"

int main()
{

    GetPinMux();
    SetPinMux("ephy");

	int status;

	status = SetPin(42,PIN_OUT,PIN_LOW);
	if(status < 0)
		printf("%d Error Code:%d",42,status);
	
	status = SetPin(43,PIN_OUT,PIN_LOW);
	if(status < 0)
        printf("%d Error Code:%d",43,status);

    for(int i=0;i<10;i++)
    {
        SetPinValue(42,PIN_LOW);
        SetPinValue(43,PIN_HIGH);
        usleep(500000);    // 500 ms
        SetPinValue(42,PIN_HIGH);
        SetPinValue(43,PIN_LOW);
        usleep(500000);    // 500 ms
        SetPinValue(42,PIN_HIGH);
        SetPinValue(43,PIN_HIGH);
        usleep(500000);    // 500 ms
        SetPinValue(42,PIN_LOW);
        SetPinValue(43,PIN_LOW);
        usleep(500000);    // 500 ms
    }

    DelPin(42);
    DelPin(43);
	return 0;
}
