//
// xpremap.cc
//
// Forgive the messy code (as expected of me).
//
// by: the2000
// deadzone code by: [cOz]
//
#include "SimpleIni.h"
#include "xpremap.h"

extern "C" const TCHAR szModuleName[] = TEXT("xpremap.dll");

typedef struct _STRING
{
  USHORT Length;
  USHORT MaximumLength;
  PCHAR Buffer;
} STRING, * PSTRING;

typedef PVOID PXINPUT_INPUT_DATA;

#ifdef __cplusplus
extern "C"
{
#endif
  HRESULT __stdcall ObCreateSymbolicLink(STRING*, STRING*);
  HRESULT __stdcall ObDeleteSymbolicLink(STRING*);
  UINT32 __stdcall XexGetModuleHandle(char* module, PVOID hand);
  UINT32 __stdcall XexGetProcedureAddress(UINT32 hand ,UINT32, PVOID);
  UINT32 __stdcall XInputdReadState(ULONG_PTR ulDeviceContext, PDWORD pdwPacketNumber, PXINPUT_INPUT_DATA pxiidGamepad);
#ifdef __cplusplus
}
#endif

//
// Gets the address of function based from given ordinal number of a module.
//
UINT32 resolveExport(char* modname, UINT32 ord)
{
  UINT32 ptr32 = 0, ret = 0, ptr2 = 0;
  ret = XexGetModuleHandle(modname, &ptr32);
  if(ret == 0){
    ret = XexGetProcedureAddress(ptr32, ord, &ptr2);
    if(ptr2 != 0)
      return(ptr2);
  }
  return(0);
}

//
// Assigns mount point to a device path
//
HRESULT Mount(CHAR* szDrive, CHAR* szDevice)
{
  CHAR* szSourceDevice;
  CHAR szDestinationDrive[MAX_PATH];
  USHORT len;
  szSourceDevice = szDevice;

  sprintf_s(szDestinationDrive, MAX_PATH, "\\System??\\%s", szDrive);
  len = (USHORT)strlen(szSourceDevice);
  STRING DeviceName =  {len, len + 1, szSourceDevice};

  len = (USHORT)strlen(szDestinationDrive);
  STRING LinkName = {len, len + 1, szDestinationDrive};

  ObDeleteSymbolicLink(&LinkName);

  return((HRESULT)ObCreateSymbolicLink(&LinkName, &DeviceName));
}

//config values for remapping...
__declspec(align(2))
typedef struct _XCONFIG
{
  WORD DUP;
  WORD DDOWN;
  WORD DLEFT;
  WORD DRIGHT;
  WORD START;
  WORD BACK;
  WORD LTHUMB;
  WORD RTHUMB;
  WORD LSHOULDER;
  WORD RSHOULDER;
  WORD A;
  WORD B;
  WORD X;
  WORD Y;
  BYTE LXTHUMB;
  BYTE LYTHUMB;
  BYTE RXTHUMB;
  BYTE RYTHUMB;
  BYTE LTRIGGER;
  BYTE RTRIGGER;
  WORD LLEFTDEAD;
  WORD LRIGHTDEAD;
  WORD LUPDEAD;
  WORD LDOWNDEAD;
  WORD RLEFTDEAD;
  WORD RRIGHTDEAD;
  WORD RUPDEAD;
  WORD RDOWNDEAD;
  BYTE LTRIGGERDEAD;
  BYTE RTRIGGERDEAD;
  BYTE RAPID_DUP;
  BYTE RAPID_DDOWN;
  BYTE RAPID_DLEFT;
  BYTE RAPID_DRIGHT;
  BYTE RAPID_START;
  BYTE RAPID_BACK;
  BYTE RAPID_LTHUMB;
  BYTE RAPID_RTHUMB;
  BYTE RAPID_LSHOULDER;
  BYTE RAPID_RSHOULDER;
  BYTE RAPID_A;
  BYTE RAPID_B;
  BYTE RAPID_X;
  BYTE RAPID_Y;
  BYTE RAPID_LTRIGGER;
  BYTE RAPID_RTRIGGER;
  BYTE INV_LXTHUMB;
  BYTE INV_LYTHUMB;
  BYTE INV_RXTHUMB;
  BYTE INV_RYTHUMB;
} XCONFIG, * PXCONFIG;

