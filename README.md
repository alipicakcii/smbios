# SMBIOS



## Usage

```cpp
SMBIOS smbios;
Eps *eps = smbios.get_eps();
printf("SMBIOS anochor string %s\n", eps->anchor_string);
printf("SMBIOS version %d.%d\n", eps->major, eps->minor);

SmBiosStructure * current_struct;
current_struct = smbios.next_structure();
auto *bios_info = static_cast<BiosInformation*>(current_struct);
printf("type %d\n", bios_info->header.type);
.
.
.
smbios.print_string();


current_struct = smbios.next_structure();
auto *system_info = static_cast<SystemInformation*>(current_struct);
printf("type %d\n", system_info->header.type);
.
smbios.print_string();




