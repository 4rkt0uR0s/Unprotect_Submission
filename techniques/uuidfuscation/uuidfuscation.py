def generate_uuid_string(shellcode):
    shellcode_size = len(shellcode)
    
    # Ensure shellcode size is a multiple of 4
    if shellcode_size %  16 != 0:
        raise ValueError("Shellcode size must be a multiple of 16.")
    
    uuid_array = []
    number_of_uuid = 0

    # Generate shellcode every 6 bytes
    for i in range(0, shellcode_size, 16):
        uuid0 = f"{int(shellcode[i+3],16):02X}{int(shellcode[i+2],16):02X}{int(shellcode[i+1],16):02X}{int(shellcode[i],16):02X}"
        uuid1 = f"{int(shellcode[i+5],16):02X}{int(shellcode[i+4],16):02X}-{int(shellcode[i+7],16):02X}{int(shellcode[i+6],16):02X}"
        uuid2 = f"{int(shellcode[i+8],16):02X}{int(shellcode[i+9],16):02X}-{int(shellcode[i+10],16):02X}{int(shellcode[i+11],16):02X}"
        uuid3 = f"{int(shellcode[i+12],16):02X}{int(shellcode[i+13],16):02X}{int(shellcode[i+14],16):02X}{int(shellcode[i+15],16):02X}"

        number_of_uuid += 1
        uuid = f"{uuid0}-{uuid1}-{uuid2}{uuid3}"
        if number_of_uuid % (shellcode_size // 4) == 0:
            uuid_array.append(f'"{uuid}"')
        elif number_of_uuid % 8 == 0:
            uuid_array.append(f'\n\t"{uuid}",')
        else:
            uuid_array.append(f'"{uuid}",')

    # Print the result in the same format
    print(f"char * payload[{len(uuid_array)}] = {{ \n\t{''.join(uuid_array)}\n}};\n")

shellcode = ["0x48","0x65","0x6c","0x6c","0x6f","0x20","0x55","0x6e","0x70","0x72","0x6f","0x74","0x65","0x63","0x74","0x50","0x72","0x6f","0x6a","0x65","0x63","0x74","0x2c","0x20","0x74","0x68","0x69","0x73","0x20","0x69","0x73","0x20","0x55","0x55","0x49","0x44","0x20","0x6f","0x62","0x66","0x75","0x73","0x63","0x61","0x74","0x69","0x6f","0x6e"]
generate_uuid_string(shellcode)