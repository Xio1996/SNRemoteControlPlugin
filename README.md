# RemoteControl
<b>Starry Night Plugin - Remote Control</b>

A plugin for the astronomy application <a href="https://www.starrynight.com/starry-night-8-professional-astronomy-telescope-control-software.html">Starry Night</a>. The plugin allows object view synchronisation between external apps such as AstroPlanner and Starry Night. The remote control plugin for Starry Night 8, was based on the ASCOM Focuser example in the <a href="https://support.simulationcurriculum.com/hc/en-us/articles/231532987-Starry-Night-Plugin-SDK">Starry Night plugin SDK</a>. Developed and tested on Windows 11 and Starry Night Pro 8.1.0.2049
<p>Unlike many astronomy applications (such as Stellarium, AstroPlanner, CdC and TheSky etc) Starry Night 8 Pro does not have any way of allowing external apps to control its features. Such as finding and selecting objects by name or position, setting the field of view etc. However, Starry Night 8 does publish a Plugin SDK. This project is an experiment in writing a plugin that could integrate Starry Night Pro 8 into my EAA workflow.</p>
<p><b>The code is not robust and not well written but if you have a similar requirement, then it might be a help (hopefully not a hinderance) in developing your own Starry Night Plugin. Have fun!</b></p>

<b>Overview.</b><br/>
Communication with the plugin is via a text file. The plugin waits until the file exists and then processes the command content.
The file has a single line of bar (|) separated parameters e.g.  target|M13|16.69478|36.4598|5
The first parameter is the lowercase command. It is a very simple communication method but allows easy access to the plugins features.

<b>Commands</b>

TARGET Command: Will move Starry Night to the specified object ID or if not found to the RA/DEC (J2000) location and change the FOV (0 FOV, keep current FOV)<br/>
ID = The Starry Night object we wanto to move to.<br/>
RA = Decimal Hours, J2000, Dec = Degrees, J2000, FOV = Degrees<br/>
target|ID|RA|Dec|FOV<br/>

ALTAZ Command: Moves to the specified Alt/Az location and sets the FOV (0 FOV, keeps the current FOV)<br/>
Alt = Degrees, Az = Degrees, FOV = Degrees<br/>
altaz|Alt|Az|FOV<br/>

FOV Command: changes SN's FOV (in degrees). The centre position is unchanged and a FOV of 0 is ignored.<br/>
FOV = degrees<br/>
fov|FOV<br/>
 
<b>INSTALLATION</b>
 
Place the "RemoteControl_Win32.plug" (plugin) and the "RemoteControl_Win32.ini" (configuration) files into the Starry Night plugins folder.
The plugins ("Plug-ins") folder resides in the Starry Night installation folder. Something like "C:\Program Files (x86)\Starry Night Pro 8\Sky Data\Plug-ins".<br/>
<p>Edit the "RemoteControl_Win32.ini" file in a text editor. Provide the full path and filename to the file used to communicate with the plugin.
Something like "D:\StarryNightMsg\snmsg.txt". Choose a location that allows you and Starry Night to read/write and delete the file.</p>

<b>ABOUT Dialog (Checking Installation)</b>

When Starry Night is running click on the Help->About Plug-in->Remote Control menu entry to bring up the About dialog.
The dialog checks that the settings file is present and displays the filepath read from the file. The plugin then checks that it
has the permissions to write and delete the file.<br/>
 
If the Remote Control entry is missing from the 'About Plug-in' menu then Starry Night did not recognise this plugin! 
Review the installation instructions. If you develop your own plugin then make sure the plugin filename ends "_Win32.plug"<br/>

<b>Remote Control Plugin Client</b><br/>
<p>To test the plugin there is a Windows desktop app to exercise the plugin's commands. It allows pre-defined commands and parameters to be sent to the Remote Control Plugin or user defined.
 It is included here for completness.</p>

<b>AstroPlanner Script</b><br/>
<p>A simple AstroPlanner script that synchronises the selected object in AstroPlanner with the selected object or position in Starry Night.</p>
 
<b>TODO</b><br/>
<p>A better "real-world" solution would be to communicate with the plugin via a TCP port or http call as is
done in other astronomy applications.</p>

This is a "happy days" implementation and needs hardening against failure and correcting the wrongs against coding!
