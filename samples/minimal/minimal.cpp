/////////////////////////////////////////////////////////////////////////////
// Name:        Minimal
// Purpose:     Minimal sample of dcButton
// Author:      erol-y
// Revision:    v1.0 (First public release)
// Created:     01/02/2020
// Copyright:   (c) erol-y
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


#include "dcbutton.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
	dcButton * m_btnSimple;

	dcButton * m_btnControl;

	/// Helper function for loading and resizing button icons.
    wxBitmap LoadBitmap(const wxString& filepath);

    /// Separated functions for each case
	void CaseOneEvtFunc(wxCommandEvent& event);
	void CaseTwoEvtFunc(wxCommandEvent& event);

	/// Unified function for both case.
	void UnifiedEvtFunc(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    wxImage::AddHandler(new wxPNGHandler);

    MyFrame *frame = new MyFrame("Minimal Dual Case Button Sample");

    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

    m_btnSimple = new dcButton(this, wxID_ANY);

    m_btnSimple->SetLabel(wxT("State One"), wxT("State Two"));

    /// Linking separated event functions to m_btnSimple.
    m_btnSimple->SetEventFunction(&MyFrame::CaseOneEvtFunc, &MyFrame::CaseTwoEvtFunc);
//    m_dsButton->Connect();

    wxSizer * topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(m_btnSimple, 0, wxALL, 5);

    wxStaticText * m_sText2 = new wxStaticText(this, wxID_ANY, wxT("Control Button:"));
    topSizer->Add(m_sText2, 0, wxALL, 5);

    m_btnControl = new dcButton(this, wxID_ANY);

    m_btnControl->SetBitMap(LoadBitmap(wxT("delete.png")), LoadBitmap(wxT("power.png")));

    m_btnControl->SetBackgroundColour(GetBackgroundColour());

    m_btnControl->SetWindowStyle(wxBORDER_NONE | wxBU_NOTEXT);

    /// Linking Unified event function.
	m_btnControl->SetEventFunction(&MyFrame::UnifiedEvtFunc, &MyFrame::UnifiedEvtFunc);
//    m_dsButton2->Connect();

    topSizer->Add(m_btnControl, 0, wxALL, 5);

    SetSizer(topSizer);

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
#endif // wxUSE_STATUSBAR
}

wxBitmap MyFrame::LoadBitmap(const wxString& filepath)
{
    wxImage image(filepath);
    if(image.IsOk())
    {
        int w =  image.GetWidth();
        w > 32 ? w = 32 : w;

        int h = image.GetHeight();
        h > 32 ? h = 32 : h;

        image.Rescale(w, h);

        return wxBitmap(image);
    }

    return wxNullBitmap;
}

void MyFrame::CaseOneEvtFunc(wxCommandEvent& event)
{
    wxMessageBox(wxT("Comes From <CASE ONE> Event Function."),
                 wxT("Button Event"));

    event.Skip();
}

void MyFrame::CaseTwoEvtFunc(wxCommandEvent& event)
{
     wxMessageBox(wxT("Comes From <CASE TWO> Event Function."),
                  wxT("Button Event"));

    event.Skip();
}

void MyFrame::UnifiedEvtFunc(wxCommandEvent& event)
{
    if (m_btnControl->GetActiveCase() == DC_Case_One)
	{
		m_btnSimple->Disable();
#if wxUSE_STATUSBAR
        SetStatusText("Button disabled", 1);
#endif // wxUSE_STATUSBAR
	}
	else
	{
		m_btnSimple->Enable();
#if wxUSE_STATUSBAR
        SetStatusText("Button enabled", 1);
#endif // wxUSE_STATUSBAR
	}
}
