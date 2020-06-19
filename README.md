# best_team
ENGR101 AVC project

*Windows 10 Installation guide*
(This program uses the Geany C++ text editor, please ensure this environment is installed first)
1) Download all the files from this repository into a zip.
2) Extract the contents of SFML.zip. Then open the extracted version and save the SFML folder inside to your C: drive following this path: This PC > Local Disk(C:)
3) Open control panel (press windows key and start typing "control panel") and go to System and Security > System > Advanced System Settings > Environment Variables. In the list "System Variables" select "Path" and click "Edit..."
4) In here click "New" and paste this "C:\\mingw\bin". Now click "OK" until you have exited the control panel.
5) Extract the AVC_Win10.zip folder and then save it where ever you would like on your PC.
6) Go into the folder and open "AVC_robot", then open "robot.cpp", "makefile", "robot.hpp" and "config" with Geany.
7) Once the files are open in Geany go to the makefile and ensure the directory in the first line reads "DIR = C:\\SFML". If you saved the SFML folder in a different location then go to the address where it is located, open the SFML folder to where it is showing the bin, doc, examples, etc folders inside, right click on "SFML" at the top and copy the address as text. 
Paste this into the directory so it looks like "DIR = C:\\Example\SFML"
8) Delete spaces before the lines starting with "g++" and then press Tab to properly indent and save.
9) Navigate to robot.cpp file in Geany and select the down arrow next to build, press "Set Build Commands". In front of the words "make" add "mingw32-", The result of which should read "mingw32-make". Press OK.
10) Select the arrow next to build again and press "Make All". Once compiled navigate back to the AVC_robot folder and go back one to open the "AVC_server" folder. Inside open "server3.cpp" with Geany. Press "Execute" next to build and after 3 pages have opened go back to robot.cpp in Geany and select Execute.
11) If any changes are made to the code in Geany press "Make All" to compile before executing again. The server must always be executed before the robot.
