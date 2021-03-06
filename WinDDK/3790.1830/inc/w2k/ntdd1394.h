/*++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    ntdd1394.h

Abstract:

    Definitions for the 1394 api

Author:

    George Chrysanthakopoulos (georgioc) 4/26/99

Environment:

    Kernel mode only

Revision History:


--*/

#ifndef _NTDD1394_H_
#define _NTDD1394_H_

#if (_MSC_VER >= 1020)
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Various definitions
//

#define IOCTL_IEEE1394_API_REQUEST                  CTL_CODE( \
                                                FILE_DEVICE_UNKNOWN, \
                                                0x100, \
                                                METHOD_BUFFERED, \
                                                FILE_ANY_ACCESS \
                                                )

//
// IEEE 1394 Sbp2 Request packet.  It is how other
// device drivers communicate with the 1sbp2 trasnport.
//

typedef struct _IEEE1394_VDEV_PNP_REQUEST{

    ULONG fulFlags;
    ULONG Reserved;
    ULARGE_INTEGER InstanceId;
    UCHAR DeviceId;

} IEEE1394_VDEV_PNP_REQUEST,*PIEEE1394_VDEV_PNP_REQUEST;


typedef struct _IEEE1394_API_REQUEST {

    //
    // Holds the zero based Function number that corresponds to the request
    // that device drivers are asking the sbp2 port driver to carry out.
    //

    ULONG RequestNumber;

    //
    // Holds Flags that may be unique to this particular operation
    //

    ULONG Flags;

    //
    // Holds the structures used in performing the various 1394 APIs
    //

    union {

        IEEE1394_VDEV_PNP_REQUEST AddVirtualDevice;
        IEEE1394_VDEV_PNP_REQUEST RemoveVirtualDevice;

        struct {

            ULONG fulFlags;
            ULONG fulDesiredAccess;
            ULARGE_INTEGER DeviceEUI;

        } DeviceAccessTransfer;

    } u;

} IEEE1394_API_REQUEST, *PIEEE1394_API_REQUEST;

//
// Request Number
//

#define IEEE1394_API_ADD_VIRTUAL_DEVICE             0x00000001
#define IEEE1394_API_REMOVE_VIRTUAL_DEVICE          0x00000002
#define IEEE1394_API_DEVICE_ACCESS_TRANSFER         0x00000003
#define IEEE1394_API_SET_LOCAL_NODE_PROPERTIES      0x00000004

//
// flags for the add/remove requests
//

#define IEEE1394_REQUEST_FLAG_UNICODE       0x00000001

//
// definitions for the access/ownership 1394 scheme
//

//
// GUID used to register for PnP notifications on access status changes
//
         
static const GUID IEEE1394_API_NOTIFICATION_EVENT = 
{ 0xA8E0BA12, 0x4ACF, 0x4278, { 0x87, 0x78, 0xED, 0x7F, 0x28, 0xF2, 0x73, 0xAA } };


typedef struct _IEEE1394_NOTIFICATION_DATA {

    ULONG Version;
    ULONG BusGeneration;
    ULONG Type;
    ULONG Flags;

    union {

        struct {

            ULONG fulFlags;
            ULONG AccessFlags;
            ULARGE_INTEGER RemoteNodeEUI;

        } AccessChange;

        struct {

            ULONG BusResetFlags;

        } BusReset;

    } u;

} IEEE1394_NOTIFICATION_DATA, *PIEEE1394_NOTIFICATION_DATA;

//
// Type definitions
//

#define IEEE1394API_NOTIFICATION_DEVICE_ACCESS    0x00000001
#define IEEE1394API_NOTIFICATION_BUS_RESET        0x00000002

//
// AccessChange.AccessFlags field
//

#define IEEE1394API_DEVICE_OWNERSHIP_LOCAL_NODE         0x00000001
#define IEEE1394API_RESOURCE_OWNERSHIP_LOCAL_NODE       0x00000002

#define IEEE1394API_DEVICE_OWNERSHIP_REMOTE_NODE        0x00000004
#define IEEE1394API_RESOURCE_OWNERSHIP_REMOTE_NODE      0x00000008

#define IEEE1394API_ACCESS_SHARED_READ                  0x00000010
#define IEEE1394API_ACCESS_SHARED_WRITE                 0x00000020
#define IEEE1394API_ACCESS_EXCLUSIVE                    0x00000040

//
// AccessChange.fulFlags field
//

#define IEEE1394API_REMOTE_ACCESS_TRANSFER_REQUEST      0x00000001

//
// BusReset.BusResetFlags
//

#define IEEE1394API_BUS_RESET_LOCAL_NODE_IS_ROOT       0x00000001
#define IEEE1394API_BUS_RESET_LOCAL_NODE_IS_IRM        0x00000002
#define IEEE1394API_BUS_RESET_LOCAL_NODE_INITIATED     0x00000004


#ifdef __cplusplus
}
#endif

#endif      // _NTDD1394_H_

