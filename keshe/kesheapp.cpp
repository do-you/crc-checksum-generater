/////////////////////////////////////////////////////////////////////////////
// Name:        kesheapp.cpp
// Purpose:     
// Author:      zhou
// Modified by: 
// Created:     2015/8/31 15:56:23
// RCS-ID:      
// Copyright:   lalala
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/fs_zip.h"
////@end includes

#include "kesheapp.h"

////@begin XPM images

////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( KesheApp )
////@end implement app


/*
 * KesheApp type definition
 */

IMPLEMENT_CLASS( KesheApp, wxApp )


/*
 * KesheApp event table definition
 */

BEGIN_EVENT_TABLE( KesheApp, wxApp )

////@begin KesheApp event table entries
////@end KesheApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for KesheApp
 */

KesheApp::KesheApp()
{
    Init();
}


/*
 * Member initialisation
 */

void KesheApp::Init()
{
////@begin KesheApp member initialisation
////@end KesheApp member initialisation
}

/*
 * Initialisation for KesheApp
 */

bool KesheApp::OnInit()
{    
////@begin KesheApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

    wxXmlResource::Get()->InitAllHandlers();
    wxFileSystem::AddHandler(new wxZipFSHandler);
    wxXmlResource::Get()->Load(wxT("mainwin.xrc"));

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
    mainwin* mainWindow = new mainwin(NULL);
    /* int returnValue = */ mainWindow->ShowModal();

    mainWindow->Destroy();
    // A modal dialog application should return false to terminate the app.
    return false;
////@end KesheApp initialisation

    return true;
}


/*
 * Cleanup for KesheApp
 */

int KesheApp::OnExit()
{    
////@begin KesheApp cleanup
    return wxApp::OnExit();
////@end KesheApp cleanup
}

