/////////////////////////////////////////////////////////////////////////////
// Name:        mainwin.cpp
// Purpose:
// Author:      zhou
// Modified by:
// Created:     2015/9/2 14:18:24
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
#include "wx/imaglist.h"
////@end includes

#include "mainwin.h"

////@begin XPM images
////@end XPM images


/*
 * mainwin type definition
 */

IMPLEMENT_DYNAMIC_CLASS( mainwin, wxDialog )


/*
 * mainwin event table definition
 */

BEGIN_EVENT_TABLE( mainwin, wxDialog )

////@begin mainwin event table entries
    EVT_BUTTON( XRCID("ID_BUTTON"), mainwin::OnOkButtonClick )
    EVT_BUTTON( XRCID("ID_BUTTON1"), mainwin::OnClearButtonClick )
    EVT_BUTTON( XRCID("ID_BUTTON2"), mainwin::OnGenerateClick )
    EVT_BUTTON( XRCID("ID_BUTTON3"), mainwin::OnNextClick )
////@end mainwin event table entries

END_EVENT_TABLE()


/*
 * mainwin constructors
 */

mainwin::mainwin()
{
    Init();
}

mainwin::mainwin( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * mainwin creator
 */

bool mainwin::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin mainwin creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    SetParent(parent);
    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end mainwin creation
    return true;
}


/*
 * mainwin destructor
 */

mainwin::~mainwin()
{
////@begin mainwin destruction
////@end mainwin destruction
}


/*
 * Member initialisation
 */

void mainwin::Init()
{
////@begin mainwin member initialisation
////@end mainwin member initialisation
    clicknum = 1;
    m_seedstr = "X8+X2+X+1";
}


/*
 * Control creation for mainwin
 */

