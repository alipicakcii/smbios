/*
 * Copyright (c) 2024 Ali PİÇAKCI. All rights reserved.
 */
#include <smbios.hh>


namespace firmware
{
	

	size_t SMBIOS::smbios_struct_len(SMBIOSHeader *hd)
	{
		size_t i;
		const char *strtab = (char *)hd + hd->len;
		for (i = 1; strtab[i - 1] != '\0' || strtab[i] != '\0'; i++)
			;
		return hd->len + i + 1;
	}

	SMBIOS::SMBIOS()
	{

		this->_eps = this->find_eps();
		this->_str_start = nullptr;
		this->_str_end   = nullptr;
		this->_type_next_number =  0;
		
	}

	void SMBIOS::print_string()
	{
		if (this->_str_start == nullptr ||this->_str_end == nullptr  )return;


		while((uint32_t) this->_str_start < (uint32_t) this->_str_end)
		{
			
			if (this->_str_start[0] == '\0' && this->_str_start[1] == '\0') break;

			while(*this->_str_start == '\0')
			{
				printf(" ");
				this->_str_start++;

			}
	
			char c = *this->_str_start++;
			_printf("%c", c);
		}
	}

	SmBiosStructure * SMBIOS::next_structure()
	{
		if (this->_eps == nullptr) return nullptr;

		SmBiosStructure  * type = reinterpret_cast<SmBiosStructure *>(this->_eps->structure_table_address);


		char *buf;
		char  buf_len;
		for (int i  = 0; i < this->_type_next_number; i++)
		{
			buf_len = this->smbios_struct_len(& type->header);
			buf     = ((char*) type + buf_len);
			type    =  reinterpret_cast<SmBiosStructure*>(buf);
		}


		char * str_start = (char*)type + type->header.len;
		char * str_end   = (char*) str_start + 64; 
		this->_str_start = str_start;
		this->_str_end   = str_end;
		this->_type_next_number++;
		if (
				type->header.type >= 127 
				|| 
				type->header.len <=0
		   )
		{
			return nullptr;
		}
		return type;
	}

	char * SMBIOS::string_start()
	{
		return this->_str_start;

	}
	char * SMBIOS::string_end()
	{
		return this->_str_end;
	}
	
	Eps * SMBIOS::find_eps()
	{
		char *_start = (char*)START_ADDR;
		char *_end = (char*)END_ADDR;
		bool checksum = false;
		while((uint32_t)_start < (uint32_t)_end)
		{
			if (
					_start[0] == '_' &&
					_start[1] == 'S' &&
					_start[2] == 'M' &&
					_start[3] == '_' 

			   )
			{
				checksum = true;
				break;
			}
			_start++;
		}
		if (!checksum)return nullptr;
		return reinterpret_cast<Eps*>(_start);
	}
	Eps * SMBIOS::get_eps()
	{
		
		return this->_eps;
	}

	
	
}
