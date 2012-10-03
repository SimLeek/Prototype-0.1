#ifndef __CONTROLS_H__
#define __CONTROLS_H__


struct GLControls{

//KEYS
    bool keys[512];
    bool esc;
    bool shif;
    bool ctrl;
    bool alt;

//MOUSE
    bool buttons[3];
    int prevX;
    int prevY;
    //there's an error here if a mouse action occurs right at startup
    //unless these are set to the mouse coordinates on startup

};


#endif
