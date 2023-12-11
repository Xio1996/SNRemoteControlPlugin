// RemoteControl
// Starry Night Plugin - Remote Control
//
// A plugin for the astronomy application Starry Night.The plugin allows object view synchronisation between external apps such as AstroPlanner and Starry Night.The remote control plugin for Starry Night 8, was based on the ASCOM Focuser example in the Starry Night plugin SDK.Developed and tested on Windows 11 and Starry Night Pro 8.1.0.2049
// Unlike many astronomy applications(such as Stellarium, AstroPlanner, CdC and TheSky etc) Starry Night 8 Pro does not have any way of allowing external apps to control its features.Such as finding and selecting objects by name or position, setting the field of view etc.However, Starry Night 8 does publish a Plugin SDK.This project is an experiment in writing a plugin that could integrate Starry Night Pro 8 into my EAA workflow.
// The code is not robust and not well written but if you have a similar requirement, then it might be a help(hopefully not a hinderance) in developing your own Starry Night Plugin.Have fun!
//
// Overview.
// Communication with the plugin is via a text file.The plugin waits until the file exists and then processes the command content.The file has a single line of bar(| ) separated parameters e.g.target | Polaris | 2.530195 | 89.26417 | 10 The first parameter is the lowercase command.It is a very simple communication method and allows easy access to the plugins features.
//
// Commands
// target Command : Will move Starry Night to the specified object ID or if not found to the RA / DEC(J2000) location and change the FOV(0 FOV, keep current FOV)
//
// target | ID | RA | Dec | FOV
//
// ID = The Starry Night object we wanto to move to.
// RA = Decimal Hours(J2000)
// Dec = Degrees(J2000)
// FOV = Degrees
// E.g.target | M13 | 16.69478 | 36.4598 | 5
//
// altaz Command : Moves to the specified Alt / Az location and sets the FOV(0 FOV, keeps the current FOV)
//
// altaz | Alt | Az | FOV
//
// Alt = Degrees
// Az = Degrees
// FOV = Degrees
// E.g.altaz | 45 | 180 | 107
//
// fov Command : changes SN's FOV (in degrees). The centre position is unchanged and a FOV of 0 is ignored.
//
// fov | FOV
//
// FOV = degrees
// E.g.fov | 110
//
// The following 'get' commands will write their output to the 'snrout.txt' file in the same directory as specified for the 'snmsg.txt' file.
//
// getselobj Command : This returns information on the currently selected object.If no object is selected the message NOSELECTION is returned.
//
// Object Name | Object Type | RA(J2000) | Dec(J2000) | RA(JNOW) | Dec(JNOW) | Alt | Az | Magnitude | Size
//
// Object Name = The SN name for the current object.
// Object Type = The SN object type.
// RA(J2000) = J2000 coordinates in decimal hours(13h 30m = 13.5).
// Dec(J2000) = J2000 coordinates in degrees.
// RA(JNOW) = JNOW coordinates in degrees.
// Dec(JNOW) = JNOW coordinates in degrees.
// Alt = Local altitude in degrees.
// Az = Local azimuth in degrees.
// Magnitude = The magnitude(if any) of object.
// Size = The size of an object in degrees.If none then 0 is returned.
//
// E.g.Polaris | Star with Exoplanet | 2.530292 | 89.264111 | 3.033089 | 89.364666 | 50.069680 | 0.096951 | 1.960000 | 0.000000
//
// getviewerloc Command : Returns the location of the observer in either planet lattitude / longitude or heliocentric coordinates.
//
// Planet | Lattitude | Longitude | Altitude | Coordinate System | Hovering
//
// Planet = The current planet or 'Helio' if using heliocentric coordinates.
// Lattitude = Latitiude on planet or heliocentric coordinate in degrees.Longitude = Longitude on planet or heliocentric coordiante in degrees.Altitude = The altitude in astronomical units from the planets surface.Coordinate System = 901 Planetary, 902 Stationary location(heliocentric) Hovering = 0 not hovering(follows object rotation) or 1 hovering
//
// Earth | 51.204000 | -1.630000 | 0.000000 | 901 | 0
//
// getfov Command : Returns the current field of view in degrees.
//
// fov
//
// fov = The current field of view in degrees.
//
// 110.00000
//
// getcentrecoords Command : Returns the centre position of the view in x, y, z coordinates(radians) for the views current coordinate system(Options->Orientation menu item).
//
// x | y | z
//
// x = x coordiante in radians.
// y = y coordinate in radians.
// z = z coordinate in radians.
// E.g. - 0.698544 | 0.147982 | 0.700098
//
// gettime Command : Returns the Julian time in univeral time(UT).
//
// JulianTime
//
// JulianTime = UT Julian Time
//
// 2460289.947557
//
// INSTALLATION
//
// Place the "RemoteControl_Win32.plug" (plugin) and the "RemoteControl_Win32.ini" (configuration)files into the Starry Night plugins folder.The plugins("Plug-ins") folder resides in the Starry Night installation folder.Something like "C:\Program Files (x86)\Starry Night Pro 8\Sky Data\Plug-ins".
//
// Edit the "RemoteControl_Win32.ini" file in a text editor.Provide the full path and filename to the file used to communicate with the plugin.Something like "C:\StarryNightMsg\snmsg.txt".Choose a location that allows you and Starry Night to read / write and delete the file.
//
// ABOUT Dialog(Checking Installation)
//
// When Starry Night is running click on the Help->About Plug - in->Remote Control menu entry to bring up the About dialog.The dialog checks that the settings file is present and displays the filepath read from the file.The plugin then checks that it has the permissions to write and delete the file.
//
// If the Remote Control entry is missing from the 'About Plug-in' menu then Starry Night did not recognise this plugin!Review the installation instructions.If you develop your own plugin then make sure the plugin filename ends "_Win32.plug"
//
// Remote Control Plugin Client
//
// To test the plugin there is a Windows desktop app to exercise the plugin's commands. It allows pre-defined commands and parameters to be sent to the Remote Control Plugin or user defined. It is included here for completness and is not required to use the remote control plugin.
//
// AstroPlanner Script
//
// A simple AstroPlanner script that synchronises the selected object in AstroPlanner with the selected object or position in Starry Night.
//
// TODO
//
// A better "real-world" solution would be to communicate with the plugin via a TCP port or http call as is done in other astronomy applications.
//
// This is a "happy days" implementation and needs hardening against failure and correcting the wrongs against coding!
//==================================================================================================

