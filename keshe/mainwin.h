/////////////////////////////////////////////////////////////////////////////
// Name:        mainwin.h
// Purpose:
// Author:      zhou
// Modified by:
// Created:     2015/9/2 14:18:24
// RCS-ID:
// Copyright:   lalala
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINWIN_H_
#define _MAINWIN_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/valtext.h"
#include "wx/treectrl.h"
////@end includes

#include "core.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MAINWIN 10000
#define SYMBOL_MAINWIN_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_MAINWIN_TITLE _("mainwin")
#define SYMBOL_MAINWIN_IDNAME ID_MAINWIN
#define SYMBOL_MAINWIN_SIZE wxSize(800, 600)
#define SYMBOL_MAINWIN_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * mainwin class declaration
 */

class mainwin: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( mainwin )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    mainwin();
    mainwin( wxWindow* parent, wxWindowID id = SYMBOL_MAINWIN_IDNAME, const wxString& caption = SYMBOL_MAINWIN_TITLE, const wxPoint& pos = SYMBOL_MAINWIN_POSITION, const wxSize& size = SYMBOL_MAINWIN_SIZE, long style = SYMBOL_MAINWIN_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MAINWIN_IDNAME, const wxString& caption = SYMBOL_MAINWIN_TITLE, const wxPoint& pos = SYMBOL_MAINWIN_POSITION, const wxSize& size = SYMBOL_MAINWIN_SIZE, long style = SYMBOL_MAINWIN_STYLE );

    /// Destructor
    ~mainwin();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin mainwin event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnOkButtonClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
    void OnClearButtonClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
    void OnGenerateClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
    void OnNextClick( wxCommandEvent& event );

////@end mainwin event handler declarations

////@begin mainwin member function declarations


    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end mainwin member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin mainwin member variables
protected:
    wxString m_desmac;
    wxString m_seedstr;
    wxString m_sourcemac;
    wxString m_userdata;
////@end mainwin member variables

    EthernetFrame m_core;
    int clicknum;

private:
    void showresult();
};

#endif
// _MAINWIN_H_
