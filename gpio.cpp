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

// Set GPIO Pin Mux
void SetPinMux(char* group)
{
	char GBuf[128]={"mt7688_pinmux set "};
	strcat(GBuf,group);
	strcat(GBuf," gpio");
	system(GBuf);
}
// Init Export/UnExport
int SetPinInit(int PinNum, char* type)
{
	// File Open
	char PExport[128]={"/sys/class/gpio/"};
	int fd = open(strcat(PExport,type) , O_WRONLY);	// open export/unexport file
	if (fd == FILE_OPEN_ERROR)
		return PIN_INIT_FILE_OPEN_ERROR;
	
	// File Write
	char WBuf[128];
	sprintf(WBuf, "%d", PinNum);
	if (write(fd, WBuf, sizeof(WBuf)) == FILE_WRITE_ERROR)	// write PinNum to file
		return PIN_INIT_FILE_WRITE_ERROR;

	// File Close
	if (close(fd) == FILE_CLOSE_ERROR)
		return PIN_INIT_FILE_CLOSE_ERROR;
	
	return PIN_INIT_SUCCESS;
}
// Export
int SetPinExport(int PinNum)
{
	return SetPinInit(PinNum,"export");
}
// Unexport
int SetPinUnExport(int PinNum)
{
	return SetPinInit(PinNum,"unexport");
}
// Set Direction
int SetPinDir(int PinNum, Pin_Direction Direction)
{
	// File Open
    char PBuf[128];
	sprintf(PBuf, "/sys/class/gpio/gpio%d/direction", PinNum);	// Open Direction file
	int fd = open(PBuf, O_WRONLY);
	if (fd == FILE_OPEN_ERROR)
		return SET_DIR_FILE_OPEN_ERROR;
	
	// File Write
	static const char DirStr[] = "in\0out";
	if(write(fd, &DirStr[Direction == PIN_IN ? 0 : 3], Direction == PIN_IN ? 2 : 3) == FILE_WRITE_ERROR)	// Write "in"/"out"
		return SET_DIR_FILE_WRITE_ERROR;
	
	// File Close
	if (close(fd) == FILE_CLOSE_ERROR)
		return SET_DIR_FILE_CLOSE_ERROR;
	
	return SET_DIR_SUCCESS;
}
// Set Value
int SetPinValue(int PinNum, Pin_Value Value)
{ 
	// File Open
    char PBuf[128];
	sprintf(PBuf, "/sys/class/gpio/gpio%d/value", PinNum);	// Open Value file
	int fd = open(PBuf, O_WRONLY);
	if (fd == FILE_OPEN_ERROR)
		return SET_VALUE_FILE_OPEN_ERROR;

	// File Write
	if (write(fd, ((Value == PIN_LOW)?"0":"1"), 1) == FILE_WRITE_ERROR)	//Write 0/1
		return SET_VALUE_FILE_WRITE_ERROR;
	
	// File Close
	if (close(fd) == FILE_CLOSE_ERROR)
		return SET_VALUE_FILE_CLOSE_ERROR;
	
	return SET_VALUE_SUCCESS;
}
// Export + Direction + Value
int SetPin(int PinNum, Pin_Direction Direction, Pin_Value Value)
{
	int status;

	status = SetPinExport(PinNum);
	if (status < 0)
		return status;

	status = SetPinDir(PinNum, Direction);
	if (status < 0)
		return status;
	
	status = SetPinValue(PinNum, Value);
	if (status < 0)
		return status;
	
	return SET_PIN_SUCCESS;
}
// Delete Pin
int DelPin(int PinNum)
{
	return SetPinUnExport(PinNum);
}

// Get Pin Mux
void GetPinMux()
{
	system("mt7688_pinmux get");
}
// Get Direction
Pin_Direction GetPinDir(int PinNum)
{

	// File Open
    char PBuf[128];
	sprintf(PBuf, "/sys/class/gpio/gpio%d/direction", PinNum);	// Open Direction file
	int fd = open(PBuf, O_RDONLY);
	if (fd == FILE_OPEN_ERROR)
		return GET_DIR_FILE_OPEN_ERROR;
	
	// File Read
	char DirStr[16];
	int status = read(fd, DirStr, 16);
	if (status == FILE_READ_ERROR)
		return GET_DIR_FILE_READ_ERROR;
	if (status == FILE_READ_EOF)
		return GET_DIR_FILE_READ_EOF;

	// File Close
	if (close(fd) == FILE_CLOSE_ERROR)
		return GET_DIR_FILE_CLOSE_ERROR;

    return (atoi(DirStr)==PIN_IN?PIN_IN:PIN_OUT);
}
// Get value
Pin_Value GetPinValue(int PinNum)
{
	// File Open
    char PBuf[128];
	sprintf(PBuf, "/sys/class/gpio/gpio%d/value", PinNum);	// Open Value file
	int fd = open(PBuf, O_RDONLY);
	if (fd == FILE_OPEN_ERROR)
		return GET_VALUE_FILE_OPEN_ERROR;
	
	// File Read
	char ValStr[16];
	int status = read(fd, ValStr, 16);
	if (status == FILE_READ_ERROR)
		return GET_VALUE_FILE_READ_ERROR;
	if (status == FILE_READ_EOF)
		return GET_VALUE_FILE_READ_EOF;

	// File Close
	if (close(fd) == FILE_CLOSE_ERROR)
		return GET_VALUE_FILE_CLOSE_ERROR;

    return (atoi(ValStr)==PIN_HIGH?PIN_HIGH:PIN_LOW);
}
