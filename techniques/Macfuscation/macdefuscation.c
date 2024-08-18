#include <Windows.h>
#include <stdio.h>
#include <ip2string.h>

#pragma comment(lib, "ntdll.lib")

void MACDeobfuscate(CHAR* MACArray[], int MACArrayLength) {
	PCSTR Terminator = NULL;
	PBYTE pointer = NULL, addressToWrite = NULL;
	pointer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, MACArrayLength*6);
	addressToWrite = pointer;
	printf("Allocated on heap at : 0x%p", pointer);
	for (int i = 0; i < MACArrayLength; i++){
		RtlEthernetStringToAddressA(MACArray[i], &Terminator, addressToWrite);
		addressToWrite = (PBYTE)(addressToWrite + 6);
	}
	getchar(); // Pause so you can inspect the heap
}


int main() {
	char * payload[9] = { 
		"48:65:6C:6C:6F:20","55:6E:70:72:6F:74","65:63:74:50:72:6F","6A:65:63:74:2C:20","74:68:69:73:20:69","73:20:4D:41:43:20","6F:62:66:75:73:63",
		"61:74:69:6F:6E:20","3A:29:00:00:00:00",
	};

	MACDeobfuscate(payload, 9);

	return 0;
}