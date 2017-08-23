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
#ifndef _GPIO_H_
#define _GPIO_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// SetPinInit
#define PIN_INIT_FILE_OPEN_ERROR -1
#define PIN_INIT_FILE_WRITE_ERROR -2
#define PIN_INIT_FILE_CLOSE_ERROR -3
#define PIN_INIT_SUCCESS 0
// SetPinDir
#define SET_DIR_FILE_OPEN_ERROR -1
#define SET_DIR_FILE_WRITE_ERROR -2
#define SET_DIR_FILE_CLOSE_ERROR -3
#define SET_DIR_SUCCESS 0
// SetPinValue
#define SET_VALUE_FILE_OPEN_ERROR -1
#define SET_VALUE_FILE_WRITE_ERROR -2
#define SET_VALUE_FILE_CLOSE_ERROR -3
#define SET_VALUE_SUCCESS 0
// SetPin
#define SET_PIN_SUCCESS 0
// File Operation
#define FILE_OPEN_ERROR -1
#define FILE_READ_EOF 0
#define FILE_READ_ERROR -1
#define FILE_WRITE_ERROR -1
#define FILE_CLOSE_ERROR -1

enum Pin_Value {
	GET_VALUE_FILE_OPEN_ERROR = -1,
	GET_VALUE_FILE_READ_ERROR = -2,
	GET_VALUE_FILE_READ_EOF = -3,
	GET_VALUE_FILE_CLOSE_ERROR = -4,
	PIN_LOW = 0,
	PIN_HIGH = 1
};

enum Pin_Direction {
	GET_DIR_FILE_OPEN_ERROR = -1,
	GET_DIR_FILE_READ_ERROR = -2,
	GET_DIR_FILE_READ_EOF = -3,
	GET_DIR_FILE_CLOSE_ERROR = -4,
	PIN_IN = 0,
	PIN_OUT = 1
};

// Set*
void SetPinMux(char* group);	// mt7688_pinmux set $ephy$ gpio
int SetPinInit(int PinNum,char* type);	// Init Export/UnExport
int SetPinExport(int PinNum);	// echo $PinNum$ > /sys/class/gpio/export
int SetPinUnExport(int PinNum);	// echo $PinNum$ > /sys/class/gpio/unexport
int SetPinDir(int PinNum, Pin_Direction Direction);	// echo $in/out$ > /sys/class/gpio/gpio$PinNum$/direction
int SetPinValue(int PinNum, Pin_Value Value);	// echo $0/1$ > /sys/class/gpio/gpio$PinNum$/value
int SetPin(int PinNum, Pin_Direction Direction, Pin_Value Value);	// Export + SetPinDir + SetPinValue
int DelPin(int PinNum);	// unexport
// Get*
void GetPinMux();	// mt7688_pinmux get
Pin_Direction GetPinDir(int PinNum);	// cat /sys/class/gpio/gpio$PinNum$/direction
Pin_Value GetPinValue(int PinNum);	// cat /sys/class/gpio/gpio$PinNum$/value

#endif // !_GPIO_H_
