//----------------------------------------------------------------------
//	Copyright � 1990-2005 by Starry Night Software, Inc., All rights reserved.
//
//	File:		StarryNightPlugins.h
//
//	Contains:	public interface to Starry Night's plug-in architecture.
//					
//	Authors:	Ted Leckie, Tom Andersen
//				With help from Roy Lovejoy
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	05/10/07	MK			5.7.0		Added ASCOM Focuser related calls
//	02/10/02	DWW			4.5.0		Updated for version 4 Plugin SDK
//	02/10/02	DWW			4.0.0		Updated comments and constants for sn_SetPluginStatusText
//	02/03/05	DWW			4.0.0		Mods for Pro X
//	99/08/20	ETL			3.0.0		Mods for Starry Night Pro 3.0
//	96/04/01	ETL			2.0.0		New
//
//----------------------------------------------------------------------

// General Notes for Version 5.x releases:
//----------------------------
// This release of Starry Night plugin SDK contains a number of enhancements that support focuser
// control, additional telescope functionality and available FOV information.
//
// General Notes for the Version 4.0 release:
//----------------------------
// The major difference between this release and previous releases of the Starry Night plugin SDK is
// the addition of the sn_SetPluginStatusText API call. Because we at SN Software now support Macintosh
// telescope control ourselves (that is, we created the telescope control plugin shipped with SN) and 
// always supported the ASCOM telescope control, we decided to make Telescope control a permanent fixture
// in the SN Pro interface. With the addition of the new "Telescope" tab, plugin developers can now communicate
// plugin starus information directly to the user without having to create their own dialogs.
//
// Note that after SN detects a telescope plugin in the "Plug-ins" folder (your plugin tells SN that it is a
// telescope -also use for digital setting circles- plugin in its op_Initialize routine by setting
// outInitRecord->fIsTelescopeController = true) it sets the Status string to "Configure Plugin". After that,
// it is the responsibility of the plugin to keep these strings accurate.



//
// Win32 Notes:
//----------------------------
//
// Note on building for MS VC++ From a plugin writer: With comments from Tom - Nov '99
// 
// - To support COM in the plugin, use the appwizard to create an MFC
// AppWizard DLL- not a plain old Win32 SDK style DLL.  Be sure to enable
// automation when setting up the wizard.  If this is done, the full range
// of OLE brain-damage is available for use by the .dll.
//
// To make a plugin, these are the files you should need:
// StarryNightPlugins.h,
// starrynight.exe.lib (which is a file that you include that will allow the plugin to link to all the available calls in starry night)
// a .cpp file such as controller.cpp
// You want to make a .dll, then change the extension to .plug, and put it in the Starry Night Plugins folder
// All the other files included in the plugin kit, such as the controller data folder, all the .xSYM files, and all other
// .lib files are not needed, but are included as they are either samples or files for mac plug-in developement.
//
// - I found the MS C++ compiler
// doesn't like the "pragma mark" entries in the sdk header file- it
// doesn't implement a pragma called mark.  Presumably ifdefs can deal with
// it, but I didn't try, instead just deleted them.
//
// - The #define TARGET_OS_WIN32 must be set by hand.  Either getting that
// setting from the compiler defines or documenting the requirement would
// be helpful (assuming I didn't miss it somewhere).
// --You will have to define it by hand, but see the code in Controller.cpp
//    put the defines in before you include StarryNightPlugins.h. I guess I
//    could put them in StarryNightPlugins.h, but it would be a big messy
//	  block of ifdefs. --Tom
// note that TARGET_OS_MAC must also be defined to 0 if you are using MS VC++ for x86 --Tom
//
// - Getting the debugger to work required the following;
// 	Copy the .dll into the plugins folder, changing the extension to
// ..plugin from .dll
// 	From the project settings, debug tab, additional DLLs option, put the
// full pathname to the .plugin file created by the previous step.  If this
// isn't done, debugger breakpoints won't stop the program.  I'm not really
// sure why this works.  Comforting, no?

//
// Mac Notes:
//-----------------------------------
//
// - The #define TARGET_OS_MAC must be set by hand.  Either getting that
// setting from the compiler defines or documenting the requirement would
// be helpful (assuming I didn't miss it somewhere).
// --You will have to define it by hand, but see the code in Controller.cpp
//    put the defines in before you include StarryNightPlugins.h. I guess I
//    could put them in StarryNightPlugins.h, but it would be a big messy
//	  block of ifdefs. --Tom
// note that TARGET_OS_WIN32 must also be defined to 0 if you are using MS VC++ for x86 --Tom
//
// -- New notes by Dave Whipps 02/10/02: Note that plugin should be compiled for Mach-0 and put into
// a standard bundle package (Checkout www.apple.com to see how this is done if your development
// environment doesn't support creating one automatically.) 
// Also note that there is no longer a mac stub library. You should now link directly to the Starry Night
// application for exported API function definitions. This can be done using the -bundle_loader "path to SN"
// linker flag in Project Builder.

#pragma once

//#include <limits.h>

#if TARGET_OS_MAC
#elif TARGET_OS_WIN32
#else
	you must have both TARGET_OS_MAC and TARGET_OS_WIN32 defined with one of them defined 1 the other 0
	// see comments above
#endif



#if TARGET_OS_MAC
	typedef void* HDC; // on the Mac we need to define an HDC as something
#endif

#ifndef qBuildingPlugin
	#define qBuildingPlugin 1
#endif


//----------------------------------------------------------------------
// data types
// we use platform neutral data types 
//----------------------------------------------------------------------

// Window ref. Starry Night uses window refs to refer to specific document windows in Starry Night.
// A document window is a regular night sky viewing window. 
typedef unsigned long sn_WindowRef;
const sn_WindowRef kFrontWindow = 0;

class TScene;
class TSelection;

#if TARGET_OS_MAC
typedef Boolean 		pBoolean;
typedef Rect 			pRect;
typedef Str255 			pStr255;
typedef GWorldPtr 		pGWorldPtr;
typedef Point 			pPoint;
typedef EventRecord* 	pEventRecordPtr;
typedef MenuHandle 		pMenuHandle;
typedef DragReference 	pDragReference;
typedef ItemReference 	pItemReference;
typedef PicHandle		pHandleToPicture;

#elif TARGET_OS_WIN32
typedef unsigned char 	pBoolean;	// the boolean or BOOL data type,
typedef signed long 	SInt32; // need to define this for windows since we use it below.
typedef long double		double_tsn;

struct pRect
{
	short 	top;
	short 	left;
	short 	bottom;
	short 	right;
};
typedef struct pRect pRect;

// pascal string
typedef unsigned char	pStr255[256];

// GWorldPtr
typedef void* pGWorldPtr;

struct pPoint 
{
	short	v;
	short 	h;
};

typedef struct pPoint pPoint;

struct pEventRecord
{
	short	 			what;
	unsigned long 		message;
	unsigned long 		when;
	pPoint 				where;
	short		 		modifiers;
};
typedef struct pEventRecord pEventRecord;

typedef pEventRecord* pEventRecordPtr;	// on Macintosh, a pointer to an EventRecord, on Win32 same thing
typedef HMENU pMenuHandle;				// on Macintosh, a menu handle, on windows an HMENU
typedef IDataObject* pDragReference;	// on Macintosh a DragReference, windows an OLE IDataObject
typedef unsigned long pItemReference; 	// on Macintosh an ItemReference
typedef HBITMAP		pHandleToPicture; 	// a devive dependent bitmap that you can get from the screen environment

struct pUpdateRegion 
{
	unsigned short 		rgnSize;		/*size in bytes*/ // you can almost always ignore this
	pRect 				rgnBBox;		/*enclosing rectangle*/
};


#endif //Windows stuff

const long 		kPluginDrawTimeNeedMoreData = 1;

const short		kUndefinedMagnitudeValue	= -9999;		// flags an unknown magnitude

//----------------------------------------------------------------------
//	Version
//
//	Purpose:	these constants are passed by Starry Night in PInitialize::fPluginAPI to inform
//				the plugin the latest version of the plugin API the currently running Starry Night
//				supports. The plugin should return the id of the API it uses. If the plugin
//				requires a later API than Starry Night supports, it should put up a warning.
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		Updated plug-in API for version 4.x
//
//----------------------------------------------------------------------

const long kVersion1Plugin = 1;
const long kVersion2Plugin = 2;
const long kVersion3Plugin = 3;		// 2.1.2 supports new Telescope controller extensions
const long kVersion4Plugin = 4;		// version 3 adds callbacks
const long kVersion5Plugin = 5;		// more call back functions, notably OpenURL
const long kVersion6Plugin = 6;		// Added a new field to PInitialize
const long kVersion7Plugin = 7;		// Added a new fields to PGaze
const long kVersion8Plugin = 8;		// Added sn_SetPluginStatusText and related struct
const long kVersion9Plugin = 9;		// Updated for SN 4
const long kVersion10Plugin = 10;	// Updated for SN 5 (NB initial release of 5.0.0 used kVersion9Plugin)
const long kLatestVersion = kVersion10Plugin;

//----------------------------------------------------------------------
//	Menu Commands
//
//	Purpose:	Note that these MUST correspond to the defined values
//				in GracileResources.h
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//  2005/Aug/24	MK			5.7			Added Focuser commands	
//	03/10/15	DWW			4.5.1		Re-Added since ted removed the command definitions from here...need to support old plugins.		
//
//----------------------------------------------------------------------

// these are actually MessageT 
const SInt32	cmd_TelescopeConfigure		= 8200;
const SInt32	cmd_TelescopeTime			= 8201;
const SInt32	cmd_TelescopeLocation		= 8202;
const SInt32	cmd_TelescopeOpen			= 8203;
const SInt32	cmd_TelescopeClose			= 8204;
const SInt32	cmd_TelescopeTrack			= 8205;
const SInt32	cmd_TelescopeSlew			= 8206;
const SInt32	cmd_TelescopeSync			= 8207;
const SInt32	cmd_TelescopeDirectionalSlew = 8208;		// New for version 5.0
const SInt32	cmd_TelescopePark			= 8209;		// New for version 5.0
const SInt32	cmd_TelescopeUnpark			= 8210;		// New for version 5.0
const SInt32	cmd_TelescopeGoHome			= 8211;		// New for version 5.0
const SInt32	cmd_TelescopeSetParkPosition	= 8212;		// New for version 5.0
const SInt32	cmd_SnapShotSettings			= 8213;		// New for version 5.0
const SInt32	cmd_TakeSnapShot				= 8214;		// New for version 5.0
const SInt32	cmd_ImportImageToStarryNight	= 8215;		// New for version 5.0
const SInt32	cmd_FocuserConfigure			= 8216;		// New for version 5.7
const SInt32	cmd_FocuserOpen					= 8217;		// New for version 5.7
const SInt32	cmd_FocuserClose				= 8218;		// New for version 5.7
const SInt32	cmd_FocuserTempCompensation		= 8219;		// New for version 5.7
const SInt32	cmd_FocuserMove					= 8220;		// New for version 5.7
const SInt32	cmd_FocuserGoto					= 8221;		// New for version 5.7
const SInt32	cmd_FocuserStop					= 8222; 	// New for version 5.7

//----------------------------------------------------------------------
//	ObjectType
//
//	Purpose:	these are the object types used universally throughout SN
//				to describe any item
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		Updated plug-in API for version 4.x
//
//----------------------------------------------------------------------

enum ObjectType {
	Kind_Unknown						= 'xxxx',
	Kind_AnyType						= 'xxxx',

	Kind_StarGrouping					= 'Cxxx',
	Kind_Asterisim						= 'CAxx',
	Kind_Constellation					= 'CCxx',
	Kind_SmallStarGrouping				= 'CSxx',

	Kind_SolarSystemObject				= 'sxxx',
	Kind_Sun							= 'sSxx',
	Kind_Planet							= 'sPxx',
	Kind_Comet							= 'sCxx',
	Kind_Asteroid						= 'sAxx',
	Kind_MoonOfPlanet					= 'sMxx',
	Kind_MeteorShower					= 'ssxx',
	Kind_Planetoid						= 'sOxx',

	Kind_Star							= 'Sxxx',
	Kind_MultipleStar					= 'SMxx',
	Kind_DoubleStar						= 'S2xx',
	Kind_TripleStar						= 'S3xx',
	Kind_VariableStar					= 'SxxV',
	Kind_VariableAndMultiple			= 'SMxV',
	Kind_StarWtihExtrasolarPlanet		= 'SxEV',

	Kind_Galaxy							= 'Gxxx',
	Kind_GalaxyCluster					= 'GCxx',
	Kind_EllipticalGalaxy				= 'GExx',
	Kind_EllipticalEMinusGalaxy			= 'GEe-',
	Kind_EllipticalE0Galaxy				= 'GEex',
	Kind_EllipticalEPlusGalaxy			= 'GEe+',
	Kind_EllipticalS0MinusGalaxy		= 'GES-',
	Kind_LenticularS0Galaxy				= 'GLSx',
	Kind_LenticularS0PlusGalaxy			= 'GLS+',
	Kind_TransitionS0					= 'GTSx',
	Kind_SpiralGalaxy					= 'GSxx',
	Kind_SpiralSaGalaxy					= 'GSSa',
	Kind_SpiralSabGalaxy				= 'GSSA',
	Kind_SpiralSbGalaxy					= 'GSSb',
	Kind_SpiralSbcGalaxy				= 'GSSB',
	Kind_SpiralScGalaxy					= 'GSSc',
	Kind_SpiralScdGalaxy				= 'GSSC',
	Kind_SpiralSdGalaxy					= 'GSSd',
	Kind_IregularGalaxy					= 'GIxx',
	Kind_IregularSpiralSdmGalaxy		= 'GISd',
	Kind_IregularSpiralSmGalaxy			= 'GISm',
	Kind_IregularImGalaxy				= 'GImx',
	Kind_IregularI0Galaxy				= 'GI0x',

	Kind_Nebula							= 'Nxxx',
	Kind_DiffuseNebula					= 'NDxx',
	Kind_DarkNebula						= 'Ndxx',
	Kind_PlanetaryNebula				= 'NPxx',
	Kind_ReflectionNebula				= 'NRxx',

	Kind_ClusterOfStars					= 'Kxxx',
	Kind_GlobularCluster				= 'KGxx',
	Kind_OpenCluster					= 'KOxx',
	Kind_ClusterWithNebulosity			= 'KNxx',

	Kind_Other							= 'Oxxx',
	Kind_Globules						= 'OGxx',
	Kind_H2Region						= 'OHxx',
	Kind_Quasar							= 'OQxx',
	Kind_RadioSource					= 'ORxx',
	Kind_SupernovaRemnant				= 'ONxx',
	Kind_BlackHole						= 'OBxx',

	Kind_Nonexistant					= 'Xxxx',

	Kind_ManmadeObject					= 'Mxxx',
	Kind_Satellite						= 'MSxx',
	Kind_GeosyncSatellite				= 'MSGx',
	Kind_AstroObsSatellite				= 'MSAx',
	Kind_Probe							= 'MPxx',
	Kind_MannedSpacecraft				= 'MMxx',

	Kind_SpotSelection					= 'Zxxx',

	kLastObjectType						= LONG_MAX			// to force ObjectType enum to be an Int32
};


//----------------------------------------------------------------------
//	FOVType
//
//	Purpose:	these are the types of FOV indicators available
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2005/May/28	MK			5.7			Necessary for FOV information
//
//----------------------------------------------------------------------

typedef short FOVType;
const FOVType FOV_Unknown			= 0;
const FOVType FOV_UserRectangle		= 1;
const FOVType FOV_UserRigel			= 2;
const FOVType FOV_UserCircle		= 3;
const FOVType FOV_UserTelrad		= 4;
const FOVType FOV_CCD				= 5;
const FOVType FOV_Eyepiece			= 6;
const FOVType FOV_Binoculars		= 7;
const FOVType FOV_FinderTelrad		= 8;
const FOVType FOV_FinderRigel		= 9;
const FOVType FOV_FinderOther		= 10;


//----------------------------------------------------------------------
//	FOVGroup
//
//	Purpose:	FOVs are grouped into equipment or specific charts. These
//				are the groupings available.
//
//	Date		 Initials	Version		Comments
//  ----------	 ---------	----------	---------------------------
//	2005/June/13 MK			5.7			Necessary for FOV information
//
//----------------------------------------------------------------------