#include "RemoteControl.h"
#include "resource.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <shlobj_core.h>
#include <fileapi.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

// Globals
HINSTANCE _hInst;						// Our DLL module handle
HINSTANCE _hProc;						// Handle to Starry Night process that loaded us
HWND _hWndMain;							// Our main window handle

// Title of the About dialog
std::string _sAlertTitle ("Remote Control Plugin v0.1");

// We store the plugin settings file, that contains the filepath to monitor for any commands, in the same directory we place Starry Night plugins.
// Releative path to plugins folder in the Starry Night installation directory from the top-level .exe folder.
std::string _sSettingsPath = ".//Sky Data//Plug-ins//RemoteControl_Win32.ini";

// Filename and path to the command file used to communicate with the plugin.
std::string _sCommandFile = "";

// Filename and path to the file used for output from plugin calls.
std::string _sOutFile = "";

// Helper function to read the command file
static std::string read_file(const std::string& path)
{
	std::ifstream file(path);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return content;
}

static bool write_file(const std::string& path, const std::string& content)
{
	bool bRes = false;
	try
	{
		std::ofstream file(path);
		if (file)
		{
			file << content;
			file.close();
			bRes = true;
		}
	}
	catch (...) {}
	return bRes;
}

// Helper function to split the command string into a vector
static std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

// Helper function to show error dialog
static void ShowErrorDialog(char* msg)
{
	MessageBox(NULL, msg, _sAlertTitle.c_str(), (MB_OK & MB_ICONWARNING | MB_SETFOREGROUND));
}

