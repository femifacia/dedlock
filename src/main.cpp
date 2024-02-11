#include <iostream>
#include <string.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
extern "C" {
#include <X11/Xlib.h>

}

#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property

Bool MakeAlwaysOnTop(Display* display, Window root, Window mywin)
{
    Atom wmStateAbove = XInternAtom( display, "_NET_WM_STATE_ABOVE", 1 );
    if( wmStateAbove != None ) {
        printf( "_NET_WM_STATE_ABOVE has atom of %ld\n", (long)wmStateAbove );
    } else {
        printf( "ERROR: cannot find atom for _NET_WM_STATE_ABOVE !\n" );
        return False;
    }
    
    Atom wmNetWmState = XInternAtom( display, "_NET_WM_STATE", 1 );
    if( wmNetWmState != None ) {
        printf( "_NET_WM_STATE has atom of %ld\n", (long)wmNetWmState );
    } else {
        printf( "ERROR: cannot find atom for _NET_WM_STATE !\n" );
        return False;
    }

    // set window always on top hint
    if( wmStateAbove != None )
    {
        XClientMessageEvent xclient;
        memset( &xclient, 0, sizeof (xclient) );
        //
        //window  = the respective client window
        //message_type = _NET_WM_STATE
        //format = 32
        //data.l[0] = the action, as listed below
        //data.l[1] = first property to alter
        //data.l[2] = second property to alter
        //data.l[3] = source indication (0-unk,1-normal app,2-pager)
        //other data.l[] elements = 0
        //
        xclient.type = ClientMessage;
        xclient.window = mywin;              // GDK_WINDOW_XID(window);
        xclient.message_type = wmNetWmState; //gdk_x11_get_xatom_by_name_for_display( display, "_NET_WM_STATE" );
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD; // add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        xclient.data.l[1] = wmStateAbove;      //gdk_x11_atom_to_xatom_for_display (display, state1);
        xclient.data.l[2] = 0;                 //gdk_x11_atom_to_xatom_for_display (display, state2);
        xclient.data.l[3] = 0;
        xclient.data.l[4] = 0;
        //gdk_wmspec_change_state( FALSE, window,
        //  gdk_atom_intern_static_string ("_NET_WM_STATE_BELOW"),
        //  GDK_NONE );
        XSendEvent( display,
          //mywin - wrong, not app window, send to root window!
          root, // <-- DefaultRootWindow( display )
          False,
          SubstructureRedirectMask | SubstructureNotifyMask,
          (XEvent *)&xclient );

        XFlush(display);

        return True;
    }

    return False;
}

bool IsGoodPassword(std::string passwd)
{
    std::string command = "./src/pass.sh " + passwd;
    int ret = std::system(command.c_str());

    std::cout << ret;
    if (ret == 0)
        return 1;
    return 0;
}

int main()
{
    // Create the main window
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(width, height), "Deadlock",1 << 0 | 1 << 2 | 1 << 3);
    sf::Texture texture;
    if (!texture.loadFromFile("./asset/wall1.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    window.setMouseCursorVisible(0);
    bool isOver = 0;
    std::string passwd = "";
    char letterEntered;
    char eraseChar = 8;
    char enterChar = 13;

    window.clear();
        // Draw the sprite
    window.draw(sprite);
        window.display();
    std::system("xmodmap -e 'keycode 133 = 0x0000'");
    while (window.isOpen() && !isOver) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))  {
            // Close window: exit
//            if (event.type == sf::Event::Closed)
//                window.close();
            if (event.type == sf::Event::TextEntered) {
                    letterEntered = (char)event.text.unicode;
                    if (letterEntered == eraseChar) {
                        if (passwd != "")
                            passwd.pop_back();
                        continue;
                    }
                    if (letterEntered == enterChar) {
                        std::cout << passwd << std::endl;
                        isOver = IsGoodPassword(passwd);
                        passwd = "";
                    }
                    passwd += letterEntered;
//                    std::cout <<"["<< event.text.unicode <<"]"<< std::endl;
//                    playerText.setString(playerInput);
                }
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        //window.draw(text);
        // Update the window
        window.display();
    }
    std::cout << "ok" << std::endl;
    std::system("xmodmap -e 'keycode 133 = 0x0085'");
    return (0);
}