//
// Sets default config (maybe unnecessary)
//
void SetDefaultConfig(PXCONFIG pxconfig)
{
  pxconfig->DUP = XINPUT_GAMEPAD_DPAD_UP;
  pxconfig->DDOWN = XINPUT_GAMEPAD_DPAD_DOWN;
  pxconfig->DLEFT = XINPUT_GAMEPAD_DPAD_LEFT;
  pxconfig->DRIGHT = XINPUT_GAMEPAD_DPAD_RIGHT;
  pxconfig->START = XINPUT_GAMEPAD_START;
  pxconfig->BACK = XINPUT_GAMEPAD_BACK;
  pxconfig->LTHUMB = XINPUT_GAMEPAD_LEFT_THUMB;
  pxconfig->RTHUMB = XINPUT_GAMEPAD_RIGHT_THUMB;
  pxconfig->LSHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER;
  pxconfig->RSHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER;
  pxconfig->A = XINPUT_GAMEPAD_A;
  pxconfig->B = XINPUT_GAMEPAD_B;
  pxconfig->X = XINPUT_GAMEPAD_X;
  pxconfig->Y = XINPUT_GAMEPAD_Y;
  pxconfig->LXTHUMB = LXTHUMB_ID;
  pxconfig->LYTHUMB = LYTHUMB_ID;
  pxconfig->RXTHUMB = RXTHUMB_ID;
  pxconfig->RYTHUMB = RYTHUMB_ID;
  pxconfig->LTRIGGER = LTRIGGER_ID;
  pxconfig->RTRIGGER = RTRIGGER_ID;
  pxconfig->LLEFTDEAD = LXDEAD_DEFAULT;
  pxconfig->LRIGHTDEAD = LXDEAD_DEFAULT;
  pxconfig->LUPDEAD = LYDEAD_DEFAULT;
  pxconfig->LDOWNDEAD = LYDEAD_DEFAULT;
  pxconfig->RLEFTDEAD = RXDEAD_DEFAULT;
  pxconfig->RRIGHTDEAD = RXDEAD_DEFAULT;
  pxconfig->RUPDEAD = RYDEAD_DEFAULT;
  pxconfig->RDOWNDEAD = RYDEAD_DEFAULT;
  pxconfig->LTRIGGERDEAD = LTDEAD_DEFAULT;
  pxconfig->RTRIGGERDEAD = RTDEAD_DEFAULT;
  pxconfig->RAPID_DUP = 0;
  pxconfig->RAPID_DDOWN = 0;
  pxconfig->RAPID_DLEFT = 0;
  pxconfig->RAPID_DRIGHT = 0;
  pxconfig->RAPID_START = 0;
  pxconfig->RAPID_BACK = 0;
  pxconfig->RAPID_LTHUMB = 0;
  pxconfig->RAPID_RTHUMB = 0;
  pxconfig->RAPID_LSHOULDER = 0;
  pxconfig->RAPID_RSHOULDER = 0;
  pxconfig->RAPID_A = 0;
  pxconfig->RAPID_B = 0;
  pxconfig->RAPID_X = 0;
  pxconfig->RAPID_Y = 0;
  pxconfig->RAPID_LTRIGGER = 0;
  pxconfig->RAPID_RTRIGGER = 0;
  pxconfig->INV_LXTHUMB = 0;
  pxconfig->INV_LYTHUMB = 0;
  pxconfig->INV_RXTHUMB = 0;
  pxconfig->INV_RYTHUMB = 0;

  return;
}

char* config_sections[] =
{
  P1CONFIG_SECTION,
  P2CONFIG_SECTION,
  P3CONFIG_SECTION,
  P4CONFIG_SECTION
};

char* deadzone_sections[] = 
{
  P1DEADZONE_SECTION,
  P2DEADZONE_SECTION,
  P3DEADZONE_SECTION,
  P4DEADZONE_SECTION
};

char* rapid_sections[] =
{
  P1RAPID_SECTION,
  P2RAPID_SECTION,
  P3RAPID_SECTION,
  P4RAPID_SECTION
};

char* invert_sections[] =
{
  P1INVERT_SECTION,
  P2INVERT_SECTION,
  P3INVERT_SECTION,
  P4INVERT_SECTION
};

XCONFIG g_xconfig[MAX_PLAYERS]; //4 players

//
// Serves as helper function for SimpleIni. Retrieves the
// first 2-byte value in a c-style string.
//
BOOL GetWordFromString(PWORD pword, const char* szString)
{
  if(szString == NULL)
    return(FALSE);
  if(szString[0] == 0x00)
    return(FALSE);

  UINT tempNum = 0;
  int scanresult = sscanf_s(szString, "%d", &tempNum);

  if(scanresult == EOF || scanresult < 1)
    return(FALSE);

  (*pword) = (WORD)tempNum;

  return(TRUE);
}