typedef short FOVGroup;
const FOVGroup FOVGroupUnknown			= 0;
const FOVGroup FOVGroupEquipment		= 1;
const FOVGroup FOVGroupThisChart		= 2;
const FOVGroup FOVGroupAllCharts		= 3;


//----------------------------------------------------------------------
//	OperationT
//
//	Purpose:	The operation type tells the called plug-in what action it should
//				perform.
//
//				A plug-in's entry point must be of the form:
//
//					OSErr main(OperationT inOperation, void* ioParams)
//
//				Where ioParams points to different kinds of structures depending on the
//				requested operation. If ioParams is NULL then the requested operation
//				does not require any parameters. Some operations call for the plug-in to
//				return information in the appropriate structure.
//				Here is a description of each operation (note that a plug-in can choose
//				to do nothing when called with an operation request.)
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/04/01	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
typedef long OperationT;
 
const long op_Initialize			= 0;
	
	// input:	PInitialize*
	// output:	PInitialize*	(fill out the PInitialize structure before returning)
	// called once at begining of program when the plugin is first initilialized. The
	// current resource file will be the plug-in's file when called.

const long op_Terminate				= 1;

	// inputs:	NULL
	// called once when Starry Night terminates

const long op_SetupWindow			= 2;

	// inputs:	WindowPtr
	// informs plug-in of the WindowPtr that was created on its behalf. This is the time for the
	// plugin to do any window specific setup. (see also op_SetupWin32Window, below)
	
const long op_UpdateWindow			= 3;

	// inputs:	RgnHandle (update region), on Win32 a pUpdateRegion** is passed in.
	// called whenever our window needs updating

const long op_MenuCommand			= 4;
	
	// inputs:	NULL
	// called each time plug-in's menu command is selected

const long op_NewScene				= 5;

	// inputs:	PGaze* (or NULL if no new scene)
	// called when new Starry Night window comes to the fore.
	// (If all windows are closed then ioParams will be NULL).

const long op_Centre				= 6;

	// inputs:	PGaze*
	// called when SN centres on a new object

const long op_About					= 7;

	// inputs:	NULL
	// called when user picks About this plug-in from the Apple menu
	
const long op_Idle					= 8;

	// inputs:	PEvent*
	// outputs:	PEvent*
	// if plug-in requested idle events then whenever the user
	// isn't doing anything in Starry Night

const long op_ClickInWindow			= 9;

	// inputs:	PEvent*
	// outputs:	PEvent*
	// called whenever there is a mouse down in the plug-in's window

const long op_DrawLayer				= 10;

	// inputs:	PDraw*
	// called for every update to draw plug-in's layer (see below)

const long op_Selection				= 11;

	// inputs:	PSelection*
	// called whenever user selects new object (NULL if object is deselected)

const long op_CursorPosition		= 12;

	// inputs:	PSelection*
	// called everytime mouse position changes

const long op_LocationChanged		= 13;
	
	// inputs:	PLocation*
	// called whenever the viewing location changes
	
const long op_BuildContextualPopup	= 14;
	
	// inputs:	PBuildContext*
	
const long op_DoContextualPopup		= 15;
	
	// inputs:	PDoContext*
	
const long op_DragDropAcceptable	= 16;

	// inputs:	PDragDropAcceptable*
	// outputs:	PDragDropAcceptable*
	// called to find out if a drog and drop item is acceptable to plug-in 

const long op_ReceiveDrag			= 17;
	
	// inputs:	PDragDrop
	
const long op_GetDrawTimeFuncPtr	= 18;
	
	// outputs:	PDrawTimeFuncPtrs*
	
const long op_FindObjectInDataBase	= 19;
	
	// inputs:	PFindAction*
	// outputs:	PFindAction*
	
const long op_ReintializeFind		= 20;
	
	// inputs:	NULL
	
const long op_DrawIndicator			= 21;

	// inputs:	PIndicator*
	// outputs:	PIndicator*
	// if you have set PInitialize's fLayer to anything other than Depth_None
	// then you will be called with an op_DrawIndicator event for every screen update.
	// This allows you to draw a eyepiece circle on Starry Night's view.

const long op_MenuStatus			= 22;
	
	// inputs:	PMenuStatus*
	// outputs:	PMenuStatus*
	
const long op_TelescopeConfigure	= 23;
	
	// inputs:	NULL

const long op_TelescopeTime			= 24;
	
	// inputs:	PTime*

const long op_TelescopeLocation		= 25;
	
	// inputs:	PLocation*

const long op_TelescopeOpen			= 26;
	
	// inputs:	NULL

const long op_TelescopeClose		= 27;
	
	// inputs:	NULL

const long op_TelescopeTrack		= 28;
	
	// inputs:	NULL
	// you should toggle tracking on/off when you receive this operation
	
const long op_TelescopeSlew			= 29;
	
	// inputs:	PGaze*

const long op_TelescopeSync			= 30;
	
	// inputs:	PGaze*

const long op_PreDraw				= 31;

	// inputs:	PEvent*
	// outputs:	PEvent*
	// called before updating the window. You can change location, gaze, etc.

const long op_PostDraw				= 32;

	// inputs:	PEvent*
	// outputs:	PEvent*
	// called after updating the window.

const long op_SelectionDoubleClick	= 33;

	// inputs:	PSelection*
	// called whenever a selection is double-clicked (to open info window etc).

const long op_TimeChanged			= 34;

	// inputs:	PTime*
	// sent when time changed (i.e. will be sent often if time flow is on)

const long op_FactoryDefaults		= 35;
	
	// inputs:	NULL
	// sent to inform plugin that user whishes all settings to go to factory defaults

const long op_CallBackAddress		= 36;
	
	// inputs:	PCallBackInfo*
	// includes the address of the function to call Starry Night back with

const long op_HomeLocation			= 37;
	
	// inputs:	PLocation*
	// called at program start-up, also called when the user changes the location size

const long op_SetupWin32Window		= 38;
	
	// inputs:	HWND
	// Win32 handle to the new created window that you asked for in op_Initialize

const long op_SceneClick			= 39;

	// inputs:	PEvent*
	// outputs:	PEvent->fOutOperation:	pass out_HandledByPlugin if you don't want SN getting the click
	// Required version: kVersion5Plugin
	// A click in a scene.
	
const long op_FOVIndicatorPosition	= 40;

	// inputs:	PIndicator*
	// outputs:	PIndicator*
	// Required version: kVersion5Plugin
	// To have starry night draw the FOV indicator at a position other than the centre of the screen.

const long op_OSEvent				= 41;

	// inputs:	POSEvent*
	// outputs:	POSEvent*
	// Required version: kVersion6Plugin
	// The structure for passing all events through to you. You must set the PInitialize member fWantsAllEvents to true!.

const long op_SetCursor				= 42;

	// inputs:	PEvent*
	// outputs:	PEvent->fOutOperation:	pass out_HandledByPlugin if you set the cursor, otherwise out_DoNothing
	// Required version: kVersion6Plugin
	// Use this call to change the current mouse cursor shape as needed. For instance the SETI plug-in uses this
	// operation to change the cursor to a pointer when the mouse is over the link to the SETI website.
	
const long op_LatLongChanged		= 43;
	
	// inputs:	PLocation*
	// called whenever the lat long changes (currently called for earth only June 2002)
	
	// const long op_TelescopeAdvanced		= 44; // this has been removed since no longer supported

	//
	//

const long op_TelescopeMotion			= 45;

	// inputs:	PScopeMotion*
	// called whenever user pushes one of the telescope motion controls (up, down, stop etc.)
	
const long op_TelescopePark				= 46;

	// inputs:	NULL
	// called whenever user pushes the telescope Park button

const long op_TelescopeUnpark			= 47;

	// inputs:	NULL
	// called whenever user pushes the telescope UnPark button

const long op_TelescopeSetParkPosition	= 48;

	// inputs:	NULL
	// called whenever user pushes the telescope Set Park Position button

const long op_TelescopeGoHome			= 49;

	// inputs:	NULL
	// called whenever user pushes the telescope Set Park Position button

const long op_ImagingPluginSnapShot			= 50;

	// inputs:	NULL
	// 

const long op_ImagingPluginSnapShotSettings		= 51;

	// inputs:	NULL
	// called whenever user pushes the telescope Snap Shot Settings button

const long op_ImagingPluginImportImageToSN		= 52;

	// inputs:	NULL
	// called whenever user pushes the telescope Import Image button

const long op_FocuserConfigure					= 53;
	
	// inputs:	NULL
	// called whenever user clicks on the Configure button in the Focuser section

const long op_FocuserOpen						= 54;
	
	// inputs:	NULL
	// called whenever Connect button is pushed for the Focuser
	
const long op_FocuserClose						= 55;

	// inputs: NULL
	// called whenever Disconnect button is pushed for the Focuser
	
const long op_FocuserTemperatureCompensation	= 56;

	// inputs: NULL
	// called whenever Temperature Compensation box is checked/unchecked

const long op_FocuserMove						= 57;

	// inputs: long*	 set 
	// called whenever In or Out buttons are pressed. Sends current number of steps with the appropriate sign.
	
const long op_FocuserGoto						= 58;

	// inputs: long*
	// called whenever Goto button is pressed for the focuser. Sends the position to which the focuser should be moved.

const long op_FocuserStop						= 59;

	// inputs: none
	// called whenever Stop button is pressed in order to Stop focuser Move operation.


//----------------------------------------------------------------------
//	Depth Order of Layers
//
//	Purpose:	Starry Night draws a sky view by drawing what can be thought of as a
//				number of transparencies in succession. Each layer is given an ID number
//				and the layers are drawn in order of this ID. So layers having lower numbers
//				get drawn first.
//
//				Plug-ins can return an ID for a layer they wish to draw.
//				(Everytime the sky needs updating the plug-in will be called with an
//				op_DrawLayer).
//
//				You can replace an existing layer by returning the existing
//				layer's ID (so for example if you return fLayer=Depth_Background from
//				op_Initialize, Starry Night will call the plug-in to draw the sky
//				background for each update instead of using its own background drawing routines).
//
//				To add a new layer return an id so that your layer is drawn at the correct
//				time (for example to draw a circle to represent the field of view of a
//				pair of binoculars you could return any number between 10000 and 60000 to have
//				this layer draw after planets but before Starry Night's onscreen info
//				layer. (Note: you can contact Sienna Software at contact@siennasoft.com to
//				obtain a unique layer id that will not be given to others so that your layer
//				won't conflict with another plug-in's layer).
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/04/01	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------

const long Depth_None					=0;		// pass back this if you don't want to draw a layer with your plug-in

const long Depth_Background				=1000;
const long Depth_MilkyWay				=2000;
const long Depth_AllSkyImage			=2100;
const long Depth_ContinentOutlines		=2200;
		
const long Depth_LocalGuides			=3000;
const long Depth_CelestialGuides		=5000;
const long Depth_GalacticGuides			=5500;
const long Depth_ExtragalacticGuides	=5500;
const long Depth_Constellations			=6000;
const long Depth_EclipticGuides			=7000;
const long Depth_NGCIC					=7400;
const long Depth_PGC					=7500;
const long Depth_Messier				=7600;
const long Depth_Images					=7650;		// depth for images layer
const long Depth_CustomData				=8000;		// default depth for users that create custom data
const long Depth_Stars					=9000;
const long Depth_LastCelestial			=9500;		// labels for all preceeding layers get drawn at this point
const long Depth_Planets				=10000;
const long Depth_Telrad					=40000;
const long Depth_NoPersonsLand			=55000;
const long Depth_Overlay				=57000;
const long Depth_OnscreenInfo			=60000;

//----------------------------------------------------------------------
//	Structure:	PInitialize
//
//	Purpose:	this structure should be filled out by the plugin when the
//				op_Initialize operation is requested.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	06/08/01	MK			5.7			fIsFocuserPlugin Added to support a focuser-only plugin (currently Win only).
//	05/01/27	DWW			5.0.2		fIsImagingPlugin Added to allow MaxIm DL (imaging software). Win only at this date.
//	96/04/02	ETL			2.0.0		New for Starry Night 2.0
//
//
//  Plug-in Writers: (Windows only) 
//	fWindowID is really a 'magic number' that you have to set to get a window. 
//	Different windowIDs will correspond to different window styles. 
//	For now you should use 3004 as your window ID. Please email tandersen@siennasoft.com
//	if you are having troubles making windows.
//
//
//
//----------------------------------------------------------------------

typedef struct
{
	long			fPluginAPI;				// version of plug-in API supported
	pBoolean		fSuccess;				// if false then plug-in will not be used
	pBoolean		fWantsMenuItem;			// if this plug-in wants a menu command in settings menu
	pBoolean		fWantsIdleTime;			// if true then plug-in receives op_Idle regularly
	
	pBoolean		fWantsWindow;			// true if the plug-in requires a window
	pBoolean		fWindowVisible;			// true if window is initially visible
	long			fWindowID;				// id of WIND resource for this window
	pBoolean		fWindowFloats;			// true if requested window should float
	pRect			fWindowBounds;			// bounds and placement for the window (in global coordinates)
	
	long			fLayer;					// pass back Depth_None if you don't draw into a sky view. If you either draw directly or have
											// Starry Night draw a Telrad object then you will need to return the depth at which you want
											// the drawing to occur here. For Telrad objects it is suggested that you draw at Depth_Telrad.
	pBoolean		fIsTelescopeController;	// pass back true if you are a telescope controller and want to manage controls in the telescope control panel
	pBoolean		fIsImagingPlugin;		// pass back true if you are a imaging plugin and want to manage controls in the telescope control panel

	pStr255			fWindowMenuItem;		// menu item for opening and closing your window, if your plug-in has a window (fWantsWindow is true)
	pStr255			fAboutMenuItem;			// text of menu item for getting information about your plug-in
	pStr255			fOptionsMenuItem;		// text of menu item for opening an options dialog for your plug-in
	pBoolean		fWantsAllEvents;		// set this to true if you want to get all of the events that go through Starry Night
	pBoolean		fIsFocuserController;	// pass back true if you are a focuser controller and want to manage focuser controls
} PInitialize;

//----------------------------------------------------------------------
//	ScopeDirectionT
//
//	Purpose:	A ScopeDirectionT is passed to the telescope control plugin through
//				a PScopeMotion parameter when the user clicks on one of the motion buttons.
//
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	04/09/01	DWW			5.0.1		Added for advanced telescope control in Mac
//
//----------------------------------------------------------------------
typedef long ScopeDirectionT;
const ScopeDirectionT direction_NONE_STOP		= 0;	// Pass this to stop all motion 
const ScopeDirectionT direction_UP				= 1;	// Start scope moving up
const ScopeDirectionT direction_DOWN			= 2;	// Start scope moving down
const ScopeDirectionT direction_LEFT			= 3;	// Start scope moving left
const ScopeDirectionT direction_RIGHT			= 4;	// Start scope moving right

//----------------------------------------------------------------------
//	ScopeSlewRateT
//
//	Purpose:	A ScopeSlewRateT is passed to the telescope control plugin through
//				a PScopeMotion parameter when the user clicks on one of the motion buttons.
//				The rate should be chosen based on the zoom level (FOV) of the current scene
//
//	NOTES:		rate_4 is the fastest, rate_1 is the slowest.
//
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	04/09/01	DWW			5.0.1		Added for advanced telescope control in Mac
//
//----------------------------------------------------------------------
const double_tsn kMaxFOVInDegreesForSlewRate1 = 2.0;
const double_tsn kMaxFOVInDegreesForSlewRate2 = 10.0;
const double_tsn kMaxFOVInDegreesForSlewRate3 = 30.0;

typedef long ScopeSlewRateT;
const ScopeSlewRateT rate_1		= 1;	// These rates are relative since each scope has its own way of doing slew rates. 
const ScopeSlewRateT rate_2		= 2;	// Starry Night sets this value based on the FOV as above
const ScopeSlewRateT rate_3		= 3;	// Anything larger than kMaxFOVInDegreesForSlewRate3 uses rate_4
const ScopeSlewRateT rate_4		= 4;	//


