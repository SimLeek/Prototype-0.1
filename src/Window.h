#ifndef __WINDOW_H__
#define __WINDOW_H__



#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/combobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/dnd.h>

#ifdef __WXMAC__
#include "OpenGL/glew.h"
#else
#include <GL/glew.h>
#endif

#include <wx/glcanvas.h>



#include "controls.h"


class MainFrame : public wxFrame
{
	private:

	protected:
		wxComboBox* m_comboBox1;
		wxMenuBar* m_menubar;
		wxMenu* m_File;
		wxMenu* m_Import;
		wxMenu* m_I3D;
		wxMenu* m_ISound;
		wxMenu* m_Export;
		wxMenu* m_E3D;
		wxMenu* m_ESound;
		wxMenu* m_Edit;
		wxMenu* m_View;
		wxMenu* m_Help;
		wxStatusBar* m_statusBar2;

    protected:

        // Virtual event handlers, overide them in your derived class
		void ComboBox_Select( wxCommandEvent& event );
		void ComboBox_Enter( wxCommandEvent& event );
		void Undo( wxCommandEvent& event );
		void Redo( wxCommandEvent& event );
		void Copy( wxCommandEvent& event );
		void Cut( wxCommandEvent& event );
		void Paste( wxCommandEvent& event );
		void Delete( wxCommandEvent& event );
		void Record( wxCommandEvent& event );
		void Toggle_FullScreen( wxCommandEvent& event );
		void Update_Toggle_FullScreen( wxUpdateUIEvent& event );
		void Toggle_ToolBar( wxCommandEvent& event );
		void Update_Toggle_ToolBar( wxUpdateUIEvent& event );
		void Toggle_SearchBar( wxCommandEvent& event );
		void Update_Toggle_SearchBar( wxUpdateUIEvent& event );
		void Toggle_StatusBar( wxCommandEvent& event );
		void Update_Toggle_StatusBar( wxUpdateUIEvent& event );
		void OpenAbout( wxCommandEvent& event );

		//DECLARE_EVENT_TABLE()


	public:

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Prototype"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,450 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();



};


class About : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticTitle;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText1;

	public:

		About( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~About();

};

class BasicGLPane : public wxGLCanvas
{
    wxGLContext*	m_context;
    GLControls* controls;

    GLuint GLprogram;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint fragmentShader2;

public:
	BasicGLPane(wxFrame* parent, int* args);
	virtual ~BasicGLPane();

	void resized(wxSizeEvent& evt);

	int getWidth();
	int getHeight();

	void render(wxPaintEvent& evt);
	void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);

	// events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void rightReleased(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);

	DECLARE_EVENT_TABLE()
};

class DnDFile : public wxFileDropTarget{
public:
    DnDFile(wxGLCanvas* GLowner){ owner = GLowner;}

    virtual bool OnDropFiles 	( 	wxCoord  	x,
                                    wxCoord  	y,
                                    const wxArrayString &  	filenames
                                );
private:
    wxGLCanvas* owner;

};

#endif //__WINDOW_H__
