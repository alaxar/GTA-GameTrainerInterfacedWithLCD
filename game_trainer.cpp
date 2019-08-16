#include <Windows.h>
#include <iostream>
using namespace std;

/*
	Name: GTA Trainer
	Copyright: 
	Author: Alazar Demessie
	Date: 15/08/19 16:37
	Description: Created for educational purpose only!!
	
 	"gta_sa.exe"+0079BAA4 + D0
  	gta_sa.exe --> default ImageBase --> 0x400000 + 0079baa4 + Pointer + d0 = ????????

*/

// funcation prototype
int lcd_screen(int);

// variable declarations and definitions

// function definition
int main() {
	int value;
	cout<<endl;
	cout<<"\t\t[*] GTA: San Andreas Memory Manipulator			"<<endl<<endl;
	cout<<"\t\t[*] Written By Alazar Demessie					"<<endl;
	cout<<"\t\t[*] Created For fun 						"<<endl;
	cout<<"\t\t[*] Increase your Sniper Ammo 					"<<endl;
	cout<<"													"<<endl;
	cout<<"\t\tEnter the amount: ";
	cin>>value;
	HWND window = FindWindow(0, "GTA: San Andreas");
	if(window) {
		cout<<"[*] Found Windows"<<endl<<endl;
	} else {
		cout<<"[-] Couldnt found windows"<<endl<<endl;
	}
	DWORD _proc_id;
	GetWindowThreadProcessId(window, &_proc_id);
	HANDLE handler = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _proc_id);
	if(handler) {
		cout<<endl<<"[*] Process Opened..."<<endl<<endl;
	} else {
		cout<<"[-] Couldnt Open Process"<<endl<<endl;
	}
	// Reading process memory (I + B + P + O)
	int i;
	unsigned long imageBase = 0x400000;  // the program's default ImageBaseAddress
	unsigned long base_address = 0x0079BAA4;	// this is the Snipers Base Address
	unsigned long int offset = 0xD0;			// this one is the first offset
	unsigned long int Pointer; // this holds the final value
	unsigned long int temp;		// this holds the temp(ImageBase + baseAddress) value
	DWORD valueSize = sizeof(value);

	if(ReadProcessMemory(handler, LPVOID(imageBase + base_address),&temp, sizeof(temp),0 )) {
		int ptr;
		Pointer =  temp + offset;
		WriteProcessMemory(handler, (LPVOID)(Pointer), &value, valueSize, NULL);
		while(ptr > 0) {
			ReadProcessMemory(handler, LPVOID(Pointer), &ptr, sizeof(ptr), 0);
			cout<<"[*] The value of the Sniper is : "<<ptr<< " @ address of "<<(void *)ptr<<endl<<endl;
			lcd_screen(ptr);	
		}
	} else {
		cout<<"[-] Error while reading process memory"<<endl<<endl;
		system("pause");
	}
	if(WriteProcessMemory(handler, (LPVOID)(Pointer), &value, valueSize, NULL)) {
		cout<<"[*] Writing to memory at "<<(void *)Pointer<<endl;	
		getchar();
	} else {
		cout<<"[-] Failed Writing to memory offset at "<<(void *)base_address<<endl;
		system("pause");
	}
	CloseHandle(handler);
	return 0;
	main();
}

// function definition
int lcd_screen(int data) {
	HANDLE SerialCommuncation;		// Creating a handle for SeriaCommuncation
	DWORD bytesWritten = 0;	
	SerialCommuncation = CreateFile("COM7", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);	
	//	Do the basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);	
	GetCommState(SerialCommuncation, &serialParams);
	serialParams.BaudRate = 9600;		// Serial BuadRate
	serialParams.ByteSize = 8;			// Serial ByteSize
	serialParams.StopBits = 1;			// Serial StopBits
	serialParams.Parity = 0;			// Parity by default 0
	SetCommState(SerialCommuncation, &serialParams);

	//writing and reading from serial code goes here
	// converting INTEGER into CHARACTER
	int writeValue = data;
	char temp[100];
	itoa(writeValue, temp, 10);			// converting an integer value to a character
	char readFrom[] = {};				// Holder of the Serial incoming data	
	if(WriteFile(SerialCommuncation, &temp, sizeof(temp), 0, 0)) {
			cout<<"Writing to a port...."<<endl;
	} else {
		cout<<"There is an error.."<<GetLastError();
	}
	if(ReadFile(SerialCommuncation, &readFrom, sizeof(readFrom), 0, 0)) {
		cout<<"COM 7 -> "<<readFrom<<endl;
	} else {
		cout<<GetLastError();
	}
	CloseHandle(SerialCommuncation);
}
