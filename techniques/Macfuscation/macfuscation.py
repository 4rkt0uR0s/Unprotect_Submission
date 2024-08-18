def generate_mac_string(shellcode):
    shellcode_size = len(shellcode)
    
    # Ensure shellcode size is a multiple of 4
    if shellcode_size %  6 != 0:
        raise ValueError("Shellcode size must be a multiple of 6.")
    
    mac_array = []
    number_of_mac = 0

    # Generate shellcode every 6 bytes
    for i in range(0, shellcode_size, 6):
        mac = f"{int(shellcode[i],16):02X}:{int(shellcode[i+1],16):02X}:{int(shellcode[i+2],16):02X}:{int(shellcode[i+3],16):02X}:{int(shellcode[i+4],16):02X}:{int(shellcode[i+5],16):02X}"
        number_of_mac += 1

        if number_of_mac % (shellcode_size // 4) == 0:
            mac_array.append(f'"{mac}"')
        elif number_of_mac % 8 == 0:
            mac_array.append(f'\n\t"{mac}",')
        else:
            mac_array.append(f'"{mac}",')

    # Print the result in the same format
    print(f"char * payload[{len(mac_array)}] = {{ \n\t{''.join(mac_array)}\n}};\n")

shellcode = ["0x48","0x65","0x6c","0x6c","0x6f","0x20","0x55","0x6e","0x70","0x72","0x6f","0x74","0x65","0x63","0x74","0x50","0x72","0x6f","0x6a","0x65","0x63","0x74","0x2c","0x20","0x74","0x68","0x69","0x73","0x20","0x69","0x73","0x20","0x4d","0x41","0x43","0x20","0x6f","0x62","0x66","0x75","0x73","0x63","0x61","0x74","0x69","0x6f","0x6e","0x20","0x3a","0x29","0x00","0x00","0x00","0x00"]
generate_mac_string(shellcode)