/*
 * (C) Copyright 2008-2014 Rockchip Electronics
 *
 * Configuation settings for the rk3xxx chip platform.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef RKIMAGE_H
#define RKIMAGE_H

#include <fastboot.h>
#include "config.h"

#define TAG_KERNEL          0x4C4E524B

typedef struct tagKernelImg {
	uint32  tag;
	uint32  size;
	char    image[1];
	uint32  crc;
} KernelImg;


#define BCD2INT(num) (((((num)>>4)&0x0F)*10)+((num)&0x0F))

#define BOOT_RESERVED_SIZE 59

typedef enum {
	RK27_DEVICE = 1,
	RK28_DEVICE = 2,
	RKNANO_DEVICE = 4
} ENUM_RKDEVICE_TYPE;

typedef enum {
	ENTRY471 = 1,
	ENTRY472 = 2,
	ENTRYLOADER = 4
} ENUM_RKBOOTENTRY;

typedef PACKED1 struct
{
	unsigned short usYear;
	unsigned char  ucMonth;
	unsigned char  ucDay;
	unsigned char  ucHour;
	unsigned char  ucMinute;
	unsigned char  ucSecond;
} PACKED2 STRUCT_RKTIME, *PSTRUCT_RKTIME;

typedef struct
{
	unsigned int uiTag;
	unsigned short usSize;
	unsigned int  dwVersion;
	unsigned int  dwMergeVersion;
	STRUCT_RKTIME stReleaseTime;
	ENUM_RKDEVICE_TYPE emSupportChip;
	unsigned char temp[12];
	unsigned char ucLoaderEntryCount;
	unsigned int dwLoaderEntryOffset;
	unsigned char ucLoaderEntrySize;
	unsigned char reserved[BOOT_RESERVED_SIZE];
} PACKED2 STRUCT_RKBOOT_HEAD,*PSTRUCT_RKBOOT_HEAD;

typedef struct
{
	unsigned char ucSize;
	ENUM_RKBOOTENTRY emType;
	unsigned char szName[40];
	unsigned int dwDataOffset;
	unsigned int dwDataSize;
	unsigned int dwDataDelay;//ÒÔÃëÎªµ¥Î»
} PACKED2 STRUCT_RKBOOT_ENTRY,*PSTRUCT_RKBOOT_ENTRY;


#define LOADER_MAGIC_SIZE     16
#define LOADER_HASH_SIZE      32
#define RK_UBOOT_MAGIC        "LOADER  "
#define RK_UBOOT_SIGN_TAG     0x4E474953
#define RK_UBOOT_SIGN_LEN     128
typedef struct tag_second_loader_hdr
{
	uint8_t magic[LOADER_MAGIC_SIZE];  // "LOADER  "

	uint32_t loader_load_addr;           /* physical load addr ,default is 0x60000000*/
	uint32_t loader_load_size;           /* size in bytes */
	uint32_t crc32;                      /* crc32 */
	uint32_t hash_len;                   /* 20 or 32 , 0 is no hash*/
	uint8_t hash[LOADER_HASH_SIZE];     /* sha */

	uint8_t reserved[1024-32-32];
	uint32_t signTag; //0x4E474953
	uint32_t signlen; //128
	uint8_t rsaHash[256];
	uint8_t reserved2[2048-1024-256-8];
} second_loader_hdr;


int loadRkImage(struct fastboot_boot_img_hdr *hdr, const disk_partition_t *boot_ptn, \
		const disk_partition_t *kernel_ptn);
int handleRkFlash(const char *name, const disk_partition_t *ptn,
		struct cmd_fastboot_interface *priv);
int handleDownload(unsigned char *buffer,
		int length, struct cmd_fastboot_interface *priv);
int handleErase(const disk_partition_t *ptn);

#endif /* RKIMAGE_H */