//
// Serves as helper function for SimpleIni. Retrieves the
// first byte value in a c-style string.
//
BOOL GetByteFromString(PBYTE pbyte, const char* szString)
{
  if(szString == NULL)
    return(FALSE);
  if(szString[0] == 0x00)
    return(FALSE);

  UINT tempNum = 0;
  int scanresult = sscanf_s(szString, "%d", &tempNum);

  if(scanresult == EOF || scanresult < 1)
    return(FALSE);

  (*pbyte) = (BYTE)tempNum;

  return(TRUE);
}

//
// Assigns digital mappings
//
BOOL AssignDigitalConfig(PWORD button, const char* value)
{
  if(value == NULL)
    return(FALSE);
  if(value[0] == 0x00)
    return(FALSE);

  if(CSTRMATCH(value, "DUP"))
    (*button) = XINPUT_GAMEPAD_DPAD_UP;
  else if(CSTRMATCH(value, "DDOWN"))
    (*button) = XINPUT_GAMEPAD_DPAD_DOWN;
  else if(CSTRMATCH(value, "DLEFT"))
    (*button) = XINPUT_GAMEPAD_DPAD_LEFT;
  else if(CSTRMATCH(value, "DRIGHT"))
    (*button) = XINPUT_GAMEPAD_DPAD_RIGHT;
  else if(CSTRMATCH(value, "START"))
    (*button) = XINPUT_GAMEPAD_START;
  else if(CSTRMATCH(value, "BACK"))
    (*button) = XINPUT_GAMEPAD_BACK;
  else if(CSTRMATCH(value, "LTHUMB"))
    (*button) = XINPUT_GAMEPAD_LEFT_THUMB;
  else if(CSTRMATCH(value, "RTHUMB"))
    (*button) = XINPUT_GAMEPAD_RIGHT_THUMB;
  else if(CSTRMATCH(value, "LSHOULDER"))
    (*button) = XINPUT_GAMEPAD_LEFT_SHOULDER;
  else if(CSTRMATCH(value, "RSHOULDER"))
    (*button) = XINPUT_GAMEPAD_RIGHT_SHOULDER;
  else if(CSTRMATCH(value, "A"))
    (*button) = XINPUT_GAMEPAD_A;
  else if(CSTRMATCH(value, "B"))
    (*button) = XINPUT_GAMEPAD_B;
  else if(CSTRMATCH(value, "X"))
    (*button) = XINPUT_GAMEPAD_X;
  else if(CSTRMATCH(value, "Y"))
    (*button) = XINPUT_GAMEPAD_Y;
  else
    return(FALSE);

  return(TRUE);
}

//
// Assigns analong swappings
//
BOOL AssignAnalogConfig(PBYTE button, const char* value)
{
  if(value == NULL)
    return(FALSE);
  if(value[0] == 0x00)
    return(FALSE);

  if(CSTRMATCH(value, "LXTHUMB"))
    (*button) = LXTHUMB_ID;
  else if(CSTRMATCH(value, "LYTHUMB"))
    (*button) = LYTHUMB_ID;
  else if(CSTRMATCH(value, "RXTHUMB"))
    (*button) = RXTHUMB_ID;
  else if(CSTRMATCH(value, "RYTHUMB"))
    (*button) = RYTHUMB_ID;
  else if(CSTRMATCH(value, "LTRIGGER"))
    (*button) = LTRIGGER_ID;
  else if(CSTRMATCH(value, "RTRIGGER"))
    (*button) = RTRIGGER_ID;
  else
    return(FALSE);

  return(TRUE);
}

//
// Assigns inversion config
//
BOOL AssignInvertConfig(PBYTE stick, const char* value)
{
  if(value == NULL)
    return(FALSE);
  if(value[0] == 0x00)
    return(FALSE);

  if(CSTRMATCH(value, "0"))
    (*stick) = 0x00;
  else
    (*stick) = 0x01;

  return(TRUE);
}