void mainwin::CreateControls()
{
////@begin mainwin content construction
    if (!wxXmlResource::Get()->LoadDialog(this, GetParent(), wxT("ID_MAINWIN")))
        wxLogError(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
    // Set validators
    if (FindWindow(XRCID("ID_TEXTCTRL")))
        FindWindow(XRCID("ID_TEXTCTRL"))->SetValidator( wxTextValidator(wxFILTER_NONE, & m_sourcemac) );
    if (FindWindow(XRCID("ID_TEXTCTRL1")))
        FindWindow(XRCID("ID_TEXTCTRL1"))->SetValidator( wxTextValidator(wxFILTER_NONE, & m_desmac) );
    if (FindWindow(XRCID("ID_TEXTCTRL2")))
        FindWindow(XRCID("ID_TEXTCTRL2"))->SetValidator( wxTextValidator(wxFILTER_NONE, & m_userdata) );
    if (FindWindow(XRCID("ID_TEXTCTRL4")))
        FindWindow(XRCID("ID_TEXTCTRL4"))->SetValidator( wxTextValidator(wxFILTER_NONE, & m_seedstr) );
////@end mainwin content construction

    // Create custom windows not generated automatically here.
////@begin mainwin content initialisation
////@end mainwin content initialisation
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void mainwin::OnOkButtonClick( wxCommandEvent& event )
{
    TransferDataFromWindow();
    m_sourcemac.Replace("-", wxEmptyString);
    m_desmac.Replace("-", wxEmptyString);
    int checkresult = m_core.fillframe(m_sourcemac.MakeUpper().ToStdString(), m_desmac.MakeUpper().ToStdString(), m_userdata.ToStdString(), m_seedstr.ToStdString());

    if (checkresult)
    {
        if (checkresult & 1)
            wxMessageBox(wxT("error:源MAC地址格式不正确"), wxT("错误提示"), wxICON_ERROR);
        if (checkresult & 2)
            wxMessageBox(wxT("error:目的MAC地址格式不正确"), wxT("错误提示"), wxICON_ERROR);
        if (checkresult & 4)
            wxMessageBox(wxT("error:数据部分格式不正确"), wxT("错误提示"), wxICON_ERROR);
        if (checkresult & 8)
            wxMessageBox(wxT("error:生成多项式语法错误"), wxT("错误提示"), wxICON_ERROR);
    }
    else
    {
        if (FindWindow(XRCID("ID_BUTTON2")))
            FindWindow(XRCID("ID_BUTTON2"))->Enable();
        if (FindWindow(XRCID("ID_BUTTON3")))
            FindWindow(XRCID("ID_BUTTON3"))->Enable();
        if (FindWindow(XRCID("ID_SCROLLEDWINDOW")))
        {
            ((wxTextCtrl*)FindWindow(XRCID("ID_SCROLLEDWINDOW")))->Clear();
            ((wxTextCtrl*)FindWindow(XRCID("ID_SCROLLEDWINDOW")))->AppendText(m_core.getcrcdata() + string(crcgenerater::checkseedstr(m_seedstr.ToStdString())-1,'0')+"\n");
        }
        if (FindWindow(XRCID("ID_TEXTCTRL3")))
            ((wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL3")))->Clear();
        if (FindWindow(XRCID("ID_TREECTRL")))
            ((wxTreeCtrl*)FindWindow(XRCID("ID_TREECTRL")))->DeleteAllItems();
        clicknum = 1;
    }
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void mainwin::OnClearButtonClick( wxCommandEvent& event )
{
    if (FindWindow(XRCID("ID_TEXTCTRL")))
        ((wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL")))->Clear();
    if (FindWindow(XRCID("ID_TEXTCTRL1")))
        ((wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL1")))->Clear();
    if (FindWindow(XRCID("ID_TEXTCTRL2")))
        ((wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL2")))->Clear();
    if (FindWindow(XRCID("ID_SCROLLEDWINDOW")))
        ((wxTextCtrl*)FindWindow(XRCID("ID_SCROLLEDWINDOW")))->Clear();
}

void mainwin::showresult()
{
    vector<string>* crcresults = m_core.getcrcresults();
    FindWindow(XRCID("ID_BUTTON2"))->Enable(false);
    FindWindow(XRCID("ID_BUTTON3"))->Enable(false);
    string crcresult = wxString(crcresults->back()).Trim(false).ToStdString();
    ((wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL3")))->SetValue(crcresult);
    if (FindWindow(XRCID("ID_TREECTRL")))
    {
        wxTreeCtrl *a = (wxTreeCtrl*)FindWindow(XRCID("ID_TREECTRL"));
        auto x=a->AddRoot(wxT("802.3帧结构"));
        a->AppendItem(x, wxT("前导码:AAAAAAAAAAAAAA"));
        a->AppendItem(x, wxT("帧前定界符:AB"));
        a->AppendItem(x, wxT("目的地址:") + m_desmac);
        a->AppendItem(x, wxT("源地址:") + m_sourcemac);

        short temp = m_userdata.size() / 8;
        temp = htons(temp);
        a->AppendItem(x, wxT("长度字段:") + m_core.binarystrtohex(bitset<16>(temp).to_string()));
        a->AppendItem(x, wxT("数据字段:") + m_core.binarystrtohex(m_userdata.ToStdString()));

        crcresult += string( 32 - crcresult.size(),'0');
        a->AppendItem(x, wxT("校验字段:") + m_core.binarystrtohex(crcresult));
    }
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
 */

void mainwin::OnGenerateClick( wxCommandEvent& event )
{
    wxTextCtrl *showarea;
    if (FindWindow(XRCID("ID_SCROLLEDWINDOW")))
    {
        showarea = (wxTextCtrl*)FindWindow(XRCID("ID_SCROLLEDWINDOW"));

        vector<string>* crcresults = m_core.getcrcresults();
        for (; clicknum < crcresults->size(); clicknum++)
            showarea->AppendText(crcresults->at(clicknum) + "\n");
        showresult();
    }
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
 */

void mainwin::OnNextClick(wxCommandEvent& event)
{
    vector<string>* crcresults = m_core.getcrcresults();
    ((wxTextCtrl*)FindWindow(XRCID("ID_SCROLLEDWINDOW")))->AppendText(crcresults->at(clicknum++) + "\n");

    if (clicknum >= crcresults->size())
        showresult();
}


/*
 * Should we show tooltips?
 */

bool mainwin::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap mainwin::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin mainwin bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end mainwin bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon mainwin::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin mainwin icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end mainwin icon retrieval
}