// MAIN ENTRY
BOOL WINAPI DllMain(HMODULE hMod, DWORD fReason, LPVOID pvRes)
{
	switch (fReason) 
	{
		case DLL_PROCESS_ATTACH:
			_hInst = (HINSTANCE)hMod;			// Needed for various things
			_hProc = (HINSTANCE)GetModuleHandle(NULL);
			DisableThreadLibraryCalls(hMod);	// No thread att/det calls
			break;

		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

bool SettingsFileExists()
{
	return PathFileExists(_sSettingsPath.c_str());
}

bool ReadSettings()
{
	bool bResult = false;
	if (SettingsFileExists())
	{
		std::string sCmdFilepath = read_file(_sSettingsPath);
		if (!sCmdFilepath.empty())
		{
			std::string sPath = sCmdFilepath.substr(0,sCmdFilepath.find_last_of("\\")+1);

			_sOutFile = sPath + "snrcout.txt";

			// File to monitor for commands
			_sCommandFile = sCmdFilepath;
			bResult = true;
		}
	}

	return bResult;
}

bool TestCmdFile()
{
	bool bResult = false;
	try
	{
		std::ofstream(_sCommandFile, std::ios::out);
		bResult = DeleteFile(_sCommandFile.c_str());
	}
	catch (...)
	{
	}

	return bResult;
}

// Initialise the plugin
static short initPlugin(PInitialize* p)
{
	p->fSuccess			= true;					// Assume success
	p->fWantsMenuItem	= true;					// if this plug-in wants a menu command in settings menu
	p->fWantsIdleTime	= true;					// if true then plug-in receives op_Idle regularly
	p->fWantsWindow		= false;				// true if the plug-in requires a window
	p->fWindowVisible	= false;				// true if window is initially visible
	p->fWindowID		= 0;					// id of WIND resource for this window
	p->fWindowFloats	= false;				// true if requested window should float
	p->fIsFocuserController = false;			// I don't control a focuser
	p->fIsTelescopeController = false;			// I don't control the Telescope
	p->fAboutMenuItem[0]= 14;					// Length of "Remote Control" entry in Starry Night Help->About Plug-in menu. In characters.
	lstrcpy((char *)(&p->fAboutMenuItem[1]), "Remote Control");
	p->fWindowMenuItem[0]	= 0;				
	p->fOptionsMenuItem[0]	= 0;				// Length of menu item in SN's Favorites menu.

	ReadSettings();

	return(0);
}

// termPlugin
static void termPlugin(void)
{
	// Do things when the plugin (SN) terminates
}

// When the user clicks on the SN Help->About plugin->Remote Control entry an about dialog is shown.
static void doAbout(void)
{
	std::string sMessage = "Remote Control Plugin for Starry Night 8 (Windows)\r\n\r\nSettings File Present: ";

	if (SettingsFileExists())
	{
		sMessage = sMessage + "TRUE\r\n";
		sMessage = sMessage + "Cmd Filepath: " + _sCommandFile + "\r\nCmd Filepath Access: ";

		if (TestCmdFile())
		{
			sMessage = sMessage + "Write + Delete OK";
		}
		else
		{
			sMessage = sMessage + "Write+Delete FAILED!";
		}
	}
	else
	{
		sMessage = sMessage + "FALSE";
	}

	sMessage = sMessage + "\r\n\r\nhttps://github.com/Xio1996/RemoteControl\r\nXio1996 (Cloudy Nights, SGL, Sky Searchers)";

	MessageBox(NULL, sMessage.c_str(), _sAlertTitle.c_str(), (MB_OK & MB_ICONINFORMATION | MB_APPLMODAL));
}

// Starry Night calls the doOperation function with the op_Idle flag.
// We do our thing when Starry Night or the user is not doing anything (idle).
static short doIdle(PEvent *p)
{
	short iRes = 0;	// Assume success (our retval)
	snErr Err; // Error/success code returned from sn_xxxxxx calls

	p->fOutOperation = out_DoNothing;	// Assume no-op
	p->fOutParams = NULL;	

	if (PathFileExists(_sCommandFile.c_str()))
	{
		// Read the file and split the parameters 
		std::string sEAACmd = read_file(_sCommandFile);
		if (sEAACmd.empty())
		{
			DeleteFile(_sCommandFile.c_str());

			//There is no text in the file.
			ShowErrorDialog("Remote Control Command file was empty.");
			return -1;
		}

		std::vector<std::string> v = split(sEAACmd, '|');
		if (v.size() == 0)
		{
			DeleteFile(_sCommandFile.c_str());
			// Does not look like a valid command line.
			ShowErrorDialog("Remote Control command incorrect format.");

			return -1;
		}

		try
		{
			std::string sCmd = v[0];

			// Process the command
			if (sCmd == "target")
			{
				PSelection obj;
				pStr255 pstrName, pstrLayer;

				// Process the command to obtain the ID, RA, Dec & FOV in the correct format for SN
				cToPstr((char*)v[1].data(), pstrName);
				cToPstr("All", pstrLayer);

				PXYZCoordinates pXYZ;
				PSphericalCoordinates pSC;

				// Convert from RA decimal hours degrees and Dec decimal degrees
				pSC.ra = std::stod(v[2].data()) * RAD_PER_HR;			// J2000 in radians
				pSC.dec = std::stod(v[3].data()) * RAD_PER_DEG;			// J2000 in radians

				double dblFOV = std::stod(v[4].data()) * RAD_PER_DEG;	// in radians

				pSC.radius = 1;	// StarryNightPlugins.h said to use 1 for star coordinates.

				// Convert our J2000 coordinates into a XYZ vector for Starry Night.
				sn_SphericalToXYZ(pSC, &pXYZ);

				if (dblFOV > 0)
				{
					// Set the location (RA/Dec) first and set the FOV. 
					// Do this because sn_SetFieldOfView does not appear to work and sn_FindObject will use its own default FOV for an object.
					sn_CentreWindowAtCoords(p->fInWindow, kSNCelestialJ2000System, pXYZ, false, true, dblFOV, true);
				}
				else
				{
					// Set the location (RA/Dec) first but leave the current Starry Night FOV.
					sn_CentreWindowAtCoords(p->fInWindow, kSNCelestialJ2000System, pXYZ, false, false, dblFOV, true);
				}

				// The sn_CentreWindowAtCoords call will lock onto the RA/Dec but if the user changes the FOV the lock is lost.
				// if sn_FindObject finds the object then the lock is preserved even if the FOV is changed by the user.
				// if the find fails then Starry Night maintains the previously called RA/Dec location.
				Err = sn_FindObject(0, pstrName, pstrLayer, &obj, true, false, false, true);
			}
			else if (sCmd == "altaz")
			{
				PXYZCoordinates pXYZ;
				PSphericalCoordinates pSC;

				pSC.ra = std::stod(v[2].data());		// Azimuth
				pSC.ra = (360 - pSC.ra) * RAD_PER_DEG;	// Starry Night's internal Az is anti-clockwise so convert to clockwise.

				pSC.dec = std::stod(v[1].data()) * RAD_PER_DEG;			// Altitude in radians
				double dblFOV = std::stod(v[3].data()) * RAD_PER_DEG;	// FOV in radians

				pSC.radius = 1;	// StarryNightPlugins.h said to use 1 for star coordinates.

				// Convert our AltAz coordinates into a XYZ vector for Starry Night.
				sn_SphericalToXYZ(pSC, &pXYZ);

				if (dblFOV > 0)
				{
					// Set the location (AltAz) first and set the FOV. 
					// Do this because sn_SetFieldOfView does not appear to work.
					sn_CentreWindowAtCoords(p->fInWindow, kSNAltAzSystem, pXYZ, false, true, dblFOV, true);
				}
				else
				{
					// Set the location (Alt/Az) first but leave the current Starry Night FOV.
					sn_CentreWindowAtCoords(p->fInWindow, kSNAltAzSystem, pXYZ, false, false, dblFOV, true);
				}
			}
			else if (sCmd == "fov")
			{
				PXYZCoordinates pcurrXYZ;

				double dblFOV = std::stod(v[1].data()) * RAD_PER_DEG;	// in radians
				if (dblFOV > 0)
				{
					// Get the current position as we are only going to change the current FOV
					sn_GetWindowCentreCoords(p->fInWindow, kSNCelestialJ2000System, &pcurrXYZ);
					// Change the FOV but keep the same position
					sn_CentreWindowAtCoords(p->fInWindow, kSNCelestialJ2000System, pcurrXYZ, false, true, dblFOV, true);
				}
			}
			else if (sCmd == "getselobj")
			{
				PSelection psObject;
				std::string sMsg = "NOSELECTION";

				if (sn_GetPSelection(p->fInWindow, &psObject) != snErr_NoSelection)
				{
					std::string sObjectName(pToCStr(psObject.fObjectName));
					std::string sObjectType(pToCStr(psObject.fObjectType));
					std::string sObjectConst(pToCStr(psObject.fConstellationName));

					// Get the object's position. Conversion from JNOW radian to J2000 in degrees
					PXYZCoordinates pXYZIn, pXYZOut;
					PSphericalCoordinates pscIn, pscOut;

					pscIn.ra = psObject.fRightAscension;
					pscIn.dec = psObject.fDeclination;
					pscIn.radius = 1;

					sn_SphericalToXYZ(pscIn, &pXYZIn);

					sn_CoordinateConversion(p->fInWindow, kSNCelestialJNowSystem, kSNCelestialJ2000System, pXYZIn, &pXYZOut);

					sn_XYZToSpherical(pXYZOut, &pscOut);

					// Output "Name|RA2000|Dec2000|RANow|DecNow|Alt|Az|Mag|Size" All positions and size in degrees.
					sMsg = sObjectName + "|" + sObjectType + "|" + 
										std::to_string(pscOut.ra * HR_PER_RAD) + "|" + std::to_string(pscOut.dec * DEG_PER_RAD) + "|" +
										std::to_string(psObject.fRightAscension * HR_PER_RAD) + "|" + std::to_string(psObject.fDeclination * DEG_PER_RAD) + "|" +
										std::to_string(psObject.fAlt * DEG_PER_RAD) + "|" + std::to_string(psObject.fAz * DEG_PER_RAD) + "|" +
										std::to_string(psObject.fMagnitude) + "|" + std::to_string(psObject.fAngularSize * DEG_PER_RAD);
				}

				// Write the selected objects data or 'NOSELECTION'
				write_file(_sOutFile, sMsg);
			}
			else if (sCmd == "getviewerloc")
			{ 
				double dblLat = 0.0;
				double dblLng = 0.0;
				double dblElevAU = 0.0;
				pBoolean bHovering = false;
				sn_LocationType snLocType;
				std::string sMsg = "NOLOCATION";

				snErr Err = sn_GetViewerLocationInfo(p->fInWindow, &dblLat, &dblLng, &dblElevAU, &snLocType, &bHovering);
				if (Err == snNoErr)
				{
					// Location is on (or above) a planet (object)
					if (snLocType == 901)
					{
						pStr255 pstrPlanetName;

						sn_GetViewerPlanetName(p->fInWindow, pstrPlanetName);

						sMsg = pToCStr(pstrPlanetName);
						sMsg = sMsg + "|"  + std::to_string(dblLat * DEG_PER_RAD) + "|" + std::to_string(dblLng * DEG_PER_RAD) + "|" + std::to_string(dblElevAU) + "|" + std::to_string(snLocType) + "|" + std::to_string(bHovering);
					}
					else
					{
						// Location is in space (heliocentric coordinates
						sMsg = "Helio";
						sMsg = sMsg + "|" + std::to_string(dblLat * DEG_PER_RAD) + "|" + std::to_string(dblLng * DEG_PER_RAD) + "|" + std::to_string(dblElevAU) + "|" + std::to_string(snLocType) + "|" + std::to_string(bHovering);

					}
				}
				write_file(_sOutFile, sMsg);
			}
			else if (sCmd == "getfov")
			{
				std::string sMsg = "NOFOV";
				double dblFOV = 0.0;
				if (sn_GetFieldOfView(p->fInWindow, &dblFOV) == snNoErr)
				{
					sMsg = std::to_string(dblFOV * DEG_PER_RAD);
				}

				write_file(_sOutFile, sMsg);
			}
			else if (sCmd == "getcentrecoords")
			{
				PXYZCoordinates pcentreXYZ;
				std::string sMsg = "NOCENTERCOORDS";

				if (sn_GetWindowCentreCoords(p->fInWindow, kSNOrientationSystem, &pcentreXYZ) == snNoErr)
				{
					sMsg = std::to_string(pcentreXYZ.x) + "|" + std::to_string(pcentreXYZ.y) + "|" + std::to_string(pcentreXYZ.z);
				}

				write_file(_sOutFile, sMsg);
			}
			else if (sCmd == "gettime")
			{
				double dblJulianTime = 0.0;
				std::string sMsg = "NOTIME";

				if (sn_GetCurrentTime(p->fInWindow , &dblJulianTime) == snNoErr)
				{

					sMsg = std::to_string(dblJulianTime);
				}

				write_file(_sOutFile, sMsg);
			}
			else if (sCmd == "GetView")
			{
				// Returns all parameters that define a view in Starry Night
				// The time, observer location, centre of the viewpoint and the FOV.

				PXYZCoordinates pcentreXYZ;
				double dblLat = 0.0; double dblLng = 0.0; double dblElevAU = 0.0; 
				double dblFOV = 0.0; double dblJulianTime = 0.0;
				pBoolean bHovering = false;
				sn_LocationType snLocType;
				pStr255 pstrPlanetName;
				std::string sPlanet = "";
				std::string sMsg = "NOVIEW";

				snErr Err = sn_GetViewerLocationInfo(p->fInWindow, &dblLat, &dblLng, &dblElevAU, &snLocType, &bHovering);
				if (Err == snNoErr)
				{
					// Location is on (or above) a planet (object)
					if (snLocType == 901)
					{
						Err = sn_GetViewerPlanetName(p->fInWindow, pstrPlanetName);
						if (Err == snNoErr)
						{
							sPlanet = pToCStr(pstrPlanetName);
						}
					}

					if (Err == snNoErr) 
					{
						if (sn_GetWindowCentreCoords(p->fInWindow, kSNOrientationSystem, &pcentreXYZ) == snNoErr)
						{
							if (sn_GetFieldOfView(p->fInWindow, &dblFOV) == snNoErr)
							{
								if (sn_GetCurrentTime(p->fInWindow, &dblJulianTime) == snNoErr)
								{
									sMsg = sPlanet + "|";
									sMsg = sMsg + std::to_string(dblLat * DEG_PER_RAD) + "|" + std::to_string(dblLng * DEG_PER_RAD) + "|" + std::to_string(dblElevAU) + "|" + std::to_string(snLocType) + "|" + std::to_string(bHovering);
									sMsg = sMsg + std::to_string(dblFOV * DEG_PER_RAD);
									sMsg = sMsg + std::to_string(dblJulianTime);
								}
							}
						}
					}
				}

				write_file(_sOutFile, sMsg);
			}
		}
		catch (...)
		{
		}

		// Remove the command file as we have finished processing.
		DeleteFile(_sCommandFile.c_str());
		
	}

	return(iRes);
}


// The main function called by Starry Night to allow interaction with the plugin.
SNCall short DoOperation(OperationT inOperation, void* ioParams)
{
	PIndicator *p = (PIndicator *)ioParams;
	short outErr = 0;
	HWND hW;

	// Get the current active window. Sometimes this is 0.
	hW = GetActiveWindow();
	
	if(hW != 0)
		_hWndMain = hW;

	__try {
		switch (inOperation)
		{
			// op_Initialize	
			// Called once at begining of program when the plugin is first initilialized.
			// The current resource file will be the plug-in's file when called.
			// 
			// 
			//  passed ioParams is of type PInitialize*
			case op_Initialize:
				outErr = initPlugin((PInitialize*)ioParams);
				break;

			case op_Terminate:	// NULL
				break;

			case op_About:		// NULL
				doAbout();
				break;

			case op_Idle:		// PEvent* passed in ioParams
				doIdle((PEvent*)ioParams);
				break;
			
			case op_MenuCommand: // NULL
				break;
			// UNKNOWN CALL
			default:
				;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		outErr = -1;
	}

	return outErr;
}