BOOL ParseConfigIni(CSimpleIniA& ini, PXCONFIG pxconfig)
{
  //4 times... 4 players
  for(unsigned i = 0; i < MAX_PLAYERS; i++){
    if(!AssignDigitalConfig(&(pxconfig[i].DUP), ini.GetValue(config_sections[i], "DUP")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].DDOWN), ini.GetValue(config_sections[i], "DDOWN")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].DLEFT), ini.GetValue(config_sections[i], "DLEFT")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].DRIGHT), ini.GetValue(config_sections[i], "DRIGHT")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].START), ini.GetValue(config_sections[i], "START")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].BACK), ini.GetValue(config_sections[i], "BACK")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].LTHUMB), ini.GetValue(config_sections[i], "LTHUMB")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].RTHUMB), ini.GetValue(config_sections[i], "RTHUMB")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].LSHOULDER), ini.GetValue(config_sections[i], "LSHOULDER")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].RSHOULDER), ini.GetValue(config_sections[i], "RSHOULDER")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].A), ini.GetValue(config_sections[i], "A")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].B), ini.GetValue(config_sections[i], "B")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].X), ini.GetValue(config_sections[i], "X")))
      return(FALSE);
    if(!AssignDigitalConfig(&(pxconfig[i].Y), ini.GetValue(config_sections[i], "Y")))
      return(FALSE);

    LogMessage("Digital OK!\n");

    if(!AssignAnalogConfig(&(pxconfig[i].LXTHUMB), ini.GetValue(config_sections[i], "LXTHUMB")))
      return(FALSE);
    if(!AssignAnalogConfig(&(pxconfig[i].LYTHUMB), ini.GetValue(config_sections[i], "LYTHUMB")))
      return(FALSE);
    if(!AssignAnalogConfig(&(pxconfig[i].RXTHUMB), ini.GetValue(config_sections[i], "RXTHUMB")))
      return(FALSE);
    if(!AssignAnalogConfig(&(pxconfig[i].RYTHUMB), ini.GetValue(config_sections[i], "RYTHUMB")))
      return(FALSE);
    
    if(!AssignAnalogConfig(&(pxconfig[i].LTRIGGER), ini.GetValue(config_sections[i], "LTRIGGER")))
      return(FALSE);
    if(!AssignAnalogConfig(&(pxconfig[i].RTRIGGER), ini.GetValue(config_sections[i], "RTRIGGER")))
      return(FALSE);

    LogMessage("Analog OK!\n");
   
    if(!GetWordFromString(&(pxconfig[i].LLEFTDEAD), ini.GetValue(deadzone_sections[i], "LTHUMBLEFT")))
      return(FALSE);
    if(!GetWordFromString(&(pxconfig[i].LRIGHTDEAD), ini.GetValue(deadzone_sections[i], "LTHUMBRIGHT")))
      return(FALSE);
    if(!GetWordFromString(&(pxconfig[i].LUPDEAD), ini.GetValue(deadzone_sections[i], "LTHUMBUP")))
      return(FALSE);
    if(!GetWordFromString(&(pxconfig[i].LDOWNDEAD), ini.GetValue(deadzone_sections[i], "LTHUMBDOWN")))
      return(FALSE);

    if(!GetWordFromString(&(pxconfig[i].RLEFTDEAD), ini.GetValue(deadzone_sections[i], "RTHUMBLEFT")))
      return(FALSE);
    if(!GetWordFromString(&(pxconfig[i].RRIGHTDEAD), ini.GetValue(deadzone_sections[i], "RTHUMBRIGHT")))
      return(FALSE);
    if(!GetWordFromString(&(pxconfig[i].RUPDEAD), ini.GetValue(deadzone_sections[i], "RTHUMBUP")))
      return(FALSE);
    if(!GetWordFromString(&(pxconfig[i].RDOWNDEAD), ini.GetValue(deadzone_sections[i], "RTHUMBDOWN")))
      return(FALSE);

    if(!GetByteFromString(&(pxconfig[i].LTRIGGERDEAD), ini.GetValue(deadzone_sections[i], "LTRIGGER")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RTRIGGERDEAD), ini.GetValue(deadzone_sections[i], "RTRIGGER")))
      return(FALSE);

    LogMessage("Deadzone OK!\n");

    if(!GetByteFromString(&(pxconfig[i].RAPID_DUP), ini.GetValue(rapid_sections[i], "DUP")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_DDOWN), ini.GetValue(rapid_sections[i], "DDOWN")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_DLEFT), ini.GetValue(rapid_sections[i], "DLEFT")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_DRIGHT), ini.GetValue(rapid_sections[i], "DRIGHT")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_START), ini.GetValue(rapid_sections[i], "START")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_BACK), ini.GetValue(rapid_sections[i], "BACK")))
      return(FALSE);
 
    if(!GetByteFromString(&(pxconfig[i].RAPID_LTHUMB), ini.GetValue(rapid_sections[i], "LTHUMB")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_RTHUMB), ini.GetValue(rapid_sections[i], "RTHUMB")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_LSHOULDER), ini.GetValue(rapid_sections[i], "LSHOULDER")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_RSHOULDER), ini.GetValue(rapid_sections[i], "RSHOULDER")))
      return(FALSE);
 
    if(!GetByteFromString(&(pxconfig[i].RAPID_A), ini.GetValue(rapid_sections[i], "A")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_B), ini.GetValue(rapid_sections[i], "B")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_X), ini.GetValue(rapid_sections[i], "X")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_Y), ini.GetValue(rapid_sections[i], "Y")))
      return(FALSE);

    if(!GetByteFromString(&(pxconfig[i].RAPID_LTRIGGER), ini.GetValue(rapid_sections[i], "LTRIGGER")))
      return(FALSE);
    if(!GetByteFromString(&(pxconfig[i].RAPID_RTRIGGER), ini.GetValue(rapid_sections[i], "RTRIGGER")))
      return(FALSE);

    LogMessage("Rapidfire OK!\n");

    if(!AssignInvertConfig(&(pxconfig[i].INV_LXTHUMB), ini.GetValue(invert_sections[i], "LXTHUMB")))
      return(FALSE);
    if(!AssignInvertConfig(&(pxconfig[i].INV_LYTHUMB), ini.GetValue(invert_sections[i], "LYTHUMB")))
      return(FALSE);
    if(!AssignInvertConfig(&(pxconfig[i].INV_RXTHUMB), ini.GetValue(invert_sections[i], "RXTHUMB")))
      return(FALSE);
    if(!AssignInvertConfig(&(pxconfig[i].INV_RYTHUMB), ini.GetValue(invert_sections[i], "RYTHUMB")))
      return(FALSE);

    LogMessage("Inverts OK!\n");
  }

  return(TRUE);
}

