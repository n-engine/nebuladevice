/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#ifndef _FWCELLINPUT_H_
#define _FWCELLINPUT_H_

// from usb to our keyboard mapping
static unsigned char sKeyboardMap[256] =
{
	0,							//SCE_USBKEYC_NO_EVENT
	0,							//SCE_USBKEYC_E_ROLLOVER
	0,							//SCE_USBKEYC_E_POSTFAIL
	0,							//SCE_USBKEYC_E_UNDEF
	FWInput::Channel_Key_A,					//SCE_USBKEYC_A	
	FWInput::Channel_Key_B,					//SCE_USBKEYC_B	
	FWInput::Channel_Key_C,					//SCE_USBKEYC_C	
	FWInput::Channel_Key_D,					//SCE_USBKEYC_D	
	FWInput::Channel_Key_E,					//SCE_USBKEYC_E	
	FWInput::Channel_Key_F,					//SCE_USBKEYC_F	
	FWInput::Channel_Key_G,					//SCE_USBKEYC_G	
	FWInput::Channel_Key_H,					//SCE_USBKEYC_H	
	FWInput::Channel_Key_I,					//SCE_USBKEYC_I	
	FWInput::Channel_Key_J,					//SCE_USBKEYC_J	
	FWInput::Channel_Key_K,					//SCE_USBKEYC_K	
	FWInput::Channel_Key_L,					//SCE_USBKEYC_L	
	FWInput::Channel_Key_M,					//SCE_USBKEYC_M	
	FWInput::Channel_Key_N,					//SCE_USBKEYC_N	
	FWInput::Channel_Key_O,					//SCE_USBKEYC_O	
	FWInput::Channel_Key_P,					//SCE_USBKEYC_P	
	FWInput::Channel_Key_Q,					//SCE_USBKEYC_Q	
	FWInput::Channel_Key_R,					//SCE_USBKEYC_R	
	FWInput::Channel_Key_S,					//SCE_USBKEYC_S	
	FWInput::Channel_Key_T,					//SCE_USBKEYC_T	
	FWInput::Channel_Key_U,					//SCE_USBKEYC_U	
	FWInput::Channel_Key_V,					//SCE_USBKEYC_V	
	FWInput::Channel_Key_W,					//SCE_USBKEYC_W	
	FWInput::Channel_Key_X,					//SCE_USBKEYC_X	
	FWInput::Channel_Key_Y,					//SCE_USBKEYC_Y	
	FWInput::Channel_Key_Z,					//SCE_USBKEYC_Z	
	FWInput::Channel_Key_1,					//SCE_USBKEYC_1	
	FWInput::Channel_Key_2,					//SCE_USBKEYC_2	
	FWInput::Channel_Key_3,					//SCE_USBKEYC_3	
	FWInput::Channel_Key_4,					//SCE_USBKEYC_4	
	FWInput::Channel_Key_5,					//SCE_USBKEYC_5	
	FWInput::Channel_Key_6,					//SCE_USBKEYC_6	
	FWInput::Channel_Key_7,					//SCE_USBKEYC_7	
	FWInput::Channel_Key_8,					//SCE_USBKEYC_8	
	FWInput::Channel_Key_9,					//SCE_USBKEYC_9	
	FWInput::Channel_Key_0,					//SCE_USBKEYC_0	
	FWInput::Channel_Key_Enter,				//SCE_USBKEYC_ENTER
	FWInput::Channel_Key_Escape,				//SCE_USBKEYC_ESC	
	FWInput::Channel_Key_Backspace,				//SCE_USBKEYC_BS	
	FWInput::Channel_Key_Tab,				//SCE_USBKEYC_TAB	
	FWInput::Channel_Key_Space,				//SCE_USBKEYC_SPACE
	FWInput::Channel_Key_Minus,				//SCE_USBKEYC_MINUS
	FWInput::Channel_Key_Equals,				//SCE_USBKEYC_EQUAL_101
	FWInput::Channel_Key_LeftBracket,			//SCE_USBKEYC_LEFT_BRACKET_101
	FWInput::Channel_Key_RightBracket,			//SCE_USBKEYC_RIGHT_BRACKET_101
	FWInput::Channel_Key_Backslash,				//SCE_USBKEYC_BACKSLASH_101
	0,							//SCE_USBKEYC_RIGHT_BRACKET_106
	FWInput::Channel_Key_Semicolon,				//SCE_USBKEYC_SEMICOLON
	FWInput::Channel_Key_Apostrophe,			//SCE_USBKEYC_QUOTATION_101
	0,							//SCE_USBKEYC_106_KANJI
	FWInput::Channel_Key_Comma,				//SCE_USBKEYC_COMMA
	FWInput::Channel_Key_Period,				//SCE_USBKEYC_PERIOD
	FWInput::Channel_Key_Slash,				//SCE_USBKEYC_SLASH
	0,							//SCE_USBKEYC_CAPS_LOCK
	FWInput::Channel_Key_F1,				//SCE_USBKEYC_F1
	FWInput::Channel_Key_F2,				//SCE_USBKEYC_F2
	FWInput::Channel_Key_F3,				//SCE_USBKEYC_F3
	FWInput::Channel_Key_F4,				//SCE_USBKEYC_F4
	FWInput::Channel_Key_F5,				//SCE_USBKEYC_F5
	FWInput::Channel_Key_F6,				//SCE_USBKEYC_F6
	FWInput::Channel_Key_F7,				//SCE_USBKEYC_F7
	FWInput::Channel_Key_F8,				//SCE_USBKEYC_F8
	FWInput::Channel_Key_F9,				//SCE_USBKEYC_F9
	FWInput::Channel_Key_F10,				//SCE_USBKEYC_F10
	FWInput::Channel_Key_F11,				//SCE_USBKEYC_F11
	FWInput::Channel_Key_F12,				//SCE_USBKEYC_F12
	0,							//SCE_USBKEYC_PRINTSCREEN
	0,							//SCE_USBKEYC_SCROLL_LOCK
	0,							//SCE_USBKEYC_PAUSE
	FWInput::Channel_Key_Insert,				//SCE_USBKEYC_INSERT
	FWInput::Channel_Key_Home,				//SCE_USBKEYC_HOME
	FWInput::Channel_Key_PageUp,				//SCE_USBKEYC_PAGE_UP
	FWInput::Channel_Key_Delete,				//SCE_USBKEYC_DELETE
	FWInput::Channel_Key_End,				//SCE_USBKEYC_END
	FWInput::Channel_Key_PageDown,				//SCE_USBKEYC_PAGE_DOWN
	FWInput::Channel_Key_Right,				//SCE_USBKEYC_RIGHT_ARROW
	FWInput::Channel_Key_Left,				//SCE_USBKEYC_LEFT_ARROW
	FWInput::Channel_Key_Down,				//SCE_USBKEYC_DOWN_ARROW
	FWInput::Channel_Key_Up,				//SCE_USBKEYC_UP_ARROW
	0,							//SCE_USBKEYC_NUM_LOCK
	FWInput::Channel_Key_Numpad_Slash,			//SCE_USBKEYC_KPAD_SLASH
	FWInput::Channel_Key_Numpad_Asterisk,			//SCE_USBKEYC_KPAD_ASTERISK
	FWInput::Channel_Key_Numpad_Minus,			//SCE_USBKEYC_KPAD_MINUS
	FWInput::Channel_Key_Numpad_Plus,			//SCE_USBKEYC_KPAD_PLUS
	FWInput::Channel_Key_Numpad_Enter,			//SCE_USBKEYC_KPAD_ENTER
	FWInput::Channel_Key_Numpad_1,				//SCE_USBKEYC_KPAD_1
	FWInput::Channel_Key_Numpad_2,				//SCE_USBKEYC_KPAD_2
	FWInput::Channel_Key_Numpad_3,				//SCE_USBKEYC_KPAD_3
	FWInput::Channel_Key_Numpad_4,				//SCE_USBKEYC_KPAD_4
	FWInput::Channel_Key_Numpad_5,				//SCE_USBKEYC_KPAD_5
	FWInput::Channel_Key_Numpad_6,				//SCE_USBKEYC_KPAD_6
	FWInput::Channel_Key_Numpad_7,				//SCE_USBKEYC_KPAD_7
	FWInput::Channel_Key_Numpad_8,				//SCE_USBKEYC_KPAD_8
	FWInput::Channel_Key_Numpad_9,				//SCE_USBKEYC_KPAD_9
	FWInput::Channel_Key_Numpad_0,				//SCE_USBKEYC_KPAD_0
	FWInput::Channel_Key_Numpad_Period,			//SCE_USBKEYC_KPAD_PERIOD
	0,							//
	0,							//SCE_USBKEYC_APPLICATION
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
	0,							//
};

