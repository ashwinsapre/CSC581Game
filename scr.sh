cp /run/user/1000/gvfs/dav+sd:host=Spice%2520client%2520folder._webdav._tcp.local/a1.cpp .
cp /run/user/1000/gvfs/dav+sd:host=Spice%2520client%2520folder._webdav._tcp.local/Circle.h .
cp /run/user/1000/gvfs/dav+sd:host=Spice%2520client%2520folder._webdav._tcp.local/Rectangle.h . 
cp /run/user/1000/gvfs/dav+sd:host=Spice%2520client%2520folder._webdav._tcp.local/Time.h . 
g++ -c a1.cpp
g++ a1.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app