BOOL LoadConfig(PXCONFIG pxconfig)
{
  CSimpleIniA ini(1, 0, 0);
  if(SUCCEEDED(Mount(MOUNT_POINT, MOUNT_PATH))){

    HANDLE hFile = CreateFile(INI_FILE, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(hFile == INVALID_HANDLE_VALUE)
      return(FALSE);

    XCloseHandle(hFile);

    if(ini.LoadFile(INI_FILE) >= SI_OK)
      return(ParseConfigIni(ini, pxconfig));
  }

  return(FALSE);
}

//
// Gets the port/player number from a given device ctx.
//
UINT32 (*XamUserLookupDevice)(ULONG_PTR ulDeviceContext, DWORD dwDeviceType, PDWORD pdwUserIndex);

UINT32 XInputdReadStateMod(ULONG_PTR ulDeviceContext, PDWORD pdwPacketNumber, PXINPUT_INPUT_DATA pxiidGamepad)
{
  static BYTE ispressed[16];
  static BYTE counter[16];

  UINT32 result = XInputdReadState(ulDeviceContext, pdwPacketNumber, pxiidGamepad);

  DWORD dwPlayerIndex = (DWORD)(-1); //0xFFFFFFFF...

  XamUserLookupDevice = (UINT32 (*)(ULONG_PTR, DWORD, PDWORD))resolveExport(XAM_XEX, XAMUSERLOOKUPDEVICE_ORD);

  if(XamUserLookupDevice != 0){

    XamUserLookupDevice(ulDeviceContext, 0, &dwPlayerIndex);

    if(dwPlayerIndex < MAX_PLAYERS){
      //use dwPlayerIndex for specific configs...
      XINPUT_GAMEPAD* padptr = (XINPUT_GAMEPAD*)pxiidGamepad;
      XINPUT_GAMEPAD oldstate;

      oldstate.bLeftTrigger = padptr->bLeftTrigger;
      oldstate.bRightTrigger = padptr->bRightTrigger;

//======================================
// Inverts
//======================================
      if(g_xconfig[dwPlayerIndex].INV_LXTHUMB == 0)
        oldstate.sThumbLX = padptr->sThumbLX;
      else
        oldstate.sThumbLX = INVERT_ANALOG(padptr->sThumbLX);

      if(g_xconfig[dwPlayerIndex].INV_LYTHUMB == 0)
        oldstate.sThumbLY = padptr->sThumbLY;
      else
        oldstate.sThumbLY = INVERT_ANALOG(padptr->sThumbLY);

      if(g_xconfig[dwPlayerIndex].INV_RXTHUMB == 0)
        oldstate.sThumbRX = padptr->sThumbRX;
      else
        oldstate.sThumbRX = INVERT_ANALOG(padptr->sThumbRX);

      if(g_xconfig[dwPlayerIndex].INV_RYTHUMB == 0)
        oldstate.sThumbRY = padptr->sThumbRY;
      else
        oldstate.sThumbRY = INVERT_ANALOG(padptr->sThumbRY);
//======================================
// End inverts
//======================================
      oldstate.wButtons = padptr->wButtons;

//======================================
// Deadzone must be set first so the response is based on the input and not output
//======================================
      if(padptr->sThumbLX < 0){
        if(padptr->sThumbLX > -(g_xconfig[dwPlayerIndex].LLEFTDEAD))
          padptr->sThumbLX = 0;
      }
      else{
        if(padptr->sThumbLX < (g_xconfig[dwPlayerIndex].LRIGHTDEAD))
          padptr->sThumbLX = 0;
      }

      if(padptr->sThumbLY < 0){
        if(padptr->sThumbLY > -(g_xconfig[dwPlayerIndex].LDOWNDEAD))
          padptr->sThumbLY = 0;
      }
      else{
        if(padptr->sThumbLY < (g_xconfig[dwPlayerIndex].LUPDEAD))
          padptr->sThumbLY = 0;
      }

      if(padptr->sThumbRX < 0){
        if(padptr->sThumbRX > -(g_xconfig[dwPlayerIndex].RLEFTDEAD))
          padptr->sThumbRX = 0;
      }
      else{
        if(padptr->sThumbRX < (g_xconfig[dwPlayerIndex].RRIGHTDEAD))
          padptr->sThumbRX = 0;
      }

      if(padptr->sThumbRY < 0){
        if(padptr->sThumbRY > -(g_xconfig[dwPlayerIndex].RDOWNDEAD))
          padptr->sThumbRY = 0;
      }
      else{
        if(padptr->sThumbRY < (g_xconfig[dwPlayerIndex].RUPDEAD))
          padptr->sThumbRY = 0;
      }

      if(padptr->bLeftTrigger < g_xconfig[dwPlayerIndex].LTRIGGERDEAD)
        padptr->bLeftTrigger = 0;

      if(padptr->bRightTrigger < g_xconfig[dwPlayerIndex].RTRIGGERDEAD)
        padptr->bRightTrigger = 0;

//======================================
//End deadzone section
//======================================

      if(oldstate.wButtons != 0x0000){
        //digital buttons/rapid fire section

        padptr->wButtons = 0x0000;

        if(oldstate.wButtons & XINPUT_GAMEPAD_DPAD_UP){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].DUP;
          if(g_xconfig[dwPlayerIndex].RAPID_DUP != 0){
            counter[DUP_ID]++;

            if((counter[DUP_ID] % g_xconfig[dwPlayerIndex].RAPID_DUP) == 0){
              counter[DUP_ID] = 0;
              ispressed[DUP_ID] = (ispressed[DUP_ID] ? 0 : 1);
            }

            if(!ispressed[DUP_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].DUP;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_DPAD_DOWN){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].DDOWN;
          if(g_xconfig[dwPlayerIndex].RAPID_DDOWN != 0){
            counter[DDOWN_ID]++;

            if((counter[DDOWN_ID] % g_xconfig[dwPlayerIndex].RAPID_DDOWN) == 0){
              counter[DDOWN_ID] = 0;
              ispressed[DDOWN_ID] = (ispressed[DDOWN_ID] ? 0 : 1);
            }

            if(!ispressed[DDOWN_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].DDOWN;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_DPAD_LEFT){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].DLEFT;
          if(g_xconfig[dwPlayerIndex].RAPID_DLEFT != 0){
            counter[DLEFT_ID]++;

            if((counter[DLEFT_ID] % g_xconfig[dwPlayerIndex].RAPID_DLEFT) == 0){
              counter[DLEFT_ID] = 0;
              ispressed[DLEFT_ID] = (ispressed[DLEFT_ID] ? 0 : 1);
            }

            if(!ispressed[DLEFT_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].DLEFT;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].DRIGHT;
          if(g_xconfig[dwPlayerIndex].RAPID_DRIGHT != 0){
            counter[DRIGHT_ID]++;

            if((counter[DRIGHT_ID] % g_xconfig[dwPlayerIndex].RAPID_DRIGHT) == 0){
              counter[DRIGHT_ID] = 0;
              ispressed[DRIGHT_ID] = (ispressed[DRIGHT_ID] ? 0 : 1);
            }

            if(!ispressed[DRIGHT_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].DRIGHT;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_START){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].START;
          if(g_xconfig[dwPlayerIndex].RAPID_START != 0){
            counter[START_ID]++;

            if((counter[START_ID] % g_xconfig[dwPlayerIndex].RAPID_START) == 0){
              counter[START_ID] = 0;
              ispressed[START_ID] = (ispressed[START_ID] ? 0 : 1);
            }

            if(!ispressed[START_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].START;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_BACK){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].BACK;
          if(g_xconfig[dwPlayerIndex].RAPID_BACK != 0){
            counter[BACK_ID]++;

            if((counter[BACK_ID] % g_xconfig[dwPlayerIndex].RAPID_BACK) == 0){
              counter[BACK_ID] = 0;
              ispressed[BACK_ID] = (ispressed[BACK_ID] ? 0 : 1);
            }

            if(!ispressed[BACK_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].BACK;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_LEFT_THUMB){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].LTHUMB;
          if(g_xconfig[dwPlayerIndex].RAPID_LTHUMB != 0){
            counter[LTHUMB_ID]++;

            if((counter[LTHUMB_ID] % g_xconfig[dwPlayerIndex].RAPID_LTHUMB) == 0){
              counter[LTHUMB_ID] = 0;
              ispressed[LTHUMB_ID] = (ispressed[LTHUMB_ID] ? 0 : 1);
            }

            if(!ispressed[LTHUMB_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].LTHUMB;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].RTHUMB;
          if(g_xconfig[dwPlayerIndex].RAPID_RTHUMB != 0){
            counter[RTHUMB_ID]++;

            if((counter[RTHUMB_ID] % g_xconfig[dwPlayerIndex].RAPID_RTHUMB) == 0){
              counter[RTHUMB_ID] = 0;
              ispressed[RTHUMB_ID] = (ispressed[RTHUMB_ID] ? 0 : 1);
            }

            if(!ispressed[RTHUMB_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].RTHUMB;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].LSHOULDER;
          if(g_xconfig[dwPlayerIndex].RAPID_LSHOULDER != 0){
            counter[LSHOULDER_ID]++;

            if((counter[LSHOULDER_ID] % g_xconfig[dwPlayerIndex].RAPID_LSHOULDER) == 0){
              counter[LSHOULDER_ID] = 0;
              ispressed[LSHOULDER_ID] = (ispressed[LSHOULDER_ID] ? 0 : 1);
            }

            if(!ispressed[LSHOULDER_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].LSHOULDER;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].RSHOULDER;
          if(g_xconfig[dwPlayerIndex].RAPID_RSHOULDER != 0){
            counter[RSHOULDER_ID]++;

            if((counter[RSHOULDER_ID] % g_xconfig[dwPlayerIndex].RAPID_RSHOULDER) == 0){
              counter[RSHOULDER_ID] = 0;
              ispressed[RSHOULDER_ID] = (ispressed[RSHOULDER_ID] ? 0 : 1);
            }

            if(!ispressed[RSHOULDER_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].RSHOULDER;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_A){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].A;
          if(g_xconfig[dwPlayerIndex].RAPID_A != 0){
            counter[A_ID]++;

            if((counter[A_ID] % g_xconfig[dwPlayerIndex].RAPID_A) == 0){
              counter[A_ID] = 0;
              ispressed[A_ID] = (ispressed[A_ID] ? 0 : 1);
            }

            if(!ispressed[A_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].A;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_B){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].B;
          if(g_xconfig[dwPlayerIndex].RAPID_B != 0){
            counter[B_ID]++;

            if((counter[B_ID] % g_xconfig[dwPlayerIndex].RAPID_B) == 0){
              counter[B_ID] = 0;
              ispressed[B_ID] = (ispressed[B_ID] ? 0 : 1);
            }

            if(!ispressed[B_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].B;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_X){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].X;
          if(g_xconfig[dwPlayerIndex].RAPID_X != 0){
            counter[X_ID]++;

            if((counter[X_ID] % g_xconfig[dwPlayerIndex].RAPID_X) == 0){
              counter[X_ID] = 0;
              ispressed[X_ID] = (ispressed[X_ID] ? 0 : 1);
            }

            if(!ispressed[X_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].X;
          }
        }

        if(oldstate.wButtons & XINPUT_GAMEPAD_Y){
          padptr->wButtons |= g_xconfig[dwPlayerIndex].Y;
          if(g_xconfig[dwPlayerIndex].RAPID_Y != 0){
            counter[Y_ID]++;

            if((counter[Y_ID] % g_xconfig[dwPlayerIndex].RAPID_Y) == 0){
              counter[Y_ID] = 0;
              ispressed[Y_ID] = (ispressed[Y_ID] ? 0 : 1);
            }

            if(!ispressed[Y_ID])
              padptr->wButtons ^= g_xconfig[dwPlayerIndex].Y;
          }
        }
      }
      
      //this may cause noticeable lag
      padptr->sThumbLX = 0;
      padptr->sThumbLY = 0;
      padptr->sThumbRX = 0;
      padptr->sThumbRY = 0;

      switch(g_xconfig[dwPlayerIndex].LXTHUMB){
        default:
        case LXTHUMB_ID:
          padptr->sThumbLX = oldstate.sThumbLX;
          break;
        case LYTHUMB_ID:
          padptr->sThumbLY = oldstate.sThumbLX;
          break;
        case RXTHUMB_ID:
          padptr->sThumbRX = oldstate.sThumbLX;
          break;
        case RYTHUMB_ID:
          padptr->sThumbRY = oldstate.sThumbLX;
          break;
      }

      switch(g_xconfig[dwPlayerIndex].LYTHUMB){
        case LXTHUMB_ID:
          padptr->sThumbLX = oldstate.sThumbLY;
          break;
        default:
        case LYTHUMB_ID:
          padptr->sThumbLY = oldstate.sThumbLY;
          break;
        case RXTHUMB_ID:
          padptr->sThumbRX = oldstate.sThumbLY;
          break;
        case RYTHUMB_ID:
          padptr->sThumbRY = oldstate.sThumbLY;
          break;
      }

      switch(g_xconfig[dwPlayerIndex].RXTHUMB){
        case LXTHUMB_ID:
          padptr->sThumbLX = oldstate.sThumbRX;
          break;
        case LYTHUMB_ID:
          padptr->sThumbLY = oldstate.sThumbRX;
          break;
        default:
        case RXTHUMB_ID:
          padptr->sThumbRX = oldstate.sThumbRX;
          break;
        case RYTHUMB_ID:
          padptr->sThumbRY = oldstate.sThumbRX;
          break;
      }

      switch(g_xconfig[dwPlayerIndex].RYTHUMB){
        case LXTHUMB_ID:
          padptr->sThumbLX = oldstate.sThumbRY;
          break;
        case LYTHUMB_ID:
          padptr->sThumbLY = oldstate.sThumbRY;
          break;
        case RXTHUMB_ID:
          padptr->sThumbRX = oldstate.sThumbRY;
          break;
        default:
        case RYTHUMB_ID:
          padptr->sThumbRY = oldstate.sThumbRY;
          break;
      }

      //the triggers
      padptr->bLeftTrigger = 0;
      padptr->bRightTrigger = 0;

      switch(g_xconfig[dwPlayerIndex].LTRIGGER){
        default:
        case LTRIGGER_ID:
          padptr->bLeftTrigger = oldstate.bLeftTrigger;
          break;
        case RTRIGGER_ID:
          padptr->bRightTrigger = oldstate.bLeftTrigger;
          break;
      }

      if(g_xconfig[dwPlayerIndex].RAPID_LTRIGGER != 0){
        counter[LTRIGGER_ID]++;

        if((counter[LTRIGGER_ID] % g_xconfig[dwPlayerIndex].RAPID_LTRIGGER) == 0){
          counter[LTRIGGER_ID] = 0;
          ispressed[LTRIGGER_ID] = (ispressed[LTRIGGER_ID] ? FALSE : TRUE);
        }

        if(!ispressed[LTRIGGER_ID]){
          switch(g_xconfig[dwPlayerIndex].LTRIGGER){
            default:
            case LTRIGGER_ID:
              padptr->bLeftTrigger = 0;
              break;
            case RTRIGGER_ID:
              padptr->bRightTrigger = 0;
              break;
          }
        }
      }

      switch(g_xconfig[dwPlayerIndex].RTRIGGER){
        case LTRIGGER_ID:
          padptr->bLeftTrigger = oldstate.bRightTrigger;
          break;
        default:
        case RTRIGGER_ID:
          padptr->bRightTrigger = oldstate.bRightTrigger;
          break;
      }

      if(g_xconfig[dwPlayerIndex].RAPID_RTRIGGER != 0){
        counter[RTRIGGER_ID]++;

        if((counter[RTRIGGER_ID] % g_xconfig[dwPlayerIndex].RAPID_RTRIGGER) == 0){
          counter[RTRIGGER_ID] = 0;
          ispressed[RTRIGGER_ID] = (ispressed[RTRIGGER_ID] ? FALSE : TRUE);
        }

        if(!ispressed[RTRIGGER_ID]){
          switch(g_xconfig[dwPlayerIndex].RTRIGGER){
            case LTRIGGER_ID:
              padptr->bLeftTrigger = 0;
              break;
            default:
            case RTRIGGER_ID:
              padptr->bRightTrigger = 0;
              break;
          }
        }
      }
    }
  }

  return(result);
}

void PatchFunction(UINT32* addr, UINT32 dest)
{
  *addr = 0x3D600000 + ((dest >> 16) & 0xFFFF);
  *(addr + 1) = 0x396B0000 + (dest & 0xFFFF);
  *(addr + 2) = 0x7D6903A6;
  *(addr + 3) = 0x4E800420;

  __dcbst(0, addr);
  __sync();

  return;
}

//
// Removed Dash Launch version check since this is open source anyway.
//
BOOL APIENTRY DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpvReserved)
{
  UNUSED_PARAM(hInstance);
  UNUSED_PARAM(lpvReserved);

  if(dwReason == DLL_PROCESS_ATTACH){
    for(unsigned i = 0; i < MAX_PLAYERS; i++)
      SetDefaultConfig(&g_xconfig[i]);
    
    if(!LoadConfig(g_xconfig))
      return(TRUE);

    PatchFunction((UINT32*)XINPUTDREADSTATE, (UINT32)XInputdReadStateMod);
  }

  return(TRUE);
}
