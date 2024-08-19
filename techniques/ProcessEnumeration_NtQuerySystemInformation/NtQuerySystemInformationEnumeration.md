# Detecting Running Process: NtQuerySystemInformation

## Authorship information
* Name or nickname (required): *4rkt0uR0s*
* Email: *4rkt0uR0s@proton.me*

## Technique Information
* Technique title (required): Process Enumeration -  NtQuerySystemInformation
* Technique category (required): Anti-Monitoring 
* Technique description (required): `NtSystemProcessInformation` is a Windows API function that can be used to enumerate processes and gather detailed information about them. This function is accessed via the NtQuerySystemInformation API call, which provides various system-related information depending on the `SystemInformationClass` parameter passed to it. When `SystemProcessInformation` is used as the `SystemInformationClass`, the API call returns an array of structures, each describing a process running on the system.

## Additional resources
* https://tbhaxor.com/windows-process-listing-using-ntquerysysteminformation/
* http://www.rohitab.com/discuss/topic/40626-list-processes-using-ntquerysysteminformation/