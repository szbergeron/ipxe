#ifndef _IPXE_EFI_UTILS_H
#define _IPXE_EFI_UTILS_H

/** @file
 *
 * EFI utilities
 */

FILE_LICENCE ( GPL2_OR_LATER );

#include <ipxe/efi/efi.h>
#include <ipxe/efi/Protocol/DevicePath.h>

extern EFI_DEVICE_PATH_PROTOCOL *
efi_devpath_end ( EFI_DEVICE_PATH_PROTOCOL *path );
extern int efi_child_add ( EFI_HANDLE parent, EFI_HANDLE child );
extern void efi_child_del ( EFI_HANDLE parent, EFI_HANDLE child );

#endif /* _IPXE_EFI_UTILS_H */
