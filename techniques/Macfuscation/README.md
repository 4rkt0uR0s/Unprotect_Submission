# *MACFuscation*

## Authorship information
* Name or nickname (required): *4rkt0uR0s*
* Email: *4rkt0uR0s@proton.me*
  
## Technique Information
* Technique title (required): IPV4/IPV6 Obfuscation
* Technique category (required): Data Obfuscation
* Technique description (required):  The obfuscated payload masquerades itself as an array of ASCII MAC addresses. Each one of these MACs is passed to the `RtlEthernetStringToAddressA` function, which will translate the ASCII MAC string to binary. The binary representation of all of these MACs is combined to form a blob of shellcode.

## Code snippets
To generate an obfuscated payload from a shellcode, you must first run the python script which will return the obfuscated payload as a list of IPs
```bash
$ python3 macfuscation.py
char * payload[9] = { 
	"48:65:6C:6C:6F:20","55:6E:70:72:6F:74","65:63:74:50:72:6F","6A:65:63:74:2C:20","74:68:69:73:20:69","73:20:49:50:76:34","20:6F:62:66:75:73",
	"63:61:74:69:6F:6E","20:3A:29:00:00:00",
};
```

Then, you can deobfuscate it at runtime in the heap, as in `macdefuscation.c`

```c
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
```