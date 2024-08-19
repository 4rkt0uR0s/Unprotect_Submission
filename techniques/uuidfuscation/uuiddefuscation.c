#include <Windows.h>
#include <stdio.h>
#include <rpcdce.h>

#pragma comment(lib, "Rpcrt4.lib")

void uuidDeobfuscate(CHAR* uuidArray[], int uuidArrayLength) {
	PCSTR Terminator = NULL;
	PBYTE pointer = NULL, addressToWrite = NULL;
	pointer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, uuidArrayLength*16);
	addressToWrite = pointer;
	printf("Allocated on heap at : 0x%p", pointer);
	for (int i = 0; i < uuidArrayLength; i++){
		UuidFromStringA((RPC_CSTR)uuidArray[i], (UUID *)addressToWrite);
		addressToWrite = (PBYTE)(addressToWrite + 16);
	}
	getchar(); // Pause so you can inspect the heap
}


int main() {
	char * payload[3] = { 
		"6C6C6548-206F-6E55-7072-6F7465637450","656A6F72-7463-202C-7468-697320697320","44495555-6F20-6662-7573-636174696F6E",
	};

	uuidDeobfuscate(payload, 3);

	return 0;
}