//----------------------------------------------------------------------
//	Structure:	PScopeMotion
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					op_TelescopeMotion
//
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	04/09/01	DWW			5.0.1		Added for advanced telescope control in Mac
//
//----------------------------------------------------------------------
 
typedef struct
{
	ScopeDirectionT		fMotionDirection;		// Direction of motion of telescope
	ScopeSlewRateT		fRelativeSlewRate;		// A relative slew rate. Must be implemeted differently for different scopes 
	sn_WindowRef		fInWindow;				// Caution: supported in kVersion7Plugin and later only
} PScopeMotion;


//----------------------------------------------------------------------
//	Structure:	PLocation
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					op_LocationChanged
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	00/10/12	Ted			3.1.1		Added fInWindow
//	96/06/12	Ted			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	pStr255			fPlaceName;				// eg. "Toronto"
	double			fEarthLatitude;			// in radians
	double			fEarthLongitude;		// in radians
	double			fElevation;				// in metres
	long			fTimeZoneSeconds;		// seconds off of GMT
	unsigned long	fPrivate;				// A private number for Sienna Use only- Do not change any values passed in here 
	sn_WindowRef	fInWindow;				// Caution: supported in kVersion7Plugin and later only
} PLocation;

//----------------------------------------------------------------------
//	Structure:	PGaze
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					op_Centre - 	both the Alt/Az and Ra/Dec are for the same point in the sky - the gaze direction
//					op_NewScene - 	both the Alt/Az and Ra/Dec are for the same point in the sky - the gaze direction
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	00/10/12	Ted			3.1.1		Added fInWindow
//	98/07/06	Tom			2.1.2		PC plugin support 
//	96/04/01	Ted			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	double			fGazeAzimuth;			// "real world" (see sn_Mathematical2RealWorldAzimuth) azimuth of user's gaze (in radians)
	double			fGazeAltitude;			// "real world" (see sn_Mathematical2RealWorldAzimuth) altitude of user's gaze (in radians)
	double			fPixelsPerRadian;		// magnification
	double			fGazeRa;				// the right ascension of the gaze in the epoch of date (not j2000)
	double			fGazeDec;				// the declination of the gaze in the epoch of date
	sn_WindowRef	fInWindow;				// Caution: supported in kVersion7Plugin and later only
} PGaze;

//----------------------------------------------------------------------
//	Structure:	PDraw
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					sn_GetFOVIndicators
//
//  Plugin API version: kVersion1Plugin - modified since this is version 4.
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/05/27	ETL			2.0.0		New for Starry Night 2.0
//	97/02/11	Tom			2.1 		2.1 - added GWorld stuff.
//
//----------------------------------------------------------------------
 
typedef struct
{
	pRect			fSceneBounds;			// bounds of scene that needs to be drawn
	pBoolean		fIsScrolling;			// true if the user is scrolling the scene
	double			fGazeAzimuth;			// "real world" (see sn_Mathematical2RealWorldAzimuth) azimuth of user's gaze (in radians)
	double			fGazeAltitude;			// "real world" (see sn_Mathematical2RealWorldAzimuth) altitude of user's gaze (in radians)
	double			fPixelsPerRadian;		// magnification
	pGWorldPtr		fGraphicsWorld;			// the GWorld for the current draw - be careful!
	long			fPrivate;				// a private number for use by Sienna - do not alter or use!
	double			fGazeRa;				// ra of the direction user is looking (in radians)
	double			fGazeDec;				// dec of the direction user is looking (in radians)
	sn_WindowRef	fDestinationWindowRef;	// new for version 3: the window ref of the window that is being drawn
	HDC				fDestinationDC;			// kVersion5Plugin The DC that you should do all your drawing into. Will be null for Macintosh plugin. 
} PDraw;


//----------------------------------------------------------------------
//	Structure:	PFov
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following calls is made:
//
//					sn_GetFOVIndicators
//
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//  2005/May/28	MK			5.7			Enables FOV information returns
//
//----------------------------------------------------------------------
typedef struct
{
	FOVType	    fType;		//type of the FOV indicator (see FOVType type for more details)
	char*		fName;		//user or system name of the indicator
	double_tsn	fWidth;		//indicator width (in radians)
	double_tsn	fHeight;	//indicator height (in radians)
	double		fRotation;	//position angle of the indicator - irrelevant for circle FOVs
	char*		fTelescope; //name of the telescope to which FOV belongs
	pBoolean	fIsVisible; //true if indicator is visible to the user
	FOVGroup	fGroup;		//group to which the indicator belongs (Unknown, Equipment, ThisChart, AllCharts)
} PFov;


//----------------------------------------------------------------------
//ActionT
//
//	Purpose:	An ActionT is passed back from the plug-in whenever it receives
//				an op_Idle or op_ClickInWindow event. This allows the plug-in to request
//				Starry Night to do something (such as change the location of the current
//				view, or slew to a point on the celestial sphere, or to find an object.
//
//				Each ActionT has associated with it a parameter structure (fOutParams in
//				PEvent).
//
//				fOutOperation			fOutParams		Description
//				---------------			-----			-------------
//				out_DoNothing			NULL			pass back if you don't want SN to do anything
//				out_SetEarthLocation	PLocation*		pass back this operation to change the
//														location of the current view.
//				out_ChangeGaze			PGazeAction*	pass back to change the direction in which view is looking, using alt az
//				out_CentrePoint			PCentreAction*	pass back to change the direction in which view is looking, using ra dec
//														
//				out_Search				PSearchAction*	to search for a named object
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/12	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
typedef long ActionT;
const long out_DoNothing			= 0;	// NULL
const long out_SetEarthLocation		= 1;	// PLocation*
const long out_ChangeGaze			= 2;	// PGazeAction*
const long out_CentrePoint			= 3;	// PCentreAction*
const long out_Search				= 4;	// PSearchAction*
const long out_Update				= 5;	// NULL
const long out_HandledByPlugin		= 6;	// NULL

//----------------------------------------------------------------------
//	Structure:	PSearchAction
//
//	Purpose:	this is the structure that should get passed from your plug-in
//				to Starry Night whenever you request an out_Search action to
//				be performed.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/12	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	pStr255			fSearchString;			// name of object to be found
	pBoolean		fFindAgain;				// true if you want to continue searching from last found object
	pBoolean		fUseCustomPanZoom;		// true if you want to override SN's pan/zoom options and use those below instead
	pBoolean		fPan;					// true if you want to pan to the found object
	pBoolean		fZoom;					// true if you want to zoom in on the found object
} PSearchAction;

//----------------------------------------------------------------------
//	Structure:	PFindAction
//
//	Purpose:	this is the structure that we get passed from SN when we receive
//				an op_FindObjectInDataBase. If we find the object in out plugin
//				database, we fill out a PSearchAction to send back and set
//				fOutFoundAMatch to true.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/12	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	pStr255			fInFindString;			// name of string for us to find
	pBoolean		fOutFoundAMatch;		// true if we found a match
	PSearchAction	fOutSearchFor;			// object to be found by Starry Night in Sky - usually set fUseCustomPanZoom to false
} PFindAction;

//----------------------------------------------------------------------
//	Structure:	PCentreAction
//
//	Purpose:	this is the structure that should get passed from your plug-in
//				to Starry Night whenever you request an out_CentrePoint action to
//				be performed. Use this if you want SN to center on an Ra / Dec.
//				If you want to centre on an Alt / Az, use out_ChangeGaze and
//				PGazeAction.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/12	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	double		fRightAscension;	// RA to pan view to	(in JNow radians)
	double		fDeclination;		// Dec to pan view to	(in JNow radians)
	pBoolean	fUseCustomPan;		// true if you want to override SN's pan options and use the one below instead
	pBoolean	fPan;				// true if you want to pan to the found object
	pBoolean	fAdjustFOV;			// true if you want to change the FOV
	double		fNewFOV;			// new FOV in radians (if fAdjustFOV is true)
} PCentreAction;

//----------------------------------------------------------------------
//	Structure:	PGazeAction
//
//	Purpose:	this is the structure that should get passed from your plug-in
//				to Starry Night whenever you request an out_ChangeGaze action to
//				be performed. If you want to use ra/dec, then use PCentreAction
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/12	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	double		fGazeAzimuth;		// azimuth of the direction user is looking (in radians)
	double		fGazeAltitude;		// altitude of the direction user is looking (in radians)
	pBoolean	fUseCustomPan;		// true if you want to override SN's pan options and use the one below instead
	pBoolean	fPan;				// true if you want to pan to the found object
	pBoolean	fAdjustFOV;			// true if you want to change the FOV
	double		fNewFOV;			// new FOV in radians (if fAdjustFOV is true)
} PGazeAction;


//----------------------------------------------------------------------
//	Structure:	PEvent
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					op_ClickInWindow
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/05/29	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	pEventRecordPtr	fEventRecord;			// most recent event, or event that triggered action is a pointer to an EventRecord
	ActionT			fOutOperation;			// if you want Starry Night to perform an action in
											// response to the event request it here
	void*			fOutParams;				// pass the appropriate paramater structure for the kVersion3Plugin
											// requested event here. NOTE: Starry Night does not
											// dispose of any memory allocated for this parameter
											// structure so it is best to pass a pointer to a global
											// structure here.
	sn_WindowRef	fInWindow;				// The window associated with this click kVersion5Plugin
} PEvent;


//----------------------------------------------------------------------
//	Structure:	POSEvent
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					op_OSEvent
//					op_SetCursor
//
//  Plugin API version: kVersion6Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	00/07/20	Tom			3.1.0		New for Starry Night 3.1
//
// There is no Starry Night Window given for these events as it would use up 
// a lot of time to find out thes sn_Window associated with the event. 
// Also many events will be for windows such as floaters etc, which have no sn_WindowRef 
//----------------------------------------------------------------------
 
typedef struct
{
	pBoolean 		fEventHandledByPlugin; 	// i/o will be set to false on entry. Set to true if your plugin handled the call
	
	pEventRecordPtr	fEventRecord;			// mac event called every time WaitNextEvent returs got vent to Starry Night, will be NULL for Win32 plugins, 
	
	unsigned long 	fWindowHandle; 			// Win32 Windows handle, really an HWND. 
	unsigned long 	fInMessage; 			// Win32 Message, really an UINT. 
	unsigned long 	fwParam; 				// Win32 Windows wParam, really an WPARAM. 
	unsigned long 	flParam; 				// Win32 Windows lParam, really an LPARAM. 
	
	unsigned long 	fReserved; 				// Reserved for future use 
} POSEvent;


//----------------------------------------------------------------------
//	Structure:	PSelection
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever one of the following operations is requested:
//
//					op_Selected
//					op_CursorPosition
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/10/13	ETL			2.0.0		added fUserFormattedName
//	96/05/29	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------

typedef struct
{
	pStr255			fObjectName;			// default name of object
	short			fObjectIconID;			// icon id for icon that represents object (or 0 if none)
	pStr255			fConstellationName;		// name of constellation that object is in
	double			fAz;					// "real world" (see sn_Mathematical2RealWorldAzimuth) azimuth of mouse or object (in radians)
	double			fAlt;					// "real world" (see sn_Mathematical2RealWorldAzimuth) altitude of mouse or object (in radians)
	double			fRightAscension;		// RA of mouse or object (in radians) using epoch of current date
	double			fDeclination;			// declination of mouse or object (in radians) using epoch of current date
	pStr255			fObjectType;			// string describing the object's kind
	double			fMagnitude;				// magnitude if object supports magnitude (otherwise kUndefinedMagnitudeValue)
	double			fAngularSize;			// angular size if object supports ang size (otherwise kUndefinedAngleValue)
	pStr255			fUserFormattedName;		// name of object as user has decided they want it displayed
											// (eg. perhaps "Alpha" instead of Sirius) May be same as fObjectName.
	unsigned long	fObjectKey;				// a key for the object, made up by the object, that is a fairly unique 
											// 32bit reference for the object. .
	long			fObjectLayerID;			// The layer ID of the object selected. The layer ID is a different number for each layer
	TSelection*		fSelection;				// A private number for Sienna Use only- Do not change any values passed in here 
	TScene*			fScene;					// A private number for Sienna Use only- Do not change any values passed in here 
	pBoolean		fObjectIsSelectable;	// true if the object is a selectable entity in Starry Night
	pBoolean		fIsNewPosition;			// only set for op_CursorPosition: true if cursor has moved
} PSelection;

//----------------------------------------------------------------------
//	Structure:	PDrawTimeObject
//
//	Purpose:	this is the structure that gets passed from Starry Night to a plug-in
//				whenever an object is being drawn
// 	Note:		Since this is called with speed in mind, the values 
//				presented here are a bit raw at times
//
//  Plugin API version: kVersion2Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/12/05	Tom			2.1			Leno
//
//----------------------------------------------------------------------

typedef struct
{
	double			fPositionXFloat;		// The position of the object on the sphere, J2000
	double			fPositionYFloat;		// The x,y,z are given as floats, 0-->1. 
	double			fPositionZFloat;		// Note that this changed in going from version Starry Night Pro 3 to version 4! 
	unsigned long	fObjectKey;				// a key for the object, made up by the object, that is a fairly unique, (unique?, even)
											// 32bit reference for the object. .
	long			fLayerSerialNum;		// The ID of the layer that this object is in
	long			fOutShowMarker;			// set to true if you want to show a marker at the passed location	
	long			fCatalogNumber;			// a catalog number for the object	
	long			fCatalogID;				// the catalog kind	
	long			fObjectKind;			// the kind of object. (Raw info only)
	long			fMagnitude;				// The magnitude times 100. So a mag 6.3 star is stored as 630
	long			fStarBMinusV;			// star temperature for SAO stars only
	long			fStarSpectralClass;		// star spectral class
	long			fDistanceParsecs;		// object distance parsecs
	pPoint			fWindowPoint;			// the spot the object is drawing at	
											
											// in order to use fOtherData you have to regiter at DrawTimeSetup to use it
	unsigned char*	fOtherData;				// pointer to a pascal string that holds other data - (plugins do not own the string! - Read only) - will usually be NULL
											// no data available is indicated by fOtherData == NULL, and fMoreDataPlease != 0
	pBoolean		fIsHIPStar;
	TScene*			fScene;					// internal use only (leave as NULL)
} PDrawTimeObject;

typedef struct
{
	TScene*			fScene;					// private, for internal use only
	pBoolean		fNeedMoreData;
} PDrawSetup;


typedef void		(*DrawTimeFuncPtr)(PDrawTimeObject* ioObject);
typedef pBoolean	(*DrawTimeSetupFuncPtr)(PDrawSetup* ioDrawSetup);

//----------------------------------------------------------------------
//	Structure:	PDrawingTimeFunctionPtrs
//
//	Purpose:	this is the structure that holds the two pointers to the 
//				plugin functions that we will call at the time 
//				each object is drawn in Starry Night. 
//				
// 	Note:		Since the draw object calls are very speed sensitive
//				we will only call native versions of the plugin's code
//				So for PowerPC execution, yu must provide a PowerPC 
//				function pointer!
//				
//
//  Plugin API version: kVersion2Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	97/01/23	Ted			2.1.0		Leno
//	96/12/05	Tom			2.1.0		Leno
//
//----------------------------------------------------------------------

typedef struct
{
	DrawTimeFuncPtr			fPPCFuncPtr;		// Pointer to a PowerPC function,  prototype void* pluginFunc(const PDrawTimeObject* ioObject)
	DrawTimeFuncPtr			notUsed;
	DrawTimeSetupFuncPtr	fPPCSetupFuncPtr;	// Pointer to a PowerPC function
	DrawTimeSetupFuncPtr	notUsed2;
	pBoolean				fCallForDimStars;	// return true if you want to be called even for the very dimmest of stars that are drawn
} PDrawTimeFuncPtrs;


//----------------------------------------------------------------------
//	Structure:	PMenuStatus
//
//	Purpose:	passed to the plug-in to determine the status of a menu item (now
//				are buttons in the Telescope panel. The plug-in
//				passes back whether the referenced menu item is enabled, whether it has a
//				check mark, and what it's menu text should be (the default menu text is
//				the current menu item's text and normally is not adjusted).
//				Used with op_MenuStatus.
//
//  Plugin API version: kVersion2Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	98/07/03	ETL			2.1.2		New for 2.1.2
//
//----------------------------------------------------------------------

