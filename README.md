# RemoteControl
<b>Starry Night Plugin - Remote Control</b>

A plugin for the astronomy application <a href="https://www.starrynight.com/starry-night-8-professional-astronomy-telescope-control-software.html">Starry Night</a>. The plugin allows object view synchronisation between external apps such as AstroPlanner and Starry Night. The remote control plugin for Starry Night 8, was based on the ASCOM Focuser example in the <a href="https://support.simulationcurriculum.com/hc/en-us/articles/231532987-Starry-Night-Plugin-SDK">Starry Night plugin SDK</a>. Developed and tested on Windows 11 and Starry Night Pro 8.1.0.2049
<p>Unlike many astronomy applications (such as Stellarium, AstroPlanner, CdC and TheSky etc) Starry Night 8 Pro does not have any way of allowing external apps to control its features. Such as finding and selecting objects by name or position, setting the field of view etc. However, Starry Night 8 does publish a Plugin SDK. This project is an experiment in writing a plugin that could integrate Starry Night Pro 8 into my EAA workflow.</p>
<p><b>The code is not robust and not well written but if you have a similar requirement, then it might be a help (hopefully not a hinderance) in developing your own Starry Night Plugin. Have fun!</b></p>

<b>Overview.</b><br/>
Communication with the plugin is via a text file. The plugin waits until the file exists and then processes the command content.
The file has a single line of bar (|) separated parameters e.g.  target|Polaris|2.530195|89.26417|10
The first parameter is the lowercase command. It is a very simple communication method and allows easy access to the plugins features.

<b>Commands</b>

<b>target Command</b>: Will move Starry Night to the specified object ID or if not found to the RA/DEC (J2000) location and change the FOV (0 FOV, keep current FOV)<br/>
<p>target|ID|RA|Dec|FOV</p>
ID = The Starry Night object we wanto to move to.<br/>
RA = Decimal Hours (J2000)<br/>
Dec = Degrees (J2000)<br/>
FOV = Degrees<br/>
<p>E.g. target|M13|16.69478|36.4598|5</p>

<b>altaz Command</b>: Moves to the specified Alt/Az location and sets the FOV (0 FOV, keeps the current FOV)<br/>
<p>altaz|Alt|Az|FOV<br/></p>
Alt = Degrees<br/>
Az = Degrees<br/>
FOV = Degrees<br/>
<p>E.g. altaz|45|180|107</p>

<b>fov Command</b>: changes SN's FOV (in degrees). The centre position is unchanged and a FOV of 0 is ignored.<br/>
<p>fov|FOV</p>
FOV = degrees<br/>
<p>E.g. fov|110</p>

<p><b>The following 'get' commands will write their output to the 'snrout.txt' file in the same directory as specified for the 'snmsg.txt' file.</b></p>

<p><b>getselobj Command</b>: This returns information on the currently selected object. If no object is selected the message NOSELECTION is returned. </p>
<p>Object Name|Object Type|RA(J2000)|Dec(J2000)|RA(JNOW)|Dec(JNOW)|Alt|Az|Magnitude|Size</p>
<p>
 Object Name = The SN name for the current object.<br/>
 Object Type = The SN object type.<br/>
 RA(J2000) = J2000 coordinates in decimal hours (13h 30m = 13.5).<br/>
 Dec(J2000) = J2000 coordinates in degrees.<br/>
 RA(JNOW) = JNOW coordinates in degrees.<br/>
 Dec(JNOW) = JNOW coordinates in degrees.<br/>
 Alt = Local altitude in degrees.<br/>
 Az = Local azimuth in degrees.<br/>
 Magnitude = The magnitude (if any) of object.<br/>
 Size = The size of an object in degrees. If none then 0 is returned.
</p>

<p>E.g. Polaris|Star with Exoplanet|2.530292|89.264111|3.033089|89.364666|50.069680|0.096951|1.960000|0.000000</p>

<p><b>getviewerloc Command</b>: Returns the location of the observer in either planet lattitude/longitude or heliocentric coordinates.</p>
<p>Planet|Lattitude|Longitude|Altitude|Coordinate System|Hovering</p>
<p>
Planet = The current planet or 'Helio' if using heliocentric coordinates.<br/>
Lattitude = Latitiude on planet or heliocentric coordinate in degrees.
Longitude = Longitude on planet or heliocentric coordiante in degrees.
Altitude = The altitude in astronomical units from the planets surface.
Coordinate System = 901 Planetary, 902 Stationary location (heliocentric)
Hovering = 0 not hovering (follows object rotation) or 1 hovering 
</p>
<p>Earth|51.204000|-1.630000|0.000000|901|0</p>

<p><b>getfov Command</b>: Returns the current field of view in degrees.</p>
<p>fov</p>
<p>fov = The current field of view in degrees.</p>
<p>110.00000</p>

<p><b>getcentrecoords Command</b>: Returns the centre position of the view in x,y,z coordinates (radians) for the views current coordinate system (Options->Orientation menu item).</p>
<p>x|y|z</p>
<p>
 x = x coordiante in radians.<br/>
 y = y coordinate in radians.<br/>
 z = z coordinate in radians.<br/>
</p>
<p>E.g. -0.698544|0.147982|0.700098</p>

<p><b>gettime Command</b>: Returns the Julian time in univeral time (UT).</p>
<p>JulianTime</p>
<p>JulianTime = UT Julian Time</p>
<p>2460289.947557</p>

<b>INSTALLATION</b>
 
Place the "RemoteControl_Win32.plug" (plugin) and the "RemoteControl_Win32.ini" (configuration) files into the Starry Night plugins folder.
The plugins ("Plug-ins") folder resides in the Starry Night installation folder. Something like "C:\Program Files (x86)\Starry Night Pro 8\Sky Data\Plug-ins".<br/>
<p>Edit the "RemoteControl_Win32.ini" file in a text editor. Provide the full path and filename to the file used to communicate with the plugin.
Something like "C:\StarryNightMsg\snmsg.txt". Choose a location that allows you and Starry Night to read/write and delete the file.</p>

<b>ABOUT Dialog (Checking Installation)</b>

When Starry Night is running click on the Help->About Plug-in->Remote Control menu entry to bring up the About dialog.
The dialog checks that the settings file is present and displays the filepath read from the file. The plugin then checks that it
has the permissions to write and delete the file.<br/>
 
If the Remote Control entry is missing from the 'About Plug-in' menu then Starry Night did not recognise this plugin! 
Review the installation instructions. If you develop your own plugin then make sure the plugin filename ends "_Win32.plug"<br/>

<b>Remote Control Plugin Client</b><br/>
<p>To test the plugin there is a Windows desktop app to exercise the plugin's commands. It allows pre-defined commands and parameters to be sent to the Remote Control Plugin or user defined.
 It is included here for completness and is not required to use the remote control plugin.</p>

<b>AstroPlanner Script</b><br/>
<p>A simple AstroPlanner script that synchronises the selected object in AstroPlanner with the selected object or position in Starry Night.</p>
 
<b>TODO</b><br/>
<p>A better "real-world" solution would be to communicate with the plugin via a TCP port or http call as is
done in other astronomy applications.</p>

This is a "happy days" implementation and needs hardening against failure and correcting the wrongs against coding!
