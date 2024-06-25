/* 
 * Copyright (c) 2024 Ali PİÇAKCI. All rights reserved.
*/
#ifndef FIRMWRAE_SM_BIOS
#define FIRMWRAE_SM_BIOS

// bunu g++ derleyicisi kendisi sağlar
// bu başlık dosyası için endişe etmenize gerek yok
#include <stdint.h>



#define START_ADDR 				0x000F0000
#define END_ADDR 				0x000FFFFF

template<typename T>
void _printf(const char *format, T args...)
{
	// buraya kendi printf nizi implemente edin
}
void printf(const char *str)
{
	_printf("%s", str);
}
namespace firmware
{

	// bütün tablolar varsa sıralama
	// bu şekilde gitmekedir ardışık ola
	enum SmBiosType  : char
	{
		BIOS_Information      =0,    
		System_Information    =1,  
		System_Enclosure      =3,
		Processor_Information =4, 
		Cache_Information     =7,
		

		inactive	      =126,
		End_of_Table          =127
	};

	struct Eps
	{
		uint8_t anchor_string[4];
		uint8_t checksum;
		uint8_t length;
		uint8_t major;
		uint8_t minor;
		uint16_t max_size;
		uint8_t revision;
		uint8_t format_area[5];
		uint8_t intermediate_anchor_string[5];
		uint8_t intermediate_checksum;
		uint16_t structure_table_length;
		uint32_t structure_table_address;
		uint16_t number;
		uint8_t bcd_revision;


	}__attribute__((packed));


	
	struct SMBIOSHeader {
		
		uint8_t type;
		uint8_t len;
		uint16_t handle;

	}__attribute__((packed));


	struct SmBiosStructure
	{
		SMBIOSHeader header;

	}__attribute__((packed));

	struct BiosInformation 
		: public SmBiosStructure
	{
		uint8_t  vendor;
		uint8_t  version;
		uint16_t starting_addr;
		uint8_t  release_date;
		uint8_t  rom_size;
		uint64_t characteristics;
		uint8_t  characteristics_ex;

	}__attribute__((packed));


	struct SystemInformation
		:public SmBiosStructure
	{
		uint8_t manufacturer;
		uint8_t product_name;
		uint8_t version;
		uint8_t serial_number;
		uint8_t uuid[16];
		uint8_t wake_up_type;
		uint8_t sku_number;
		uint8_t family;



	}__attribute__((packed));

	struct SystemEnclosure
		: public SmBiosStructure
	{
		uint8_t manufacturer;
		uint8_t type;
		uint8_t version;
		uint8_t serial_number;
		uint8_t asset_tag_number;
		uint8_t boot_up_state;
		uint8_t power_supply_state;
		uint8_t thermal_state;
		uint8_t security_status;
		uint16_t oem_defined;
		uint8_t height;
		uint8_t number_of_power_cords;
		uint8_t contained_element_count;
		uint8_t contained_element_record_len;


	}__attribute__((packed));


	struct ProcInformation
		: public SmBiosStructure
	{
		uint8_t socket_designation;
		uint8_t type;
		uint8_t family;
		uint8_t manufacturer;
		uint64_t id;
		uint8_t version;
		uint8_t voltage;
		uint16_t external_clock;
		uint16_t max_speed;
		uint16_t current_speed;
		uint8_t status;
		uint8_t upgrade;
		uint16_t l1_cahce_handle;
		uint16_t l2_cahce_handle;
		uint16_t l3_cahce_handle;
		uint8_t serial_number;
		uint8_t asset_tag;
		uint8_t part_number;

	}__attribute__((packed));

	struct CacheInformation
		:public  SmBiosStructure
	{
		
		uint8_t socket_dsesignation;
		uint16_t cache_configuration;
		uint16_t maximum_cache_size;
		uint16_t installed_size;
		uint16_t supported_sram_type;
		uint16_t current_sram_type;
		uint8_t  cahce_speed;
		uint8_t error_correction_type;
		uint8_t system_cache_type;
		uint8_t associativity;



	}__attribute__((packed));

	class SMBIOS
	{
		private:
			Eps*  _eps;
			Eps*  find_eps();
			char* _str_start;
			char* _str_end;
			int   _type_next_number;
		public:
			SMBIOS(); 
			Eps *get_eps();
			size_t smbios_struct_len(SMBIOSHeader *hd);
			void print_string();
			SmBiosStructure * next_structure();
			char * string_start();
			char * string_end();
			
		
	};
}


#endif