// Note that the cmd_TelescopeTime and  cmd_TelescopeLocation buttons have been
// removed from the UI. If you want to implement these in your plugin, you should 
// enable cmd_TelescopeAdvanced and implement your own interface...

typedef struct
{
	long		fMenuCommand;		// currently the only menu items you will be ever asked about are:
									//		cmd_TelescopeConfigure
									//		cmd_TelescopeLocation
									//		cmd_TelescopeOpen
									//		cmd_TelescopeClose
									//		cmd_TelescopeTrack
									//		cmd_TelescopeTime
									//		cmd_TelescopeSlew
									//		cmd_TelescopeSync
									//		cmd_TelescopeAdvanced
	pBoolean	fIsEnabled;			// whether or not the menu item is enabled
	pBoolean	fHasCheck;			// whether or not the menu item should have a checkmark
	pStr255		fMenuText;			// default menu item's text
} PMenuStatus;

//----------------------------------------------------------------------
//	Structure:	PTime
//
//	Purpose:	passed to the plug-in to get it to update the telescope controller's time.
//				Starry Night passes the user's current time in this structure.
//				Used with op_TelescopeTime.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	98/07/03	ETL			2.1.2		New for 2.1.2
//
//----------------------------------------------------------------------

typedef struct
{
	double			fJulianDate;		// universal time
	unsigned long	fPrivate;			// A private number for Sienna Use only- Do not change any values passed in here 
} PTime;

//----------------------------------------------------------------------
//	Structure:	PBuildContext
//
//	Purpose:	this structure is passed to a plug-in when op_BuildContextualPopup is called.
//				The plug-in can add menu items to the passed contextual popup menu which
//				is being built for the passed object. If the user selects a menu item from
//				the contextual menu we will be called again with an op_DoContextualPopup
//				operation so that we can respond.
//
//  Plugin API version: kVersion2Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/16	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	PSelection	fObject;				// object whose contextual menu is being built
	pBoolean	fObjectBeingDeselected;	// true if object is already selected (in which case it is going
										// most likely going ot be deselected
	pMenuHandle	fMenuHandle;			// menu handle of menu being built
	void*		fPrivate;				// private data-do not change
} PBuildContext;

//----------------------------------------------------------------------
//	Structure:	PDoContext
//
//	Purpose:	if the user selects a menu item from a contextual menu that is build when
//				they hold the mouse down over an onscreen Starry Night object then we will be
//				called and informed what menu command they selected. We tell Starry Night
//				whether we handled the command. We can respond to any menu command, not just
//				our own.
//				Used with the op_DoContextualPopup operation.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/16	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
const long do_Select						= 1000;		// will select object
const long do_Deselect						= 1001;		// will deselect object
const long do_Centre						= 1002;		// will centre object
const long do_CentreAndLock					= 1003;		// will centre and lock on object
const long do_SelectConstellation			= 1004;		// will select fConstellationName
const long do_Magnify						= 1005;		// zooms the object into view
const long do_GetInfo						= 1006;		// opens new Get Info window for object
const long do_ShowOrbit						= 1007;		// if the object is a planet, toggles orbit on and off
const long do_TrackLocalPath				= 1008;		// if the object is a planet, toggles local path on and off
const long do_TrackCelestialPath			= 1009;		// if the object is a planet, toggles celestial path on and off
const long do_GoThere						= 1010;		// if the object is a planet or Hipparchos star, changes location to view from there
const long do_Settings						= 1011;		// opens settings dialog for this kind of object
const long do_AddImage						= 1013;		// adds an image 
const long do_EditImage						= 1014;		// edits an image 
const long do_Ecliptic						= 1015;		// shows ecliptic

const long do_HighlightGroup				= 1017;		// if galaxy, will select galaxy's group
const long do_HighlightFilament				= 1018;		// if galaxy, will select galaxy's filament
const long do_HighlightType					= 1019;		// if galaxy, will select galaxy's type
const long do_RotateDefault					= 1020;		// return to default rotation centre
const long do_CentreGroup					= 1021;		// centre group
const long do_CentreFilament				= 1022;		// centre filament
const long do_HighlightCategory				= 1023;		// highlight filament
const long do_HideInfo						= 1024;		// opens new Get Info window for object
const long do_RiseTime						= 1025;		// resets clock to rise time for this object
const long do_TransitTime					= 1026;		// resets clock to tranist time for this object
const long do_SetTime						= 1027;		// resets clock to set time for this object
const long do_StartCharting					= 1028;		// starts charting this object in the conjunction searcher
const long do_StopCharting					= 1029;		// stops charting this object in the conjunction searcher
const long do_GraphElongations				= 1030;		// starts charting elongations of object's moons
const long do_AddSelectionToPlanner			= 1031;		// adds or removes the selection to the planner panel
const long do_GoToLocalView					= 1033;		// will change the scene to home view for an interesting planner item
const long do_GoToBestView				    = 1034;		// will change the scene to best view for an interesting planner item
const long do_AddChildPlanetOfDefaultType	= 1035;		// orbit editor
const long do_AddAsteroid				    = 1036;		// orbit editor
const long do_AddComet					    = 1037;		// orbit editor
const long do_EditPlanet				    = 1038;		// orbit editor
const long do_DeletePlanet				    = 1039;		// orbit editor
const long do_SunHaloMenu				    = 1041;
const long do_SunHaloNever				    = 1042;
const long do_SunHaloDaytime			    = 1043;
const long do_SunHaloAlways				    = 1044;
const long do_SunLensFare				    = 1045;
const long do_EnlargeMoonSize			    = 1046;
const long do_SlewTelescope			   		= 1047;		// Telescope control
const long do_SynchTelescope			    = 1048;		// Telescope control
const long do_FOVIndicatorMenu			    = 1049;
const long do_SavePlanetAsQuickTimeVR	    = 1050;
const long do_OnlineInfo				    = 1051;
const long do_AddAllChartsTelrad			= 1052;
const long do_AddAllChartsRigelQuickfinder	= 1053;
const long do_AddAllChartsCircular			= 1054;
const long do_AddAllChartsRectangular		= 1055;
const long do_AddThisChartTelrad			= 1056;
const long do_AddThisChartRigelQuickfinder	= 1057;
const long do_AddThisChartCircular			= 1058;
const long do_AddThisChartRectangular		= 1059;
const long do_ToggleLayer					= 1060;
const long do_GenerateEphemides				= 1061;
const long do_GoogleMap						= 1062;
const long do_SetTimeToLaunchDate			= 1063;
const long do_MarkLocation					= 1064;
const long do_UnMarkLocation				= 1065;
const long do_UpdateSETI					= 10000;

typedef struct
{
	pBoolean	fMenuHandled;			// return true here if you handle menu command and don't want Starry Night to get it
	PSelection	fObject;				// object whose contextual menu is being built
	pBoolean	fObjectBeingDeselected;	// true if object is already selected (in which case it is going
										// most likely going ot be deselected
	short		fMenuItem;				// menu item that was selected
	long		fMenuCommand;			// if the menu item selected was one of Starry Night's built in
										// one's then fMenuCommand contains the ID of the command that will
										// be performed (see constants above), otherwise contains 0.
} PDoContext;

//----------------------------------------------------------------------
//	Structure:	PDragDropAcceptable
//
//	Purpose:	this structure is passed to a plug-in when op_DragDropAcceptable is called.
//				If the plug-in finds the described drag and drop item acceptable (meaning that
//				it can accept or wants to receive drag and drop events for this kind of item)
//				then it can indicate so in this record.
//
//  Plugin API version: kVersion1Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/29	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	pDragReference		fDragReference;
	pItemReference		fItemReference;
	pBoolean			fOutIsAcceptable;				// return true here if item is acceptable for windows
	pBoolean			fOutIsAcceptableForObjects;		// return true here if item is acceptable for stars,planets,etc.
} PDragDropAcceptable;

//----------------------------------------------------------------------
//	Structure:	PIndicator
//
//	Purpose:	this structure is passed to a plug-in when op_DrawIndicator is called.
//				(To receive op_DrawIndicator messages you will need to set PInitialize's
//				fLayer when you get op_Initialize to the depth at which you want the
//				telrad object drawn--usually Depth_Telrad).
//
//	Note:    	You can draw multiple eyepiece objects (for example a spotting scope and the main scope)
//				by setting fDoneDrawing to false until you have completed all the eyepiece objects. You
//				will continue getting op_DrawIndicator until you pass back fDoneDrawing as true.
//				You will receive one op_DrawLayer message before you start receiving the op_DrawIndicator
//				messages so you can perform any setup you wish to do there).
//
//				Starry Night calls you like this:
//					op_DrawLayer
//					op_DrawIndicator
//					op_DrawIndicator
//					.
///					.
//				    . until you pass fDoneDrawing as true.
//
//
//				op_FOVIndicatorPosition: With this operation, Starry Night is almost ready to draw an FOV indicator 
// 										 you can use the fCentreRA and fCentre dec to move it around. PLEASE don't change the 
//										 colour, size, etc of the FOV indicator. The user has set up their indicators the way that
//										 they want them. op_FOVIndicatorPosition allows the user to use Starry Night's interface for 
//										 selecting  and setting up the eypiece circles, while allowing the plugin to move them around on 
//										 the sky. Also keep in mind that you should only move the FOV indicator around for the 
//										 window that you have set as your telescope window. Don't change the fDrawIndicator of fDoneDrawing fields.z
//
//
//				fCoordSystemOfIndicator: 	Change this if you want to the coordinate system you have that is handy. 
//											This is very useful for showing camera rectangles, just use the coord system of the telescope mount.
//
//  Plugin API version: kVersion2Plugin and later for some features
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	98/07/03	Tom			3 .0.0		New for Starry Night 2.1.2 Bob Denny Version
//
//----------------------------------------------------------------------

const long Indicator_Circle				= 0;
const long Indicator_Rectangle			= 1;
const long Indicator_Telrad				= 2;
const long Indicator_RigelQuickfinder	= 3;
const long Indicator_UnalignedRect		= 4;   // this rect will ignore the rollangle, and always plot a rect that is straight up and down in the window

typedef struct
{
	pBoolean			fDrawIndicator;					// return true here if you want one drawn
	unsigned char		fIndicatorStyle;				// Indicator_Circle, Indicator_Rectangle, Indicator_Telrad or Indicator_RigelQuickfinder
														//	(for circle fVertical is used as diameter)
	pBoolean			fDoneDrawing;					// true if this is the only indicator, false if you draw more than one
	double				fCentreRA;						// Right ascension (in radians) using epoch of current date
	double				fCentreDec;						// Declination (in radians) using epoch of current date
	double				fVertical;						// Dec span (diameter) of the rectangle (circle) to  plot
	double				fHorizontal;					// Ra span of rectangle to  plot
	double				fRollAngle;						// optional: Roll angle of camera (set to zero for unkown)
	double				fPixelsPerRadian;				// INPUT: pixels per radian, so you can get an idea of the size of the thing drawn - sizeInPixels = fPixelsPerRadian*fVertical
	unsigned short		fRed;							// color: for white pass out red = green = blue = 65535 == USHRT_MAX
	unsigned short		fGreen;							// black is 0 0 0 (but don't use black), a dark red might be nice
	unsigned short		fBlue;							// 0.7*USHRT_MAX, 0.1*USHRT_MAX, 0.1*USHRT_MAX
	pStr255				fString;						// Optional name of indicator. Pascal string.
	sn_WindowRef		fWindowThatIsDrawing;			// IN: kVersion5Plugin You should only usually draw the indicator at your custom position for the 'telescope' window
	long				fCoordSystemOfIndicator;		// kVersion6Plugin: Set this to the coord sys that you are passing in. Currently , SN always passes in kSNCelestialJNowSystem, change to alt az or whatever if that is easier for you.
} PIndicator;




//----------------------------------------------------------------------
//	Structure:	PDragDrop
//
//	Purpose:	this structure is passed to a plug-in when op_ReceiveDrag is called.
//				If the user dropped an object in a window or over an object in a window
//				then your plug-in will receive this message.
//
//  Plugin API version: kVersion2Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	96/06/29	ETL			2.0.0		New for Starry Night 2.0
//
//----------------------------------------------------------------------
 
typedef struct
{
	pDragReference	fDragReference;
	pItemReference	fItemReference;
	pBoolean		fDroppedOnObject;	// true if item was dropped on an object (star, etc) otherwise was dropped in win
	PSelection		fObject;			// description of the object that the item was dropped on
} PDragDrop;


//----------------------------------------------------------------------
//	Structure:	PXYZCoordinates
//
//	Purpose:	Plugins can use this structure to pass coordinates to Starry Night
// 				with the Callback API
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
// coordinate systems that we support
const long kSNNoCoordinateSystem	= 1; // never used
const long kSNAltAzSystem			= 2;
const long kSNGalacticSystem		= 3;
const long kSNEclipticSystem		= 4;
const long kSNCelestialJ2000System	= 5;
const long kSNCelestialJNowSystem	= 6;
const long kSNOrientationSystem		= 7; // the coordinate system of the passed window. For windows in the default orientation, this is the same as kSNAltAzSystem
const long kSNSuperGalacticSystem	= 8;

typedef struct
{
	double			x;
	double			y;
	double			z;
} PXYZCoordinates;

//----------------------------------------------------------------------
//	Structure:	PSphericalCoordinates
//
//	Purpose:	Use this to convert your coords to/from XYZ form. 
//				The callback API's use the XYZ form as they are faster
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
typedef struct
{
	double			ra;		// aka azimuth, ra, longitude
	double			dec;	// aka altitude, dec, latitude
	double			radius;	// usually set to 1, for star coordinates
} PSphericalCoordinates;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Call Back API
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


