// Copyright YummyCarrot(huyuzhe)

// My Github Location:
// https://github.com/CRThu

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
