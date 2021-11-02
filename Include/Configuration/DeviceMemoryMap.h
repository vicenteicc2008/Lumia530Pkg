#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 64

/* Below flag is used for system memory */
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES \
                EFI_RESOURCE_ATTRIBUTE_PRESENT |                 \
                EFI_RESOURCE_ATTRIBUTE_INITIALIZED |             \
                EFI_RESOURCE_ATTRIBUTE_TESTED |                  \
                EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |             \
                EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |       \
                EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |    \
                EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum {
    NoHob,
    AddMem,
    AddDev,
    MaxMem
} DeviceMemoryAddHob;

typedef struct {
	EFI_PHYSICAL_ADDRESS				Address;
	UINT64						Length;
	EFI_RESOURCE_TYPE				ResourceType;
	EFI_RESOURCE_ATTRIBUTE_TYPE			ResourceAttribute;
	ARM_MEMORY_REGION_ATTRIBUTES			ArmAttributes;
	DeviceMemoryAddHob				HobOption;
	EFI_MEMORY_TYPE					MemoryType;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = 
{
	/* Address,	  Length,     ResourceType, Resource Attribute,                                  ARM MMU Attribute,                  HobOption, EFI Memory Type */
	/*New HLOS*/
	{ 0x00000000, 0x0F700000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },	
	/*Tz Apps*/
	{ 0x0F700000, 0x00300000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddMem, EfiReservedMemoryType },
	/*!!!SMEM*/
	{ 0x0FA00000, 0x00200000, EFI_RESOURCE_MEMORY_RESERVED, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED, AddMem, EfiMaxMemoryType },
	/*NonRelocatable 0*/
	{ 0x0FC00000, 0x00300000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddMem, EfiReservedMemoryType },
    /*FrameBuffer*/
	{ 0x0FF00000, 0x00800000, EFI_RESOURCE_MEMORY_RESERVED, EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH, AddMem, EfiMaxMemoryType },
	/* HLOS Memory 5 */
	{ 0x10700000, 0x0C500000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },
    /*Firmware location*/
	{ 0x1CC00000, 0x00100000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiBootServicesCode},
    /*UEFI MEM POOL*/
    { 0x1CD00000, 0x03300000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },
	/* Other memory regions */
	/*IMEM Boot Base*/
	{ 0xFE800000, 0x00040000, EFI_RESOURCE_SYSTEM_MEMORY, EFI_RESOURCE_ATTRIBUTE_INITIALIZED, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, NoHob, EfiConventionalMemory },
	/*IMEM Cookie Base*/
	{ 0xFC42B000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_INITIALIZED, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiConventionalMemory },
	/*IMEM Cookie Base 2*/	
	{ 0xFE805000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_INITIALIZED, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiConventionalMemory },
	/*RPM CODE_DATARAM Dump*/
	//{ 0xFC100000, 0x00100000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_INITIALIZED, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiConventionalMemory },
	/* Register regions */
	/*1*/
	{ 0xF9000000, 0x02000000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*2*/
	{ 0xFC400000, 0x00002000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*3*/
	{ 0xFC428000, 0x00008000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*4*/
	{ 0xFC4AB000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*5*/
	{ 0xFC4C0000, 0x00040000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*6*/
	{ 0xFD400000, 0x00D00000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*7*/
	{ 0xFC4B8000, 0x00008000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*8*/
	{ 0xFC4A9000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/* Terminator for MMU*/
	{0},
	/* Terminator for LibMem */
	{ 0xFFFFFFFF, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO }
};

#endif