extern "C" 
{

// This set of defines allows the Starry Night Application to export the exact same 
// functions as a plugin will import.

#if TARGET_OS_MAC && !__mwlinker__
	// Define out the SN Call and SN Callback for Mac 
	// Note that we have used #pragma export to export the calls from starrynight
	#define SNCall
	#define SNCallBack
#else
	#if qBuildingPlugin
		#define SNCall __declspec(dllexport)
		#define SNCallBack __declspec(dllimport)
	#else
		#define SNCallBack __declspec(dllexport)
		#define SNCall __declspec(dllimport)
	#endif
#endif


// you as a plugin must export this one call. This does it
//------------------------------
SNCall short DoOperation(OperationT inOperation, void* ioParams);


//----------------------------------------------------------------------
//-----------                                     ----------------------
//-----------  Starry Night Callbck API           ----------------------
//-----------                                     ----------------------
//----------------------------------------------------------------------
// The rest of this Header contains the list of calls that Starry Night supports to call back.
// If you want to call these functions, just call them, as when your dll or shlb(Mac) is 
// loaded, these calls will have been linked to your plugin.
// 
// See also the linking notes at the top of this file.
//
// All of these calls return a 32bit long that is an error code
// positive numbers (including 0) mean that everything is oK, with 0 meaning nothing to support
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Call back return codes:
typedef long snErr;
const snErr snNoErr 					= 0;	// oK
const snErr snErr_Failed 				= -1;	// failed, for some unknown reason		
const snErr snErr_CallAtIdleOnly 		= -2;	// you can only call this call during idle time
const snErr snErr_cmdNotAvailable 		= -3;	// this command is not avialable (for instance menu command is dimmed out)
const snErr snErr_LayerNotFound	 		= -4;	// The layer you asked for was not found. Perhaps you have the name for the layer wrong?
const snErr snErr_ParameterError	 	= -5;	// One or more of the passed parameters (arguments) to a function was out or range or wrong
const snErr snErr_noDocumentFound	 	= -6;	// You passed in that you wanted something done to a Starry Night window, and that window was not found
const snErr snErr_InternalError	 		= -7;	// Starry Night made an error processing your request
const snErr snErr_ViewerNotOnPlanet	 	= -8;	// The viewer is not on a planet, so what you are asking for does not make sense
const snErr snErr_PlanetNotFound		= -9;	// the planet you asked to find was not found
const snErr snErr_LayerHasNoSelections	= -10;	// the layer you want is does not have selectable objects (ie: milky way layer)
const snErr snErr_NoObjectFound			= -11;	// No object was found that matched your request
const snErr snErr_NoSelection			= -12;	// No selection was found for the passed window
const snErr snErr_UnknownScreenMode		= -13;	// the screen mode you passed was not a known kind
const snErr snErr_NoHRDiagramFound		= -15;	// The HR diagram was not found. Certain versions of Starry Night may ship without this capability
const snErr snErr_UnknownFlowState		= -16;	// You asked for a flow state that was not found in a call to SetTimeFlowState() or like that
const snErr snErr_NullParameter			= -17;	// You have passed a parameter as NULL, when we need it to point to correct object
const snErr snErr_AlreadyOnStationaryLoc = -18;	// you are trying to move to a stationary location, when you are already on one
const snErr snErr_ValueNotFound			= -19;	// When trying to get/set a value for a window, the passed value label was not found 
const snErr snErr_NotDrawing			= -20;	// You have passed a document which was found, but the scene is not being drawn


// Constants - See the associated call


//sn_SetOrientation(sn_WindowRef inWindowRef, long inOrientation);
// These are NOT the things you use for the coord system picking
// If you want to pick a coord system use for instance kSNCelestialJ2000System  
typedef long sn_Orientation;
const sn_Orientation kOrientationLocal 			= 100;
const sn_Orientation kOrientationEquatorial 	= 102;
const sn_Orientation kOrientationEcliptic 		= 103;
const sn_Orientation kOrientationGalactic 		= 104;
const sn_Orientation kOrientationSuperGalactic 	= 105;

//sn_SetFlip(sn_WindowRef inWindowRef, long inFlip);
typedef long sn_Flip;
const sn_Flip kFlipNone 		= 201;
const sn_Flip kFlipHorizontal 	= 202;
const sn_Flip kFlipVertical 	= 203;
const sn_Flip kFlipBoth 		= 204;


//sn_TurnHorizonOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn, long inFeature);
typedef long sn_HorizonFeature;
const sn_HorizonFeature kHorizonOption_noChange 		= 300;  	// use this to simply turn on/off the horizon (no cange in translucency or style)
// Horizion Translucency
const sn_HorizonFeature kHorizonOption_Line 			= 301;		// horizon will draw as line (Not compatible with kHorizonOption_Photorealistic. If style is currently Photorealistic no action is performed.)
const sn_HorizonFeature kHorizonOption_Opaque 			= 302;		// horizon will draw as filled in
const sn_HorizonFeature kHorizonOption_Translucent 		= 303;		// see through horizon
// Other Horizion Options
const sn_HorizonFeature kHorizonOption_CompassPointsOn 	= 304;		// show the compass points
const sn_HorizonFeature kHorizonOption_CompassPointsOff = 305;		// hide the compass points
const sn_HorizonFeature kHorizonOption_TreesEtcOn 		= 306;		// show trees, clouds, houses, etc
const sn_HorizonFeature kHorizonOption_TreesEtcOff 		= 307;		// hide trees, clouds, houses, etc
const sn_HorizonFeature kHorizonOption_ShadowsOn 		= 308;		// shadows on trees
const sn_HorizonFeature kHorizonOption_ShadowsOff 		= 309;		// shadows on trees
const sn_HorizonFeature kHorizonOption_NightCloudsOn 	= 310;		// show clouds at night
const sn_HorizonFeature kHorizonOption_NightCloudsOff 	= 311;		// show clouds at night
// Horizion Styes
const sn_HorizonFeature kHorizonOption_Flat 			= 312;		// Flat (featureless) horizon
const sn_HorizonFeature kHorizonOption_Custom			= 313;		// Customizible CG horizon
const sn_HorizonFeature kHorizonOption_Photorealistic	= 314;		// Photorealistic horizion (Not compatible with kHorizonOption_Line.  If Translucency is currently Line no action is performed.)


//sn_TurnGuidesOnOff(sn_WindowRef inWindowRef, long inGuideLayer, long inGuideFeature, pBoolean inTurnOn);
// which guides you want on:
typedef long sn_GuideLayer;
const long kLocalGuidesLayer 		= 500;
const long kCelestialGuidesLayer 	= 501;
const long kGalacticGuidesLayer 	= 502;
const long kEclipticGuidesLayer 	= 503;
const long kSuperGalacticGuidesLayer = 504;
// guide prefs
typedef long sn_GuideLayerFeature;
const sn_GuideLayerFeature kMeridian	= 600; 
const sn_GuideLayerFeature kEquator 	= 601; // for the ecliptic, this option will draw the ecliptic
const sn_GuideLayerFeature kGrids 		= 602;
const sn_GuideLayerFeature kLabels 		= 603;
const sn_GuideLayerFeature k3DAxes 		= 604;

//sn_TurnOnscreenInfoOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn, long inFeature, pBoolean inFeatureOn);
typedef long sn_OnScreenInfoFeature;
const sn_OnScreenInfoFeature kOnScreenInfo_NoFeatureChange 	= 700;
const sn_OnScreenInfoFeature kOnScreenInfo_Location 		= 701;
const sn_OnScreenInfoFeature kOnScreenInfo_LocalTime 		= 702;
const sn_OnScreenInfoFeature kOnScreenInfo_UniversalTime 	= 703;
const sn_OnScreenInfoFeature kOnScreenInfo_JulianDate 		= 704;
const sn_OnScreenInfoFeature kOnScreenInfo_AltAz 			= 705;
const sn_OnScreenInfoFeature kOnScreenInfo_RaDec 			= 706;
const sn_OnScreenInfoFeature kOnScreenInfo_FieldOfView 		= 707;
const sn_OnScreenInfoFeature kOnScreenInfo_Orientation 		= 708;
const sn_OnScreenInfoFeature kOnScreenInfo_ShowOnlyWhileScrolling	= 709;
const sn_OnScreenInfoFeature kOnScreenInfo_ShowCompass 			= 710;
const sn_OnScreenInfoFeature kOnScreenInfo_ShowAtTopLeft 		= 711; // NOTE: Passing inFeatureOn true/false has no effect for these
const sn_OnScreenInfoFeature kOnScreenInfo_ShowAtTopRight 		= 712; // NOTE: Passing inFeatureOn true/false has no effect for these
const sn_OnScreenInfoFeature kOnScreenInfo_ShowAtBottomRight 	= 713; // NOTE: Passing inFeatureOn true/false has no effect for these
const sn_OnScreenInfoFeature kOnScreenInfo_ShowAtBottomLeft 	= 714; // NOTE: Passing inFeatureOn true/false has no effect for these
const sn_OnScreenInfoFeature kOnScreenInfo_LocationElevation	= 715; // NOTE: Elevation only shows if kOnScreenInfo_Location in ON!
const sn_OnScreenInfoFeature kOnScreenInfo_DistanceFromSun		= 716;

//sn_TurnConstellationsOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn, long inFeature, pBoolean inFeatureOn);
typedef long sn_ConstellationFeature;
const sn_ConstellationFeature kConstellations_NoFeatureChange	= 800;
const sn_ConstellationFeature kConstellations_ZodiacOnly 		= 801;
const sn_ConstellationFeature kConstellations_Boundaries 		= 802;
const sn_ConstellationFeature kConstellations_Lines 			= 803;
const sn_ConstellationFeature kConstellations_Pict 				= 804;
const sn_ConstellationFeature kConstellations_Labels 			= 805;

//sn_GetViewerLocationInfo(sn_WindowRef inWindowRef, double* outLat, double* outLong, double* outElevationAu, long* outLocationType, pBoolean* outHovering);
typedef long sn_LocationType;
const sn_LocationType kPlanetLocation 		= 901;
const sn_LocationType kStationaryLocation 	= 902;

//sn_FullScreenMode(sn_WindowRef inWindowRef, long inMode);
typedef long sn_ScreenMode;
const sn_ScreenMode kNormalScreenMode 		= 1001;
const sn_ScreenMode kFullWithMenuScreenMode = 1002;  // Now same as kFullScreenMode. No menus. Version 4.5.0
const sn_ScreenMode kFullScreenMode 		= 1003;

//sn_SetTimeFlowState(sn_WindowRef inWindowRef, long inFlowState)
typedef long sn_TimeFlowState;
const sn_TimeFlowState kFlowBackward 		= 1101;
const sn_TimeFlowState kFlowStop 			= 1102;
const sn_TimeFlowState kFlowForward 		= 1103;

//sn_SetTimeFlowState(sn_WindowRef inWindowRef, long inFlowState)
typedef long sn_FontStyle;
const sn_FontStyle kStyleNormal 		= 1201;
const sn_FontStyle kStyleBold 			= 1202;
const sn_FontStyle kStyleItalic 		= 1203;
const sn_FontStyle kStyleUnderline 		= 1204;

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	File Menu
//
// 				These calls can only be called during the op_idle.
//	Purpose:	The file menu commands are mostly implemented. 
//				Generally there should be a way to things without 
//				user nvolvelment, if you are willing to secify the file 
//				that Starry Night needs to save a window to or build a data 
//				file for, etc.
//
//				A file is represented by three things:
//					invRefNum: on Windows set to 0   Mac needs vRefNum as from an FSSpec 
//					inParID:   on Windows set to 0	 Mac needs parID as from an FSSpec
//  (pascal string)	inName:	   on Windows path to the file. Mac needs File name
// 
//				if you set the length of the string to 0, then Starry Night will ask 
//				the user for the file needed. 
//
//					
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_NewWindow
//
//	Purpose:	we make a new window in Starry Night
//				The window ref is returned.
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_NewWindow(sn_WindowRef* outWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_OpenWindow
//
//	Purpose:	Opens a window in Starry Night. If the window is already open,
//				just returns a ref num for the already opened window
//	
//	Two options:
// 	1) everything to zero, inName[0] = 0, and the user will be called to pick a file.
//  2w) Windows: pass in a path inName, set  invRefNum, inParID to zeros.
//  2m) Mac: pass in the invRefNum, inParID, inName, from a file spec for a file
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_OpenWindow(sn_WindowRef* outWindowRef, long invRefNum, long inParID, pStr255 inName);

//----------------------------------------------------------------------
//	SNCallBack	sn_CloseWindow
//
//	Purpose:	closes front most window if inWindowRef == 0, 
//				else it closes the passed window, if found.
//				never saves any changes, so if you want to 
//				save changes, then call SaveWindow first.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_CloseWindow(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_SaveWindow
//
//	Purpose:	Saves the passed window. If there is no file as yet specified for the
//				window, then the user will be asked to supply one.
//				If you don't want the user to get involved, then 
//				use save as first, passing in a file.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SaveWindow(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_SaveAsWindow
//
//	Purpose:	Saves the passed window with a new name. 
//				If you don't specify a name, the user has to type one in.
//				If you don't want the user to get involved, then  pass in a file.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SaveAsWindow(sn_WindowRef inWindowRef, long invRefNum, long inParID, pStr255 inName);

//----------------------------------------------------------------------
//	SNCallBack	sn_SaveSettings
//
//	Purpose:	Saves the options for the passed window.
//				This means that the color of the constellations, names, font sizes, etc
//				are put into a file. If you don't pass a file, then the 
//				user will be called to give the options a name.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SaveSettings(sn_WindowRef inWindowRef, long invRefNum, long inParID, pStr255 inName);

//----------------------------------------------------------------------
//	SNCallBack	sn_SaveSettingsAsDefault
//
//	Purpose:	Saves the options for the passed window as default.
//				as usual, if you pass in 0 for the window ref, 
//				Starry Night will use the top window.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SaveSettingsAsDefault(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_UseDefaultSettings
//
//	Purpose:	Uses the default settings for the passed window.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_UseDefaultSettings(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_UseOtherSettings
//
//	Purpose:	Will use some other set of options as passed in from the 
//				file, or as chosen by the user.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_UseOtherSettings(sn_WindowRef inWindowRef, long invRefNum, long inParID, pStr255 inName);

//----------------------------------------------------------------------
//	SNCallBack	sn_BuildDataFile
//
//	Purpose:	Will build a data file that can be used as a 
//				dataset of fixed objects for Starry Night.
//				You either pass in both files or set both blank.
//				The inName file is the .dm text file, 
//				The destination file should end with .ssd, so it will be a valid data file
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_BuildDataFile(long invRefNum, long inParID, pStr255 inName, long destvRefNum, long destParID, pStr255 destName);

//----------------------------------------------------------------------
//	SNCallBack	sn_BuildUSNODataFiles
//
//	Purpose:	Will build a database of USNO stars in SN format.
//				USNO *.acc and corresponding *.cat files used to generate
//				the database must be located in the directory sourceFolderName
//				within "Sky Data" directory.
//				The process data is output to "Sky Data/USNO". This destination directory
//				must have appropriate USNO txt files located in it prior to processing.
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	05/May/12	MK			5.0.5+		Ability to specify full source and destination paths
//										will be added in the next version
//
//----------------------------------------------------------------------
SNCallBack snErr sn_BuildUSNODataFiles(const char* sourceFolderName = "usnoa");

//----------------------------------------------------------------------
//	SNCallBack	sn_ExportSkyData
//
//	Purpose:	Will build a data file that refelcts what is on the 
//				screen at the time. It will output data for each star, planet, etc that is on the sky
//				you can turn layes on or off prior to calling this in order to 
//				only get data for one object type. Zooming in is another trick.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ExportSkyData(long invRefNum, long inParID, pStr255 inName);

//----------------------------------------------------------------------
//	SNCallBack	sn_ExportBookmarks
//
//	Purpose:	The user can build a library of Internet Bookmarks. This
///				call lets you save them into an html file
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ExportBookmarks(long invRefNum, long inParID, pStr255 inName);

//----------------------------------------------------------------------
//	SNCallBack	sn_PrintDocument
//
//	Purpose:	Prints the passed doc, or the top doc if you pass in 
//				0 for the windowRef. If you want the print dialog to 
//				appear, then pass in true for inInteractive
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/03	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_PrintDocument(sn_WindowRef inWindowRef, pBoolean inInteractive);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetTopDocumentRef
//
//	Purpose:	returns the top most document reference, 
// 				could be NULL if no windows are open.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetTopDocumentRef(sn_WindowRef* outWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_QuitSN
//
//	Purpose:	Quits Starry Night. You may not get this call returning, 
//				depending on how things go. If you pass inInteractive as true, 
//				the documents will be saved, if the preferences for the 
//				user were to ask about saving documents at closing.
//
//				Pref	innteractive		result
//	Scenario 1) ask		false			all docs are automatically saved, (what about ones with no file?)
//	Scenario 2) noask	fasle			all docs closed without saving 
//	Scenario 3) ask		true			dialogs that ask you to save everything 
//	Scenario 4) noask	true			all docs closed without saving 
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_QuitSN(pBoolean inInteractive);

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Settings Menu
//
//	Purpose:	If you have a plugin that needs to get Starry Night 
// 				into a certain state, labels, colours, etc, then you run Starry Night
//				as a user would, set things up, save the options you want to use as a file.
//				Then use the Callback UseOtherSettings to get Starry Night to use 
//				the settings you have created. This saves Sienna from having to program
//				all of those settings dialogs so you can use them with CallBacks, and 
//				it allows you to set up your views the exact way you want using Starry 
//				Night.
//			
//				The only things that you can do in here are stuff that is not stored 
//				in the settings, such as orientation and flip.
//
//
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_SetOrientation
//
//	Purpose:	changes the orientation of the passed window.
// 				
//				inOrientation: 
//								kOrientationLocal      -- local 
//								kOrientationEquatorial -- equatorial 
//								kOrientationEcliptic   -- ecliptic 
//								kOrientationGalactic   -- galactic 
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetOrientation(sn_WindowRef inWindowRef, sn_Orientation inOrientation);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetFlip
//
//	Purpose:	changes the flip of the passed window.
// 				
//				inFlip: 
//								kFlipNone
//								kFlipHorizontal
//								kFlipVertical
//								kFlipBoth
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetFlip(sn_WindowRef inWindowRef, sn_Flip inFlip);

//----------------------------------------------------------------------
//	SNCallBack	sn_ToggleRedMode
//
//	Purpose:	Turns the screen red, so as not to blind users who are 
//				actually outside looking at stars.
// 				
//				inGoRed:  true means go red, fals means go back to normal
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ToggleRedMode(pBoolean inGoRed);

//----------------------------------------------------------------------
//	SNCallBack	sn_ToggleWhiteSkyMode
//
//	Purpose:	Turns the screen white, as with a star chart in a book.
// 				
//	Inputs:		inWindowRef:	The window to perform this action on.
//				inGoWhite:		true means go white (chart) mode, false means go back to normal
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		New for 4.5.
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ToggleWhiteSkyMode(sn_WindowRef inWindowRef, pBoolean inGoWhite);


//----------------------------------------------------------------------
//	SNCallBack	sn_UseFactoryDefaultPrefsAndOptions
//
//	Purpose:	Will reset all of the prefs to factory default.
//				If you do this, you might very well upset the user, 
//				since she might have spent a long time setting up the 
//				prefs/options to the way they like them.
//			
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_UseFactoryDefaultPrefsAndOptions(void);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetWindowSetting
//
//	Purpose:	determine the value of a window setting.
//				the values returned are text, and you will have to turn them into
//				numbers or whatever.  
//				
//	This is a very powerful call. To see examples of what you get here,
//  open up a Starry Night Pro file with a text editor. You can obtain the value of 
//  many settings in Starry Night this way.
//	
//	inWindowRef - the window
//	inLabel - the desriptor for the item
//  outValue - Starry Night will return the value here, always as a pascal string
//				
//			
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/04/22	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetWindowSetting(sn_WindowRef inWindowRef, pStr255 inLabel, pStr255 outValue);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetWindowSetting
//
//	Purpose:	set the value of a window setting.
//				the values we need are text, and you have to get the format right.
//				
//				
//	This is a very powerful call. To see examples of what you do here,
//  open up a Starry Night Pro file with a text editor. You can set the value of 
//  many settings in Starry Night this way.
//	
//	inWindowRef - the window
//	inLabel - the desriptor for the item
//  inValue - you need to pass a string that is formatted as in the Starry Night Pro file.
//
//	Example call: 
//	Here is al line from a Starry Night file:
//  <SN_VALUE name="Messier_ShowLabels" value="No">
//	You could turn messier labels on by calling 
//	sn_SetWindowSetting(windowRef, "Messier_ShowLabels", "Yes"); 
//  The " part of a string tells the compiler that these are pasca strings.
//	
//	As long as you pass in a valid window pointer, this call will return snNoErr.
//	You have no way of knowing if the value was actually taken in.
//	If you want to find out if the label you have is a valid one, then call sn_GetWindowSetting
//	
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/04/22	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetWindowSetting(sn_WindowRef inWindowRef, pStr255 inLabel, pStr255 inValue);


//----------------------------------------------------------------------
//	SNCallBack	sn_GetFOVIndicators
//
//	Purpose:	Retrieves a list of all FOV indicators with their properties according to
//				the PFov structure. The number of indicators retrieved is stored in outNum. 
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2005/may/16	MK			5.7		initial setup
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetFOVIndicators(PFov **outFOVs, int &outNum);


//----------------------------------------------------------------------
//	SNCallBack	sn_AddImageToImageLayer
//
//	Purpose:	Will add an image to the "User Images" layer. 
//				This allows CCD image plug-ins or other plugins to add images 
//				directly to the sky. 
//				
//				We need to be passed a picture, along with 
//				the coordinates of the centre, along with information on
//				how to align the picture in the sky.
//				Starry Night also needs the name of the image, 
//				and two optional lines of text describing the image,
//				the magnitude, the type of object.
//		
//				
//		Inputs
//		-------------------------
//		inPictureRef	        Starry Night assumes ownership of the passed picture.
//						        Mac- pass in a PicHandle
//						        Win32- pass in a HBITMAP, of the exact kind that you would pass to the clipboard
//
//		inCentreOfImageJ2000    the coordinates of the centre of the image, j2000 celestial ra dec.
// 
//		inWidthOfPictureRadians		pass in the width of the image in radians.
//		inHeightOfPictureRadians	pass in height in radians 
//
//		inPositionAngleRadians pass in the position angle, in radians, counter-clockwise positive from north
//		
//		inImageName            pass in the name of the object
//		inImageSource          pass in the source of the object, such as "\pSBIG CCD"
//		inNotes                pass in the notes, perhaps your plugin name
//		
//		inMagnitude            pass in the magnitude, or -999 if you don't know it
//		inDistanceLightYears   pass in the distance, or -999 if you don't know it
//		
//		inObjectType           pass in the object type as from the ObjectType chart defined in StarryNightPlugins.h
//		
//		inAutomaticBackGroundReduction	pass in true if you want SN to attempt to reduce the background of the image.
//
//		inOpenImageInEditor		pass true if you want to open the newly added image in the image editor		
//				
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
///	05/02/01	DWW			5.0.2		Updated for MaxImDL plugin 
//	99/04/22	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_AddImageToImageLayer(	pHandleToPicture inPictureRef, 
											PSphericalCoordinates inCentreOfImageJ2000, 
											double		inWidthOfPictureRadians,
											double		inHeightOfPictureRadians,
											double		inPositionAngleRadians,
											pStr255		inImageName,
											pStr255		inImageSource,
											pStr255		inNotes,
											double		inMagnitude,
											double		inDistanceLightYears,
											long		inObjectType,
											pBoolean	inAutomaticBackGroundReduction,
											pBoolean	inOpenImageInEditor);


//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Sky Menu
//
//	Purpose:	The sky menu is primarily used for turning on and off certain
//				'Layers' in Starry Night. The stars are considered one layer,
//				as are planets, galaxies, etc. 
//				
//				The other thing you can do is turn on the labels for any layer,
//				this is passed in as an option.
//
//				You can also find out if a layer is turned on.
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnLayerOnOff
//
//	Layers: 	Layers are Starry Night terminology for all of the sky elements that draw,
//				such as the Stars, Planets, On Screen Info, etc. 
//				They are called layers, since the sky is drawn starting at the most distant 
//				layers(guides), through to the MilkyWay, on to Nebulae, Stars, Planets
//				
//	Guide Layers. 	Since guide layers, (such as ecliptic, equatorial, etc) are 
//					not simply turned on or off, use TurnGuidesLayerOnOff, below
//					The onscreen info layer can be turned on and off with TurnLayerOnOff
//	
//	Purpose:	Turns the layer passed in the string on or off.
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inLayerName:  	pascal string that has the name of the layer, eg "Stars", "Planets", etc
//				inTurnLayerOn:  if true will turn the layer on
//				inShowLabels:  	if you also want the labels on, then pass in true.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/09	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnLayerOnOff(sn_WindowRef inWindowRef, pStr255 inLayerName, pBoolean inTurnLayerOn, pBoolean inShowLabels);

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnHorizonOnOff
//
//	Purpose:	Turns the horizon on or off
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inTurnOn:  		true if you want the horizon on.
//				inFeature:  	you can set which features of the horizon to show, setting also works with horizon off
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnHorizonOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn, sn_HorizonFeature inFeature);

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnDaylightOnOff
//
//	Purpose:	Turns the daylight on or off
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inTurnOn:  		true if you want the daylight on.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnDaylightOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn);

