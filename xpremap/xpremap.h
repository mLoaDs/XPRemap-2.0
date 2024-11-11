//
// All the preprocessor definitions for xpremap.cc goes here.
//
#ifndef __XPREMAP_H__
#define __XPREMAP_H__

#include <xtl.h>

//
// Currently there are two kernel defines: KE_9199, KE_12611 -use the appropriate one.
// You can add it here or on the compile properties of Visual Studio.
//
#define KE_12611

//
// Add your own logging mechanism.
//
#define LogMessage(message)

#define CSTRMATCH(strA, strB) (strcmp(strA, strB) == 0 ? TRUE : FALSE)

//
// These are application specific identifiers for each button.
//
#define DUP_ID 0x00
#define DDOWN_ID 0x01
#define DLEFT_ID 0x02
#define DRIGHT_ID 0x03
#define START_ID 0x04
#define BACK_ID 0x05
#define LTHUMB_ID 0x06
#define RTHUMB_ID 0x07
#define LSHOULDER_ID 0x08
#define RSHOULDER_ID 0x09
#define A_ID 0x0A
#define B_ID 0x0B
#define X_ID 0x0C
#define Y_ID 0x0D

#define LTRIGGER_ID 0x0E
#define RTRIGGER_ID 0x0F

#define LXTHUMB_ID 0x10
#define LYTHUMB_ID 0x11
#define RXTHUMB_ID 0x12
#define RYTHUMB_ID 0x13

//
// Default deadzone values.
//
#define LXDEAD_DEFAULT XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
#define LYDEAD_DEFAULT XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
#define RXDEAD_DEFAULT XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#define RYDEAD_DEFAULT XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#define LTDEAD_DEFAULT XINPUT_GAMEPAD_TRIGGER_THRESHOLD
#define RTDEAD_DEFAULT XINPUT_GAMEPAD_TRIGGER_THRESHOLD

//
// Ini file defines.
//
#define MAX_PLAYERS 4

#define P1CONFIG_SECTION "p1config"
#define P1DEADZONE_SECTION "p1deadzone"
#define P1RAPID_SECTION "p1rapid"
#define P1INVERT_SECTION "p1invert"
#define P2CONFIG_SECTION "p2config"
#define P2DEADZONE_SECTION "p2deadzone"
#define P2RAPID_SECTION "p2rapid"
#define P2INVERT_SECTION "p2invert"
#define P3CONFIG_SECTION "p3config"
#define P3DEADZONE_SECTION "p3deadzone"
#define P3RAPID_SECTION "p3rapid"
#define P3INVERT_SECTION "p3invert"
#define P4CONFIG_SECTION "p4config"
#define P4DEADZONE_SECTION "p4deadzone"
#define P4RAPID_SECTION "p4rapid"
#define P4INVERT_SECTION "p4invert"


#define USB0 "usb0:"
#define USB1 "usb1:"
#define USB2 "usb2:"
#define HDD0 "hdd0:"

#define DEV_USB0 "\\Device\\Mass0"
#define DEV_USB1 "\\Device\\Mass1"
#define DEV_USB2 "\\Device\\Mass2"
#define DEV_HDD0 "\\Device\\Harddisk0\\Partition1"

#define INI_USB0 "usb0:\\plugins\\xpremap\\xpremap.ini"
#define INI_USB1 "usb1:\\plugins\\xpremap\\xpremap.ini"
#define INI_USB2 "usb2:\\plugins\\xpremap\\xpremap.ini"
#define INI_HDD0 "hdd0:\\plugins\\xpremap\\xpremap.ini"

//
// Mount point definitions.
//
#ifdef USE_DEV
  #undef USE_DEV
#endif

//change 0/1/2/3 for other mount points
#define USE_DEV 0

#if USE_DEV == 0
  #define MOUNT_POINT USB0
  #define MOUNT_PATH DEV_USB0
  #define INI_FILE INI_USB0
#elif USE_DEV == 1
  #define MOUNT_POINT USB1
  #define MOUNT_PATH DEV_USB1
  #define INI_FILE INI_USB1
#elif USE_DEV == 2
  #define MOUNT_POINT USB2
  #define MOUNT_PATH DEV_USB2
  #define INI_FILE INI_USB2
#elif USE_DEV == 3
  #define MOUNT_POINT HDD0
  #define MOUNT_PATH DEV_HDD0
  #define INI_FILE INI_HDD0
#endif

//
// There is a very small chance that Microsoft may change the ordinal (or it will break
// older titles), but it is still possible. If the ordinal changes, update it here.
//
#define XAM_XEX "xam.xex"
#define XAMUSERLOOKUPDEVICE_ORD 521

//need to make sure the values don't wrap around (sets max at -32767/+32767)
#define INVERT_ANALOG(X) ((X < 0 ? (X + 1) : X) * -1)

//
// Kernel specific addresses. Options to compile for any kernel version.
//
#if defined(KE_9199)
  #define XINPUTDREADSTATE 0x81BD1A1C
#elif defined(KE_12611)
  #define XINPUTDREADSTATE 0x81BC79B4
#endif

//
// Suppress unused parameter warnings.
//
#define UNUSED_PARAM(param) (void)param

#endif //__XPREMAP_H__
