#include "Window.h"
#include "util.h"


#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/dnd.h"
#include "wx/dataobj.h"
#include "wx/clipbrd.h"

#include <GL/glut.h>

class App: public wxApp{
    virtual bool OnInit();

    MainFrame* mainFrame;


};

IMPLEMENT_APP(App)

bool App::OnInit(){

    mainFrame = new MainFrame((wxFrame *)NULL);

    mainFrame->Show();
    return true;
}

BEGIN_EVENT_TABLE(BasicGLPane, wxGLCanvas)
    EVT_MOTION(BasicGLPane::mouseMoved)
    EVT_LEFT_DOWN(BasicGLPane::mouseDown)
    EVT_LEFT_UP(BasicGLPane::mouseReleased)
    EVT_RIGHT_DOWN(BasicGLPane::rightClick)
    EVT_RIGHT_UP(BasicGLPane::rightReleased)
    EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
    EVT_SIZE(BasicGLPane::resized)
    EVT_KEY_DOWN(BasicGLPane::keyPressed)
    EVT_KEY_UP(BasicGLPane::keyReleased)
    EVT_MOUSEWHEEL(BasicGLPane::mouseWheelMoved)
    EVT_PAINT(BasicGLPane::render)
END_EVENT_TABLE()

///////////////
//GL CONTROLS
///////////////

void BasicGLPane::mouseMoved(wxMouseEvent& event) {


    /*if (event->Dragging() && controls->buttons[0]){

    }*/


    //last

    controls->prevX = event.m_x;
    controls->prevY = event.m_y;

}
void BasicGLPane::mouseDown(wxMouseEvent& event) {
    controls->buttons[0] = true;
    event.Skip();
}
void BasicGLPane::mouseWheelMoved(wxMouseEvent& event) {}
void BasicGLPane::mouseReleased(wxMouseEvent& event) {
    controls->buttons[0] = false;
}
void BasicGLPane::rightClick(wxMouseEvent& event) {
    controls->buttons[2] = true;

    wxMenu menu(wxT("menu"));

    //menu.Append(Menu_Drag, wxT("&Copy"));
    //menu.Append(Menu_Drag, wxT("&Paste"));
    menu.AppendSeparator();
    //menu.Append(Menu_About, wxT("&About"));

    PopupMenu( &menu, event.GetX(), event.GetY() );

}
void BasicGLPane::rightReleased(wxMouseEvent& event){
    controls->buttons[2] = false;


}
void BasicGLPane::mouseLeftWindow(wxMouseEvent& event) {}
void BasicGLPane::keyPressed(wxKeyEvent& event) {
    controls->keys[event.GetKeyCode()]= true;
}
void BasicGLPane::keyReleased(wxKeyEvent& event) {
    controls->keys[event.GetKeyCode()]= false;
}

void BasicGLPane::resized(wxSizeEvent& evt)
{
//	wxGLCanvas::OnSize(evt);

    Refresh();
}

int BasicGLPane::getWidth()
{
    return GetSize().x;
}

int BasicGLPane::getHeight()
{
    return GetSize().y;
}

bool DnDFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
    size_t nFiles = filenames.GetCount();
    wxString str;
    str.Printf( wxT("%d files dropped"), (int)nFiles);

    /*if (owner != NULL)
    {
        owner->Append(str);
        for ( size_t n = 0; n < nFiles; n++ )
            owner->Append(filenames[n]);
    }*/

    return true;
}

/////////////////
//INITIALIZATION
/////////////////

// Vertices and faces of a simple cube to demonstrate 3D render
// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
GLfloat v[8][3];
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };



BasicGLPane::BasicGLPane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	m_context = new wxGLContext(this);
    // prepare a simple cube to demonstrate 3D render
    // source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    controls= new GLControls;

    /*glutInit(NULL, NULL);

    glewInit();
    if (glewIsSupported("GL_VERSION_3_3"))
		printf("OpenGL 2.0 supported\n");
	else {
		printf("OpenGL 2.0 not supported, you need a new graphics card.\n");
		exit(1);
	}*/


    /*char* vsSource = util::fileToStr("toon.vert");
    char* fsSource = util::fileToStr("toon.frag");
    char* fs2Source = util::fileToStr("toon2.frag");

	vertexShader = glCreateShader(GL_VERTEX_SHADER );
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER );
    fragmentShader2= glCreateShader(GL_FRAGMENT_SHADER );

    glShaderSource(vertexShader, 1, const_cast<const char**>(&vsSource), NULL);
    glShaderSource(fragmentShader, 1, const_cast<const char**>(&fsSource), NULL);
    glShaderSource(fragmentShader2, 1, const_cast<const char**>(&fs2Source), NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    glCompileShader(fragmentShader);

    GLprogram= glCreateProgram();

    glAttachShader(GLprogram, vertexShader);
    glAttachShader(GLprogram, fragmentShader);
    glAttachShader(GLprogram, fragmentShader2);

    glLinkProgram(GLprogram);

    glUseProgram(GLprogram);*/

}

BasicGLPane::~BasicGLPane()
{
	delete m_context;
}

///////////
//RENDER
///////////

/** Inits the OpenGL viewport for drawing in 3D. */
void BasicGLPane::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);

    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
    gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

/** Inits the OpenGL viewport for drawing in 2D. */
/*void BasicGLPane::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}*/

float lpos[4] = {1,0.5,1,0};

void BasicGLPane::render( wxPaintEvent& evt )
{
    if(!IsShown()) return;

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ------------- draw some 2D ----------------
   /* prepare2DViewport(0,0,getWidth()/2, getHeight());
    glLoadIdentity();

    // white background
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(getWidth(),0,0);
    glVertex3f(getWidth(),getHeight(),0);
    glVertex3f(0,getHeight(),0);
    glEnd();

    // red square
    glColor4f(1, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3f(getWidth()/8, getHeight()/3, 0);
    glVertex3f(getWidth()*3/8, getHeight()/3, 0);
    glVertex3f(getWidth()*3/8, getHeight()*2/3, 0);
    glVertex3f(getWidth()/8, getHeight()*2/3, 0);
    glEnd();*/

    // ------------- draw some 3D ----------------
    prepare3DViewport(0,0,getWidth(), getHeight());
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);

    glColor4f(0,0,1,1);
    glTranslatef(0,0,-5);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

    glColor4f(1, 0, 0, 1);
    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_LINE_STRIP);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glEnd();
    }

    glFlush();
    SwapBuffers();
}