//----------------------------------------------------------------------
//	SNCallBack	sn_ShowHideLogEntryMarkers
//
//	Purpose:	Shows or hides the on screen log entry markers
//				If item has a log entry, this will mark it.
// 				
//	Inputs:		inTurnOn: true if you want the log markers to show.
//
//  Plugin API version: kVersion9Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		New for 4.5.
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ShowHideLogEntryMarkers(pBoolean inShowMarkers);

//#pragma mark-
//#pragma mark Guides Menu �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Guides Menu
//
//	Purpose:	The Guides menu is primarily used for turning on and off certain
//				'Guide Layers' in Starry Night. The stars are considered one layer,
//				as are planets, galaxies, etc. 
//
//				The 4 guides that draw grids in space are all accessed through one 
//				call. 
//
//				The onscreen info is accessed through one call.
//
//				The constellations are accessed through one call
//				
//				Right now to turn on a telrad indicator, the only interface is through the op_Draw 
//				call that Starry Night calls you with during scene drawing
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/04	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnGuidesLayerOnOff
//
//	Purpose:	Turns requested guide layer on or off.
// 				
//				inWindowRef:  	 window that you want to do this for, or 0 for the top one.
//				inGuideLayer:  	 one of kLocalGuidesLayer to  kEclipticGuidesLayer. The guides you are playng with
//				inGuideFeature:  one of kMeridian to  k3DAxes. The feature you want to turn on or off
//				inTurnOn:		 whether or not you want to turn the feature on or off
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnGuidesOnOff(sn_WindowRef inWindowRef, sn_GuideLayer inGuideLayer, sn_GuideLayerFeature inGuideFeature, pBoolean inTurnOn);

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnOnscreenInfoOnOff
//
//	Purpose:	Turns the onscreen info, with things like time and location on and off
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inTurnOn:  		true if you want the onscreen info on.
//				inFeature:		we offer the ability to turn on/off some features for the info
//				inFeatureOn		if you want the feature on. 
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnOnscreenInfoOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn, sn_OnScreenInfoFeature inFeature, pBoolean inFeatureOn);

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnConstellationsOnOff
//
//	Purpose:	Turns constellations on or off
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inTurnOn:  		true if you want the constellations on.
//				inFeature:		we offer the ability to turn on/off some features
//				inFeatureOn		if you want the feature on. 
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnConstellationsOnOff(sn_WindowRef inWindowRef, pBoolean inTurnOn, sn_ConstellationFeature inFeature, pBoolean inFeatureOn);

//----------------------------------------------------------------------
//	SNCallBack	sn_TurnFeetOnOff
//
//	Purpose:	Turns on or off the feet
//			
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/18	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TurnFeetOnOff(sn_WindowRef inWindowRef, pBoolean inFeetOn);

//#pragma mark-
//#pragma mark Go Menu �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Go Menu
//
//	Purpose:	The Go menu has two sections: 
//				The first section is for changing the location of the viewer or the location
//				of the home base of the computer. 
//				There is a call to set the location of the viewer, as well as a call to set the planet.
//			
//				The second section is a menu of places that you can go to. This menu is built 
//				up from a folder full of starry night files. When the user selects one of these
//				files, the file is opened, and the time is set to right now. 
//				We provide a call in here to open any member of the second section by passing in the
//				name of the menu item. 
//		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_GetViewerLocationInfo
//
//	Purpose:	Gets the location of the viewer to the passed lat and long
//				Does not change the planet or elevation. If the viewer is not on a planet, 
//				but rather in a stationary location, this changes the heliecliptic lat and long
//				of the observer. 
// 				
//				inWindowRef:  			window that you want to do this for, or 0 for the top one.
//				outLat:  				radians, between 90 and -90 deg
//				outLong:  				radians, between 180 and -180 deg
//				outElevationAu:			for planets: elevation from surface, in AU, for stationary locations, elevation in AU from Sun Centre 
//				outLocationType:		kPlanetLocation or  kStationaryLocation for now
//				outHovering:			if true, the user is hovering over a location
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetViewerLocationInfo(sn_WindowRef inWindowRef, double* outLat, double* outLong, double* outElevationAu, sn_LocationType* outLocationType, pBoolean* outHovering);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetViewerLocation
//
//	Purpose:	Sets the location of the viewer to the passed lat and long
//				Does not change the planet or elevation. If the viewer is not on a planet, 
//				but rather in a stationary location, this changes the heliecliptic lat and long
//				of the observer. 
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inLat:  		radians, between 90 and -90 deg
//				inLong:			radians, between 180 and -180 deg 
//				inElevationAu:  If you pass in zero you will locate to the centre of the earth:
//								to locate to the SN default elevation of 3m set the elevation to 3.0*kAuPerMetre, as elevation takes in Astronomical Units
//				const double_tsn	kMetrePerAu				=1.4959787066e11;			// number of metres per astronomical unit
//				const double_tsn	kAuPerMetre				=1.0/kMetrePerAu;			// number of astronomical unit per metres
//
//
//	The elevation is elevation above the ground. 
//	Starry Night really does not support the elevation of a location. 
//	(ie for being on the ground in Denver you would enter 0 as elevation)
//	The elevation is in astronomical units (AU)
//	You can pass in hover as true as long as you are over about 150? km. 
//	When hover is on, the earth will turn below you as time flows on, so that 
//	your surface location will change as time goes by.
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/15	DWW			4.5.0		Added timeZone info for 4.5.0
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetViewerLocation(sn_WindowRef inWindowRef, double inLat, double inLong, double inElevationAu, pBoolean inHovering);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetViewerPlanetName
//
//	Purpose:	Returns the name of the planet that the viewer is on. If not on a planet,
//				the string returned will be empty. 
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				outPlanetName:  the name of the planet, as long as snNoErr is the error
//				inLong:			radians, between 180 and -180 deg 
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetViewerPlanetName(sn_WindowRef inWindowRef, pStr255 outPlanetName);