// Cell pad info wrapper
class FWCellPadInfo
{
public:
	inline FWCellPadInfo(int device) :
	mDevice(device),
	mPadId(-1)
	{
	}

private:
	int		mDevice;
	int		mPadId;

	friend class	FWInputDevicePad;
};

#define FWINPUT_MAX_PAD_IDS	6

static int sPadIds[FWINPUT_MAX_PAD_IDS][3] =
{
	{-1,	-1,	-1},	// libusbpad supported device
	{0x6666,	0x667,	-1},	// PS Controller Adaptor
	{0x7b5,  0x312,	4},	// Logic3 Rumble Pad
	{0xc12,	0x5,	4},	// Game USB Adaptor
	{0xb43,	0x1,	-1},	// Smart Joy USB Adaptor
	{0x925,	0x1802,	-1},	// Elecom USB Adaptor
};

static int sPadMappings[FWINPUT_MAX_PAD_IDS][40] =
{
	// libusbpad supported pad mapping
	{6, 7, 4, 5, 3, 7, 3, 6, 3, 5, 3, 4, 3, 2, 3, 3, 3, 0, 3, 1, 2, 0, 2, 3, 2, 1, 2, 2, 2, 4, 2, 5, 2, 6, 2, 7, 20, 21, 22, 23},
	// PS Controller Adaptor
	{2, 3, 4, 5, 0, 3, 0, 2, 0, 1, 0, 0, 0, 6, 0, 7, 0, 4, 0, 5, 1, 0, 1, 3, 1, 1, 1, 2, 1, 4, 1, 5, 1, 6, 1, 7, -1, -1, -1, -1},
	// Logic3 Rumble Pad
	{0, 1, 3, 2, 4, 4, 4, 6, 4, 7, 4, 5, 5, 0, 5, 2, 5, 1, 5, 3, 5, 4, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	// Game USB Adaptor
	{0, 1, 3, 2, 4, 7, 4, 6, 4, 5, 4, 4, 5, 2, 5, 3, 5, 0, 5, 1, 5, 4, 5, 7, 5, 5, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	// Smart Joy USB Adaptor
	{2, 3, 4, 5, 0, 3, 0, 2, 0, 1, 0, 0, 0, 6, 0, 7, 0, 4, 0, 5, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, -1, -1, -1, -1},
	// Elecom USB Adaptor
	{3, 4, 5, 6, 1, 3, 1, 2, 1, 1, 1, 0, 1, 6, 1, 7, 1, 4, 1, 5, 2, 1, 2, 0, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, -1, -1, -1, -1},
};

#define FW_MAX_KEYBD_NUM	4
#define FW_MAX_PAD_NUM		4
#define FW_MAX_MOUSE_NUM	4

#endif//_FWCELLINPUT_H_

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
