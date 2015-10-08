/////////////////////////////////////////////////////////////////////////////
// Name:        kesheapp.h
// Purpose:
// Author:      zhou
// Modified by:
// Created:     2015/8/31 15:56:23
// RCS-ID:
// Copyright:   lalala
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _KESHEAPP_H_
#define _KESHEAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/image.h"
#include "mainwin.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * KesheApp class declaration
 */

class KesheApp: public wxApp
{
    DECLARE_CLASS( KesheApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    KesheApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin KesheApp event handler declarations
////@end KesheApp event handler declarations

////@begin KesheApp member function declarations
////@end KesheApp member function declarations

////@begin KesheApp member variables
////@end KesheApp member variables
};

/*!
 * Application instance declaration
 */

////@begin declare app
DECLARE_APP(KesheApp)
////@end declare app

#endif
// _KESHEAPP_H_