//----------------------------------------------------------------------
//	SNCallBack	sn_GoHome
//
//	Purpose:	Returns the viwer to home base. AS if you pressed the 'home' button
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GoHome(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_GotoPlanetCenter
//
//	Purpose:	Puts the viewer in the center of planet location
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GotoPlanetCenter(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_GotoPlanet
//
//	Purpose:	Puts the viewer on another planet
// 				
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GotoPlanet(sn_WindowRef inWindowRef, pStr255 inNewPlanetName);

//----------------------------------------------------------------------
//	SNCallBack	sn_GotoFixedLocation
//
//	Purpose:	Puts the viewer at an XYZ location, 'at rest' at their current location
// 				
//				inWindowRef:  	window that you want to do this for, or kFrontWindow for top one.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GotoFixedLocation(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetViewerHelioEcliptic
//
//	Purpose:	returns the location of the viewer in au from the sun,
//				x,y,z as ecliptic coords. This means that z is almost 0 for anyone on Earth.
// 				
//				inWindowRef:  	window that you want to do this for, or kFrontWindow for top one.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetViewerHelioEcliptic(sn_WindowRef inWindowRef, PXYZCoordinates* outXYZHelioEcliptic);

//#pragma mark-
//#pragma mark Select Menu �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Select Menu
//
//	Purpose:	The Select menu: 
//				One of the nicest things you can do here is a find. If you pass in a string, and
//				the group you want to search through, then Starry Night will return those items matching 
//				your search criteria. .
//			
//				The goto option centres the screen on a passed point. 
//				
//		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_FindObject
//
//	Purpose:	Finds the requested object. Does not centre or otherwise move
//				the screen around, and so is invisible to the user, other than the
//				fact that a search can easily take muliple seconds.
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//									you need a window ref, since we return the objects position in the sky.
//
//				inObjectName: 		The name of the object you are searching for.
//
//				inLayerToSearch: 	The name of the layer you are searching in. To search
//									all layers, pass in the string "All".
//									You should try and narrow the search down as much as possible, since
//									that will speed things up.
//
//				outSelection: 		The info for the found object. If no object is found, This will return
//									the error code snErr_NoObjectFound.
//
//				inLockOnSelection: 	if you would like the screen centered on the selection, then pass in true.
//				inZoomLocked: 		if you want the found object zoomed in to.
//				inPanLocked: 		if you wanna pan.
//
//				inMakeSelection:	if you want to make the selection on the screen, but not centre it, then pass in this as true. 
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_FindObject(sn_WindowRef inWindowRef, pStr255 inObjectName, pStr255 inLayerToSearch, PSelection* outSelection, pBoolean inLockOnSelection, pBoolean inZoomLocked, pBoolean inPanLocked, pBoolean inMakeSelection);

//----------------------------------------------------------------------
//	SNCallBack	sn_FindObjectClosestTo
//
//	Purpose:	Finds an object closest to the coordinates specified (does not include constellation layer in its search).
//				Stars can be ignored in this search by specifying inIgnoreStellarObjects as true.
//				The search is 2D only so that the distance of the object from the observer is not taken into account.
//			
//				inWindowRef:  			window that you want to do this for, or kFrontWindow for top one.
//				
//				inCoordsJ2000:			coordinates in the sky around which to search
//
//				outSelection:			result of the search.
//
//				outDistance:			distance of the object from the coordinates given (in pixels).
//
//				inIgnoreStellarObjects:	set to true if you wish to ignore stars during search. set to false otherwise.
//
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	05/02/04	DWW			5.0.2		New for MaxIm DL plugin.
//
//----------------------------------------------------------------------
SNCallBack snErr sn_FindObjectClosestToCoords(	sn_WindowRef			inWindowRef,	
												PSphericalCoordinates	inCoordsJ2000, 
												PSelection*				outSelection,
												double_tsn*				outDistance,
												pBoolean				inIgnoreStellarObjects);


//----------------------------------------------------------------------
//	SNCallBack	sn_OpenLiveSkyLink
//
//	Purpose:	you send in a PSelection, and we send the user to the LiveSky link and open 
//				up info for you there
//			
//				
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_OpenLiveSkyLink(PSelection* inPSelection);


//----------------------------------------------------------------------
//	SNCallBack	sn_OpenURL
//
//	Purpose:	You pass in a URL, and Starry Night opens up a web browser 
//				and passes the URL over to it the browser for you.
//				Use this to open up the internet. You could for instance
//				use this to direct people to your own web site.
//				Or make up your own custom cgi to interact with the 
//				your own web server, etc.
//
//				If inEncodeUnsafeCharacters is true, then the URL is encoded as per
//				RFC 1630 to remove unsafe characters from the URL. A very common example 
//				of an unsafe character is a space, so that the URL www.surfer.com/lucky star.html
//				would be encoded to wwww.surfer.com/lucky%20star.html
//				Note that right now encoding only works for URLS less than 255 chars long.
//
//	
//				Requires verison 5 or later of the plugin API!
//				If you wish to run with version 4 clients, then don't call
//				this routine if the client passes in that it is a version 4 client
//				in op_Initialize.
//				
//
//
//  Plugin API version: kVersion5Plugin  *********
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	00/02/28	Tom			3.0.4		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_OpenURL(char* inURL, pBoolean inEncodeUnsafeCharacters);


//----------------------------------------------------------------------
//	SNCallBack	sn_GetPSelection
//
//	Purpose:	You send in a windowRef, and we send you back a PSelection
//				If there is no selection, or more than one, we send back snErr_NoSelection
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetPSelection(sn_WindowRef inWindowRef, PSelection* outPSelection);

//----------------------------------------------------------------------
//	SNCallBack	sn_CentreSelection
//
//	Purpose:	You send in a windowRef, if there is a selection in that window,
//				we centre on it.
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_CentreSelection(sn_WindowRef inWindowRef, pBoolean inPan, pBoolean inZoom, pBoolean inLockOnSelection);

//#pragma mark-
//#pragma mark Window Menu �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Window Menu
//
//	Purpose:	Here you learn how to show or hide windows such as document windows, 
//				floating windows, etc.
//				
//				You can also resize windows, go to full screen, hide all the floaters, 
//				whichis nice for doing a scripted demo.
//
//				Also you can cause an update to a window which forces a redraw of 
//				the window. This is nice, since many of the option setting calls
//				like turning on layers, etc, do not redraw the window.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_BringDocumentWindowToFront
//
//	Purpose:	You send in a windowRef, we try and move it to the top, so 
//				the user can se it.
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_BringDocumentWindowToFront(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_ImmediateUpdateWindow
//
//	Purpose:	Will draw the contents of the window. You may need to call this if you
//				are doing many changes to a window, and want the user to see the changes.
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ImmediateUpdateWindow(sn_WindowRef inWindowRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_FullScreenMode
//
//	Purpose:	Sets the full screen mode of Starry Night to the requested mode. 
//				You can pass in a window ref if you want.
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//				inMode:  			mode that you want to use.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_FullScreenMode(sn_WindowRef inWindowRef, sn_ScreenMode inMode);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetWindowSizeAndLocation
//
//	Purpose:	Returns the size and location of the passed window, in pixels
//				You get back two rectangles. One describes the whole thing 
//				the other the size of the content part of the window.
//			
//	Input:		inWindowRef:  						window that you want to do this for, or kFrontWindow for top one.
//	Output:		outContent, outEntireWindow			the location and size of the entire window, and the content, or scene
//													
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetWindowSizeAndLocation(sn_WindowRef inWindowRef, pRect* outContent, pRect* outEntireWindow);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetWindowContentRect
//
//	Purpose:	Sets the placement and size of the window to the passed rectangle
//			
//				inWindowRef:  		window that you want to do this for, or kFrontWindow for top one.
//				inNewRect:  		new window rect. 0,0 is the point at the upper left of the main monitor
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/11	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetWindowContentRect(sn_WindowRef inWindowRef, pRect inNewRect);

//----------------------------------------------------------------------
//	SNCallBack  ShowHideWindow
//
//	Purpose:	You can show or hide a starry night window.
//				You can use this after you create a window, in order for you
//				to have full control over it, without bothering the user 
//				with moving screens, etc. Useful for doing headless 
//				server-style plug-ins that do neat stuff.
//
//	Input:		inWindowRef: Pass in the window you want to hide along with 
//				inShow:	     Wether to show or hide it
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/17	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ShowHideWindow(sn_WindowRef inWindowRef, pBoolean inShow);

//----------------------------------------------------------------------
//	SNCallBack	sn_ScrollbarsOnOff
//
//	Purpose:	Turns scroll bars on or off for a window. You might want to turn them off if you
//				are in control of the screen.
//			
//				inWindowRef:  		window that you want to do this for, or 0 for the top one.
//				inShowScrollbars:  	if true, will show the scroll bars.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/12	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ScrollbarsOnOff(sn_WindowRef inWindowRef, pBoolean inShowScrollbars);

//----------------------------------------------------------------------
//	SNCallBack	sn_ShowHideToolbar
//
//	Purpose:	Will show or hide the toolbar
//			
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inShow:  		if true, will show the toolbar.
//
//
//  Plugin API version: kVersion9Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		New for 4.5.
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ShowHideToolbar(sn_WindowRef inWindowRef, pBoolean inShow);

//----------------------------------------------------------------------
//	SNCallBack	sn_ShowHideGraph
//
//	Purpose:	Will show or hide the grtaph (Pro Only)
//			
//				inWindowRef:  	window that you want to do this for, or 0 for the top one.
//				inShow:  		if true, will show the graphin tool (Pro only).
//
//
//  Plugin API version: kVersion9Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		New for 4.5.
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ShowHideGraph(sn_WindowRef inWindowRef, pBoolean inShow);

//----------------------------------------------------------------------
//	SNCallBack	sn_ShowHideControls
//
//	Replaces:	sn_ShowHidePalettes
//				sn_ShowHideTimePalette
//				sn_ShowHidePlanetPalette
//				sn_ShowHideTogglerPalette
//				
//
//	NOTE:		All of the above calls will still function, but will perform the
//				exact same action as sn_ShowHideControls.
//				 
//
//	Purpose:	Will show or hide all of the controls including the Toolbar.
//				If you want to hide only the toolbar, call sn_ShowHideToolbar
//				If you want to go to full screen mode (no window bar or menus) call sn_FullScreenMode
//			
//				inShowPalettes:  	if true, will show palletes the user currently has open
//									if false will hide them all.
//
//
//  Plugin API version: kVersion9Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/28	DWW			4.5.0		New for 4.5. Replaces several older calls.
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ShowHideAllControls(sn_WindowRef inWindowRef, pBoolean inShowAllControls);

// Replaces these... which will still function but simply call sn_ShowHideControls on the front window (kFrontWindow).
SNCallBack snErr sn_ShowHidePalettes(pBoolean inShow);
SNCallBack snErr sn_ShowHideTimePalette(pBoolean inShow);	
SNCallBack snErr sn_ShowHidePlanetPalette(pBoolean inShow);
SNCallBack snErr sn_ShowHideTogglerPalette(pBoolean inShow);


//----------------------------------------------------------------------
//	SNCallBack	sn_ShowHideHRDiagram
//
//	Purpose:	Will show or hide the HR diagram.
//				If you want a different set of options for the HR diagram, 
//				you must use an option set that you have saved. 
//			
//				inShow	:  		if true, will open
//								if false will hide.
//
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_ShowHideHRDiagram(pBoolean inShow);

//----------------------------------------------------------------------
//	SNCallBack	sn_GrabScreenshot
//
//	Purpose:	Will try to get a screen shot of the passed window, load
//				it into a new PicHandle (Mac) or HBITMAP (Win32) and hand the 
//				caller back the reference. The caller then owns the graphic, 
//				and must call the appropriate destruction mechanism for it.
//			
//				Mac: The pictHandle was made with a call to OpenPicture
//					 then copybits was used to fill it all in.
//				     Dispose with DisposeHandle(outPictureRef);  
//				
//				Win32: The bitmap will have been created by a call to CreateCompatibleBitmap(),
//				and a call to SetDIBits().
//				Use DeleteObject(outPictureRef) to delete it.
//			
//				inShow	:  		if true, will open
//								if false will hide.
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GrabScreenshot(sn_WindowRef inWindowRef, pHandleToPicture* outPictureRef);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetWindowList
//
//	Purpose:	Returns a list of sn_WindowRefs to the caller. The caller must supply 
//				the space for the refs.
//				To find out a cout of windows call as:
//				long windowCount;
//				snErr = sn_GetWindowList(NULL, 0, &windowCount);
//
//				To get a list of windows call as:
//				sn_WindowRef windowRefs[20];
//				snErr = sn_GetWindowList(windowRefs, 20, &windowCount);
//			
//  Plugin API version: kVersion6Plugin
//
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	00/07/22	Tom			3.1.0		Requested
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetWindowList(sn_WindowRef* ioWindowRefs, long inMaxNumberWindows,  long* outNumWindows);

//#pragma mark-
//#pragma mark Time Window �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Time Window
//
//	Purpose:	Here you gain control over the time in a Starry Night window.
//				you can set the time step, turn time flow on, 
//				translate times from one format to another, get/set the time
//				for any window, etc
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_GetCurrentTime()
//
//	Purpose:	Will return the time in julian date as a double
//				
//	Input:		The window you want the julian date for.
//	output:		This is Universal Time, or UT.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetCurrentTime(sn_WindowRef inWindowRef, double* outJulianDate);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetDeltaT()
//
//	Purpose:	Will return the value of delta T, in days that the Starry Night
//				is using for the passed window
//				
//	Input:		The window you want the julian date for.
//	output:		Delta T, in days. delta_T = TDT - UT
//				So to get the dynamic, or ephemeris time, just do the addition
//				TDT = UT + delta_T
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetDeltaT(sn_WindowRef inWindowRef, double* outDeltaT);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetTimeZoneSeconds()
//
//	Purpose:	Will return the time zone amount in seconds
//				There are 3600 seconds in an hour 
//				
//	Input:		The window you want the time zone of.
//	output:		outTimeZoneOffset: in seconds, unadjusted for DST
//				outDSTinUse:       if true then daylight savings time is in use, (3600 secs)
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetTimeZoneSeconds(sn_WindowRef inWindowRef, long* outTimeZoneOffset, pBoolean* outDSTinUse);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetTimeZoneSeconds()
//
//	Purpose:	Will set the time zone amount in seconds
//				There are 3600 seconds in an hour.
//				This should be -ve for westerly longitudes (e.g. Toronto = -5.0*(3600))
//				
//	Input:		The window you want the time zone of.
//				inTimeZoneOffsetSeconds: in seconds, unadjusted for DST
//
//  Plugin API version: kVersion9Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/05/15	DWW			4.5.0		New for 4.5
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetTimeZoneSeconds(sn_WindowRef inWindowRef, long inTimeZoneOffsetSeconds);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetCurrentTime()
//
//	Purpose:	Set the UT to the passed time for the window
//				
//	Input:		The window you want the julian date for.
//	intput:		The julian time, UT in days
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetCurrentTime(sn_WindowRef inWindowRef, double inJulianDate);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetTimeStep()
//
//	Purpose:	Set the time step in days for the passed window
//				
//	Input:		The window you want the julian date for.
//	intput:		the time step in days
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetTimeStep(sn_WindowRef inWindowRef, double inTimeStepDays);

//----------------------------------------------------------------------
//	SNCallBack	sn_TimeFlowOneStep()
//
//	Purpose:	Take one step in time. 
//				
//	Input:		The window you want the julian date for.
//	intput:		inStepForwards:  if true then will go forward 
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_TimeFlowOneStep(sn_WindowRef inWindowRef, pBoolean inStepForwards);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetTimeFlowState()
//
//	Purpose:	Turns time flow on/off, real time, stop, etc
//				
//	Input:		The window you want the julian date for.
//	intput:		inFlowForwards:  if true then will go forward 
//	
//	Note:		This turns time flow on/off, but no steps are taken until you release Starry 
//				Night by returning from your op_idle call. 
//				Set up a loop around calls to TimeFlowOneStep() in order to 
//				control Starry Night more directly
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetTimeFlowState(sn_WindowRef inWindowRef, sn_TimeFlowState inFlowState);

//----------------------------------------------------------------------
//	SNCallBack	sn_Julian2CivilTime()
//
//	Purpose:	Converts a passed Julian date to the civil time equivalent.
//				
//				
//	Input:		The window you want the julian date for.
//	intput:		inFlowForwards:  if true then will go forward 
//	
//	Outputs:	outCivilDate	returns the civil calendar date (for the calendar in use at the time).
//								The Gregorian calendar is used for dates after October 4, 1582 with all other
//								dates being returned using the Julian calendar. This means that the dates
//								from October 5, 1582 through October 14, 1582 (inclusive) will never be
//								returned.
//
//				Note that since this function takes no window ref, it assumes no timeZone, ie: a time zone of 0.
//				to take time zone into account, you can add the time zone before caling this, saving youself messy 
//				stuff.
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_Julian2CivilTime(double inJulianUT, long* outYear, long* outMonth, long* outDay, long* outHour, long* outMinute, long* outSecond);

//----------------------------------------------------------------------
//	SNCallBack	sn_Civil2JulianTime()
//
//	Purpose:	Converts a passed Civil date to the Julian equivalent.
//				
//				
//	Input:		The window you want the julian date for.
//	intput:		inFlowForwards:  if true then will go forward 
//	
//	Outputs:	outJulianUT		Given the passed date, will return the 
//								julian equivalent. This will be the correct UT if you pass in time in greenwich.
//	
//				Note that since this function takes no window ref, it assumes no timeZone, ie: a time zone of 0.
//				to take time zone into account, you can add the time zone after caling this, saving youself messy 
//				stuff.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_Civil2JulianTime(double* outJulianUT, long inYear, long inMonth, long inDay, long inHour, long inMinute, long inSecond);

//#pragma mark-
//#pragma mark Telescope Panel �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack   Coordinate Conversion Utilities
//
//	Purpose:	These utilities allow you to control aspects of the telescope
//				panel.
//				
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	02/03/03	DWW			4.0.0		New for Pro X
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_SetPluginStatusText()
//
//	Purpose:	Sets the status text for the plugin.
//				
//	Input:		inMessageString		As with an error alert, we use a "message" (brief) and an "informative" (longer) string
//									that describes the problem and a possible solution.
//				inInformativeString	See above. Should not exceed 256 characters.
//				inRA				The current Right Ascension of the telescope.
//									(In radians). Input the constant "coordinate_NotAvailable" to display "N/A" in SN "Telescope" tab
//				inDec				The current Declination of the telescope. (In radians). Also see above.
//
//	NOTE:		You can set the RA and Dec strings in the telescope panel to "N/A" by passing coordinate_NotAvailable into inRA and inDec
//				Also note that it is the responsibility of the plugin to keep this current. If Starry Night does not detect a plugin
//				in the Plug-ins folder, these strings will be set to "No Plug-in Detected" and will be set to "Configure Telescope" if 
//				a plugin is detected. After that, it is the complete responsibility of the plugin to maintain this.
//				
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	02/03/03	DWW			4.0.0		New for Pro X
//----------------------------------------------------------------------
const double coordinate_NotAvailable = -9999.0;

SNCallBack snErr sn_SetPluginStatusText(pStr255 inMessageString, pStr255 inInformativeString, double inRA, double inDec);


//----------------------------------------------------------------------
//	SNCallBack	sn_GetCurrentDisplayedCoordinates()
//
//	Purpose:	Gets coordinates displayed in the Telescope Panel
//	
//	Output:		Outputs RA/Dec through the variables passed.
//				returns coordinate_NotAvailable if they cannot be retrieved			
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	05/04/05	MK			5.0.3		New for plugin communication
//----------------------------------------------------------------------
SNCallBack snErr sn_GetCurrentDisplayedCoordinates(double &outRightAscension, double &outDeclination);


//----------------------------------------------------------------------
//	SNCallBack	sn_GetAreCoordinatesWithinUserSlewLimits()
//
//	Purpose:	Determines if the passed PGaze coordinates are within the user defined slew limits. If no limits are set, returs true.
//				
//	Input:		inCoordinateToCheck	A PGaze including at least an Altitude and Azimuth to check against user preferences.
//
//				outAreWithinLimits	Returns with the resut. True if PGaze is within the limits (or the user has overridden settings, false otherwise.
//
//	NOTE:		You must pass either a correct Ra / Dec or Alt / Az and set the other pair to
//				coordinate_NotAvailable each, or pass correct values for both Ra/Dec AND Alt/Az
//				
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2004/12/07	DWW			5.0.2		New for advanced telescope control
//----------------------------------------------------------------------
SNCallBack snErr sn_GetAreCoordinatesWithinUserSlewLimits(PGaze inCoordinateToCheck, pBoolean inShowOverrideDialog, pBoolean* outAreWithinLimits);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetMaxMinSlewAltitude()
//	SNCallBack	sn_GetMaxMinSlewDeclination()
//
//	Purpose:	Returns the Maximum and Minimum slew altitudes and declinations as set by the user, if any
//				
//
//	NOTE:		Values will be set to "coordinate_NotAvailable" if the user has not set any preferences for these values.
//				
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2004/12/07	DWW			5.0.2		New for advanced telescope control
//----------------------------------------------------------------------
SNCallBack snErr sn_GetMaxMinSlewAltitude(pBoolean* outUserWantsAltLimits, double* outMinAltitude, double* outMaxAltitude);
SNCallBack snErr sn_GetMaxMinSlewDeclination(pBoolean* outUserWantsDecLimits, double* outMinDeclination, double* outMaxDeclination);


//----------------------------------------------------------------------
//	SNCallBack	sn_RefreshTelescopePanel()
//
//	Purpose:	Forces the Telescope Panel to be refreshed
//				
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2005-Apr-04 DWW and MK	5.0.3		Used to refresh telescope panel buttons from within the plugin
//----------------------------------------------------------------------
SNCallBack snErr sn_RefreshTelescopePanel(void);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetFocuserTempInfo()
//
//	Purpose:	Sends current focuser temperature to SN for display in the UI
//				
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2005-Aug-05	DWW, MK		5.7			Used to display current focuser temperature
//----------------------------------------------------------------------
SNCallBack snErr sn_SetFocuserTempInfo(double inTempInDegrees);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetFocuserPositionInfo()
//
//	Purpose:	Sends current focuser position to SN for display in the UI
//				
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2005-Aug-30	DWW, MK		5.7			Used to display current focuser position
//----------------------------------------------------------------------
SNCallBack snErr sn_SetFocuserPositionInfo(long inFocuserPosition);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetFocuserProperties()
//
//	Purpose:	Sends current focuser properties to SN.
//
//	Inputs:		inLowerStepBoundary:	lowest position setting available for the focuser
//
//				inUpperStepBoundary:	highest position setting available for the focuser
//
//				inMaxStepIncrement:		maximum increment for a single step of the focuser
//				
//  Plugin API version: kVersion10Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	2005-Aug-05	DWW, MK		5.7			Used to display current range of the focuser
//----------------------------------------------------------------------
SNCallBack snErr sn_SetFocuserProperties(	long inLowerStepBoundary,
											long inUpperStepBoundary,
											long inMaxStepIncrement);

//#pragma mark-
//#pragma mark Coordinate Conversion Utilities �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Coordinate Conversion Utilities
//
//	Purpose:	These utiliies allow you to convert between screen and ra, dec coords,
//				between alt az and ra dec, etc. 
//				You can use this to draw in the screen, or to calculate alt az
//				coords when all you have is ra dec, etc. 
//				
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/10	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_CoordinateConversion()
//
//	Purpose:	Converts one coordinate system into another
//				
//	Input:		inWindowRef: You need a window ref, since coordinate conversions depend on the time, etc		
//				You need to pass in the source coord system, the destination coord system, and the 
//				source coords. We fill in outToCoords;
//				
// 				// you can transform between any two of these systems
//				kSNNoCoordinateSystem // never used
//				kSNAltAzSystem
//				kSNGalacticSystem
//				kSNEclipticSystem
//				kSNCelestialJ2000System
//				kSNCelestialJNowSystem
//				kSNOrientationSystem -----the coordinate system of the passed window. 
//										  For windows in the default orientation, 
//                	                      this is the same as kSNAltAzSystem
//
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_CoordinateConversion(sn_WindowRef inWindowRef, long inFromCoordSystem, long inToCoordSystem, PXYZCoordinates inFromCoords, PXYZCoordinates* outToCoords);

//----------------------------------------------------------------------
//	SNCallBack	sn_XYZToSpherical()
//
//	Purpose:	converts from XYZ coords to spherical equivalent
//				
//				
//	Input:		You pass in 
// 
//	Note:		The definition of Azimuth is such that it is backwards from ra. We return the 
//				ra style of coords. If the coords you are passing are alt az, you will need
//				to convert the returned coords ra with 
//				Mathematical2RealWorldAzimuth, which is (kTwicePi - mathematicalAz)		
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_XYZToSpherical(PXYZCoordinates inCoords, PSphericalCoordinates* outSameCoords);

//----------------------------------------------------------------------
//	SNCallBack	sn_SphericalToXYZ()
//
//	Purpose:	converts from  spherical to XYZ toequivalent
//				
//				
//	Input:		You pass in spherical (with azimuth in mathematical mode as below)
// 
//	Note:		The definition of Azimuth is such that it is backwards from ra. We need the 
//				ra style of coords. If the coords you are passing are alt az, you will need
//				to convert the returned coords ra with 
//				Mathematical2RealWorldAzimuth, which is (kTwicePi - mathematicalAz)		
//				
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SphericalToXYZ(PSphericalCoordinates inCoords, PXYZCoordinates* outEquivalentCoords);

//----------------------------------------------------------------------
//	SNCallBack	sn_Mathematical2RealWorldAzimuth()
//	SNCallBack	sn_RealWorldAzimuth2Mathematical()
//
//	Purpose:	For astronomers azimuth increases clockwise as looking down at the Earth.
//				Starry Night refers to this type of azimuth as "Real World" azimuth. Starry
//				Night also uses an internal representation of azimuth that is the opposite.
//				We call Starry Night's azimuth the "Mathematical" azimuth. You can convert
//				between the two representations of azimuth using this formula:
//
//					mathematical = 2*pi - realWorld
//					realWorld = 2*pi - mathematical
//
//				Or you can call these routines. Check comments for the structures passed
//				to determine whether the azimuth is real world or mathematical. (For example
//				PGaze uses real world coordinates).
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/16	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_Mathematical2RealWorldAzimuth(double inMathematicalAz, double* outRealAz);
SNCallBack snErr sn_RealWorldAzimuth2Mathematical(double inRealWorldAz, double* outMathematicalAz);

//----------------------------------------------------------------------
//	SNCallBack	sn_XYZToWindowPoint()
//
//	Purpose:	you give us a point, we tell you where on the window that is
//				used for, say doing drawing on the screen. You pass in an alt az, we tell you 
//				where on the window that is.
//				
//	Input:		inWindowRef:	 the window you want the point for
//				inCoordSystem:	 the coord system of the input xyz point
//				inCoords:		 the coordinates of the point. We expect this point to be normalized, that is
//									the length (radius) is 1.
//	
//	Output:		outH, outV, 	 the equivalent window points. These points could be anywhere,
//								 even very, very far away from the centre of the window. The caller
//								is responsible for figuring out to do with what comes back. Don't draw something
//								unless it has a chance of making it on the window. 
//								We use double precision, since the routine calculates positions to the nearst 1/256 th of a pixel
//				outFront:		If this comes back true, the window point returned is in front of the viewer, and can be drawn.
//								If it returns as false, then the point is behind the viewer, don't draw!
//
//		
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/17	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_XYZToWindowPoint(sn_WindowRef inWindowRef, long inCoordSystem, PXYZCoordinates inCoords, double* outH, double* outV, pBoolean* outFront);


//----------------------------------------------------------------------
//	SNCallBack	sn_PlotStar()
//
//	Purpose:	Will plot a star in the current window. The 
//				
//	Input:		inWindowRef:	 the window you are drawing into, which must be the same as given to you by a op_DrawLayer call
//				inH, inV:	 	 the coordinates of the Star you want to plot, obtained from say sn_XYZToWindowPoint
//				inMag:		 	 the magnitude of the star you wish to plot (from -2 to say 25)
//				inBMinusV:		 the colour index of the star you wish to plot. (from -0.5 blue to 3 red), pass in 0.5 for a white star
//	
//	This call can only be called from op_DrawLayer, where you are passed a 
//		
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/05/05	Tom			3.0.0		Pro
//
//----------------------------------------------------------------------
SNCallBack snErr sn_PlotStar(sn_WindowRef inWindowRef, double inH, double inV, double inMag, double inBMinusV);

//----------------------------------------------------------------------
//	SNCallBack	sn_WindowPointToXYZ()
//
//	Purpose:	Given a window point, we return the equivalent position on the coord sphere.
//				you can use this for whatever you like.
//				
//	Input:		inWindowRef:	 the window you want the point for
//				inCoordSystem:	 the coord system of the output xyz point
//				inH, 	 inV:	 the h and v of as measured from top left of the window of the window point. 
//				
//
//	Ouput:		outCoords:		 The coordinates of the point. will be normalized, that is
//				outWorked:		 If returned true, then that means that there was a point found. For example,
//								 if the viewer is looking at a 180 deg picture of the sky, many points on the window have 
//								no equivalent coordinates on the celestial sphere.			
//
//	Note:		currently this routine only works for inputs up to SHRT_MAX, and does not pay attention to sub pixels
//				so that 34.87, 78.21 is taken as 34, 78. This could change in the future.
//
//  Plugin API version: kVersion4Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/17	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_WindowPointToXYZ(sn_WindowRef inWindowRef, double inH, double inV, long inCoordSystem, PXYZCoordinates* outCoords, pBoolean* outWorked);

//----------------------------------------------------------------------
//	SNCallBack	sn_CentreWindowAtCoords
//
//	Purpose:	Centres the window on the requested coords. You can make an animation like panning and zooming
//			
//				inWindowRef:  		window that you want to do this for, or kFrontWindow for top one.
//
//				inCoordSystem: 		The coordinate system that the coordinates are in
//				inCoords: 			The location you want to zoom in on, XYZ 
//
//				inPan	: 			if you wanna pan.
//				inZoom	: 			if you want to zoom.
//				inZoomToField 		the field of view that you desire, in radians.
//
//				inLockToRaDec: 		if you want to lock on the passed ra dec. if you don't the view will just go to that 
//								direction, and as time passes, the ra dec may float out of the window.
//									if you want to lock to the alt-az then don't lock the gaze will not change.
//				
//		Note on Pan and Zoom.
//
//				Pan				Zoom
//             -----           ------
//				true			true		then there will be the panning and zooming effect.
//				true			false		then there will be the panning effect. inFieldOfView is ignored
//				false			true		no zoom effect, the will just go in one step to the desired zoom.
//				false			false		no pan no zoom, inFieldOfView is ignored.
//		
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/18	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_CentreWindowAtCoords(sn_WindowRef inWindowRef, long inCoordSystem, PXYZCoordinates inCoords, pBoolean inPan, pBoolean inZoom, double inFieldOfView, pBoolean inLockToRaDec);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetWindowCentreCoords
//
//	Purpose:	Returns the coordinates of the centre of the window in any system you like
//			
//				inWindowRef:  		window that you want to do this for, or kFrontWindow for top one.
//
//				inCoordSystem: 		The coord system you want the coordinates returned in
//
//				outCoords: 			pointer to the structure to recieve the coords
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/18	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetWindowCentreCoords(sn_WindowRef inWindowRef, long inCoordSystem, PXYZCoordinates* outCoords);

//----------------------------------------------------------------------
//	SNCallBack	sn_GetFieldOfView
//
//	Purpose:	Gets the zoom state to the field you pass in
//			
//				inWindowRef:  		window that you want to do this for, or kFrontWindow for top one.
//
//				outFieldRadians: 			the field, right ot left in radians
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/18	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_GetFieldOfView(sn_WindowRef inWindowRef, double* outFieldRadians);

//----------------------------------------------------------------------
//	SNCallBack	sn_SetFieldOfView
//
//	Purpose:	Sets the zoom state to the field you pass in
//			
//				inWindowRef:  		window that you want to do this for, or kFrontWindow for top one.
//
//				inFieldRadianss: 	the horizontal field you desire
//
//				outCoords: 			pointer to the structure to recieve the coords
//
//  Plugin API version: kVersion4Plugin
//
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	99/02/18	Tom			3.0.0		Bullard
//
//----------------------------------------------------------------------
SNCallBack snErr sn_SetFieldOfView(sn_WindowRef inWindowRef, double inFieldRadians);

//#pragma mark-
//#pragma mark Drawing Utilities �
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//	SNCallBack	Drawing Utilities
//
//	Purpose:	These utiliies allow you to draw lines and text in SN//				
//				
//
//  Plugin API version: kVersion9Plugin
//					
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/06/02	DWW			4.5.0		New drawing utils for SN
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	SNCallBack	sn_RaDecLineTo()
//
//	Purpose:	Draws a line in starry night from inFrom coords to inTo coords. JNow.
//				
//	Input:		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/02/06	DWW			4.5.0		New for version 4 Plugin SDK
//
//----------------------------------------------------------------------
SNCallBack snErr sn_RaDecLineTo(sn_WindowRef inWindowRef,
								double	inFromRa,
								double	inFromDec,
								double	inToRa,
								double	inToDec,
								float	inRed,
								float	inGreen,
								float	inBlue,
								float	inThickness,
								unsigned short inStipple);

//----------------------------------------------------------------------
//	SNCallBack	sn_XYZLineTo()
//
//	Purpose:	Draws a line in starry night from inFrom XYZ coords to inTo XYZ coords.
//				
//	Input:		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/02/06	DWW			4.5.0		New for version 4 Plugin SDK
//
//----------------------------------------------------------------------
SNCallBack snErr sn_XYZLineTo(	sn_WindowRef inWindowRef,
								PXYZCoordinates* inFrom,
								PXYZCoordinates* inTo,
								float	inRed,
								float	inGreen,
								float	inBlue,
								float	inThickness,
								unsigned short inStipple);

//----------------------------------------------------------------------
//	SNCallBack	sn_LineTo()
//
//	Purpose:	Draws a line in starry night from inFrom coodes to inTo screen coords.
//				
//	Input:		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/02/06	DWW			4.5.0		New for version 4 Plugin SDK
//
//----------------------------------------------------------------------
SNCallBack snErr sn_LineTo(	float inFromHorz,
							float inFromVert,
							float inToHorz,
							float inToVert,
							float inRed,
							float inGreen,
							float inBlue,
							float inThickness,
							unsigned short inStipple);

//----------------------------------------------------------------------
//	SNCallBack	sn_MoveTo()
//
//	Purpose:	does a move to in the current drawing environment
//				
//	Input:		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/02/06	DWW			4.5.0		New for version 4 Plugin SDK
//
//----------------------------------------------------------------------
SNCallBack snErr sn_MoveTo(double inH, double inV);


//----------------------------------------------------------------------
//	SNCallBack	sn_DrawString()
//
//	Purpose:	Draws the passed text at the passed location 
//				
//	Input:		
//				
//	Date		Initials	Version		Comments
//  ----------	---------	----------	---------------------------
//	03/02/06	DWW			4.5.0		New for version 4 Plugin SDK
//
//----------------------------------------------------------------------
SNCallBack snErr sn_DrawString(	float	inH,
								float	inV,
								char*	inTextString,
								float	inRed,
								float	inGreen,
								float	inBlue,
								long	inFontSize,
								sn_FontStyle inFontStyle,
								char*	inFontName,
								float	inAngle);
								
} // end 'C' function definitions
