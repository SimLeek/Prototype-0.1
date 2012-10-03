
#include "Window.h"


/////////////////
/////////////////
//EVENT SECTION
/////////////////
/////////////////



void MainFrame::ComboBox_Select( wxCommandEvent& event ){};
void MainFrame::ComboBox_Enter( wxCommandEvent& event ){};
void MainFrame::Undo( wxCommandEvent& event ){};
void MainFrame::Redo( wxCommandEvent& event ){};
void MainFrame::Copy( wxCommandEvent& event ){};
void MainFrame::Cut( wxCommandEvent& event ){};
void MainFrame::Paste( wxCommandEvent& event ){};
void MainFrame::Delete( wxCommandEvent& event ){};
void MainFrame::Record( wxCommandEvent& event ){};
void MainFrame::Toggle_FullScreen( wxCommandEvent& event ){};
void MainFrame::Toggle_ToolBar( wxCommandEvent& event ){};
void MainFrame::Toggle_SearchBar( wxCommandEvent& event ){};
void MainFrame::Toggle_StatusBar( wxCommandEvent& event ){};
void MainFrame::OpenAbout( wxCommandEvent& event ){

    About* about= new About((wxFrame*)this);

    about->Show();
};


/////////////////////////
/////////////////////////
//INITIALIZATION SECTION
/////////////////////////
/////////////////////////


MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_comboBox1 = new wxComboBox( this, wxID_ANY, wxT("Go to a Location"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0x0400 );
	bSizer1->Add( m_comboBox1, 0, wxALL|wxEXPAND, 5 );

	//--- GL pane
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

    BasicGLPane * glPane;
	glPane = new BasicGLPane( (wxFrame*) this, args);

	glPane->SetDropTarget(new DnDFile(glPane));

	bSizer1->Add(glPane, 1, wxEXPAND);
	//--- GL pane

	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar = new wxMenuBar( 0 );
	m_File = new wxMenu();
	m_Import = new wxMenu();
	m_I3D = new wxMenu();
	m_Import->Append( -1, wxT("3D"), m_I3D );

	m_ISound = new wxMenu();
	m_Import->Append( -1, wxT("Sound"), m_ISound );

	m_File->Append( -1, wxT("Import"), m_Import );

	m_Export = new wxMenu();
	m_E3D = new wxMenu();
	m_Export->Append( -1, wxT("3D"), m_E3D );

	m_ESound = new wxMenu();
	m_Export->Append( -1, wxT("Sound"), m_ESound );

	m_File->Append( -1, wxT("Export"), m_Export );

	m_menubar->Append( m_File, wxT("File") );

	m_Edit = new wxMenu();
	wxMenuItem* m_Undo;
	m_Undo = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Undo") ) + wxT('\t') + wxT("Ctrl-Z"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Undo );

	wxMenuItem* m_Redo;
	m_Redo = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Redo") ) + wxT('\t') + wxT("Ctrl-Y"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Redo );

	wxMenuItem* m_separator1;
	m_separator1 = m_Edit->AppendSeparator();

	wxMenuItem* m_Copy;
	m_Copy = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Copy") ) + wxT('\t') + wxT("Ctrl-C"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Copy );

	wxMenuItem* m_Cut;
	m_Cut = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Cut") ) + wxT('\t') + wxT("Ctrl-X"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Cut );

	wxMenuItem* m_Paste;
	m_Paste = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Paste") ) + wxT('\t') + wxT("Ctrl-V"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Paste );

	wxMenuItem* m_Delete;
	m_Delete = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Delete") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Delete );

	wxMenuItem* m_separator7;
	m_separator7 = m_Edit->AppendSeparator();

	wxMenuItem* m_Record;
	m_Record = new wxMenuItem( m_Edit, wxID_ANY, wxString( wxT("Record") ) + wxT('\t') + wxT("Ctrl-R"), wxEmptyString, wxITEM_NORMAL );
	m_Edit->Append( m_Record );

	m_menubar->Append( m_Edit, wxT("Edit") );

	m_View = new wxMenu();
	wxMenuItem* m_FullScreen;
	m_FullScreen = new wxMenuItem( m_View, wxID_ANY, wxString( wxT("FullScreen") ) + wxT('\t') + wxT("Alt-Enter"), wxEmptyString, wxITEM_CHECK );
	m_View->Append( m_FullScreen );

	wxMenuItem* m_separator8;
	m_separator8 = m_View->AppendSeparator();

	wxMenuItem* m_ToolBar;
	m_ToolBar = new wxMenuItem( m_View, wxID_ANY, wxString( wxT("ToolBar") ) + wxT('\t') + wxT("Ctrl-T"), wxEmptyString, wxITEM_CHECK );
	m_View->Append( m_ToolBar );
	m_ToolBar->Check( true );

	wxMenuItem* m_SearchBar;
	m_SearchBar = new wxMenuItem( m_View, wxID_ANY, wxString( wxT("SearchBar") ) , wxEmptyString, wxITEM_CHECK );
	m_View->Append( m_SearchBar );
	m_SearchBar->Check( true );

	wxMenuItem* m_StatusBar;
	m_StatusBar = new wxMenuItem( m_View, wxID_ANY, wxString( wxT("Status Bar") ) , wxEmptyString, wxITEM_CHECK );
	m_View->Append( m_StatusBar );

	m_menubar->Append( m_View, wxT("View") );

	m_Help = new wxMenu();
	wxMenuItem* m_About;
	m_About = new wxMenuItem( m_Help, wxID_ANY, wxString( wxT("About") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	m_Help->Append( m_About );

	m_menubar->Append( m_Help, wxT("Help") );

	this->SetMenuBar( m_menubar );

	m_statusBar2 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	m_comboBox1->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &MainFrame::ComboBox_Select, this);
	//m_comboBox1->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrame::ComboBox_Select ), NULL, this );
	//m_comboBox1->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::ComboBox_Enter ), NULL, this );
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Undo, this,  m_Undo->GetId() );
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Redo, this, m_Redo->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Copy, this, m_Copy->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Cut, this, m_Cut->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Paste, this, m_Paste->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Delete, this, m_Delete->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Record, this, m_Record->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Toggle_FullScreen, this, m_FullScreen->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Toggle_ToolBar, this, m_ToolBar->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Toggle_SearchBar, this, m_SearchBar->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Toggle_StatusBar, this, m_StatusBar->GetId());
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OpenAbout, this, m_About->GetId());

}

MainFrame::~MainFrame()
{

}

About::About( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_staticTitle = new wxStaticText( this, wxID_ANY, wxT("Prototype 0.1"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTitle->Wrap( -1 );
	m_staticTitle->SetFont( wxFont( 14, 72, 90, 90, false, wxEmptyString ) );

	bSizer2->Add( m_staticTitle, 0, wxALL|wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("\n"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer2->Add( m_staticText3, 0, wxALL, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("This is the first of the Prototype series.\nRight now I'm just trying to get everything working."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 8, 73, 90, 90, false, wxEmptyString ) );

	bSizer2->Add( m_staticText1, 0, wxALL|wxEXPAND, 5 );

	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );
}

About::~About()
{
}

