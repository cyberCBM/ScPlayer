# The ScPlayer Network Audio Player |
By CyberCBM(cyber.cbm@gmail.com)    |
-------------------------------------

ScPlayer(Network Audio Player) holds GNU General Public License v2. It is created in C++ using JUCE and DrwoAudio Classes.
ScPlayer "Server-Client(Network) Audio Player" is Juce(C++) based Music player for Network teams to play their network hosted music. 

How to Install:
---------------
Start the ScPlayer-Server, press Red button in top panel, that will start your Server. Server can add any songs either from network storage or local machine's songs.

Start ScPlayer-Client on network machine, In first time you will be added to server, And once added clients' right is granted from server, client is able to manage Server Music player i.e Client can change current song, add new songs from network, delete songs from playlist, change order of songs in playlist, save and restore playList. 

How to Use:
-----------
ScPlayer-Server:
Server is Audio player that is running on that machine which has speakers attached with it and attached to network also.
(1) Server can manage audio setting from Top Panel's setting button.
(2) Server can manage clients to let connect and get Lock for modification or not.
(3) Server can add songs from either network or local drive too.
(4) Server is able to seek the song using seekBar for current playing song.
(5) Server has play/pause/stop and back/previous song facility.
(6) Server can also rewind and forward song by continuously pressing back and previous buttons.

ScPlayer-Client:
Client is simple application that can connect to ScPlayer-Server by It's Ipaddress(Machine's Ip on which ScPlayer-Server.exe is running) and Port Number(7227). If client has rights to connect to server is granted from server, client will be connected to server, and get the updates from server about current playList, current playing song, current lock status and owner. if client see network is green(at bottom), client can ask for lock to server for music player modification.
(1) Client can connect and Lock for modification to server audio player.
(2) before connecting to Server, client can change it's name in client setting section.
(3) if Client has lock It can play/pause/stop and back/song on current playing song.
(4) If Client has lock can drag and drop songs from network (No local machine's songs allowed from client)
(5) If client don't have lock still it can create and save playlist from network for later use.

Updates in new version:
-----------------------
Shuffle : Random and unique non repeative songs
Drag nad Drop : Songs and playlist can be dropped from Explorer to any song inbetween

For more information, visit the website:
http://cybercbm.github.com/ScPlayer/