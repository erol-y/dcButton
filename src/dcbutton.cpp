/////////////////////////////////////////////////////////////////////////////
// Name:        dcbutton.cpp
// Purpose:     Dual case button declaration on wxButton
// Author:      erol-y
// Revision:    v1.0 (First public release)
// Created:     01/02/2020
// Copyright:   (c) erol-y
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "dcbutton.h"

dcButton::dcButton() : wxButton()
{
    Init();
}

dcButton::dcButton(wxWindow* parent,
                   wxWindowID id,
                   const wxString& label,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style,
                   const wxValidator& validator,
                   const wxString& name)
             : wxButton(parent, id, label, pos, size, style, validator, name)
{
    Init();

    m_objOne->label = label;

    Connect();
}

dcButton::~dcButton()
{
    wxDELETE(m_objOne);

    wxDELETE(m_objTwo);
}

void dcButton::Init()
{
    m_case = DC_Case_One;

    m_linked = false;

    m_objOne = new dcButtonObject();

    m_objTwo = new dcButtonObject();
}

void dcButton::SetActiveCase(dcButtonCase cs)
{
    if(cs == DC_Case_One)
    {
        wxButton::SetLabel(m_objOne->label);
        wxButton::SetBitmap(m_objOne->bitmap);
    }
    else
    {
         wxButton::SetLabel(m_objTwo->label);
         wxButton::SetBitmap(m_objTwo->bitmap);
    }

    m_case = cs;
}

void dcButton::SetLabel(dcButtonCase cs, const wxString& label)
{
    if(cs == DC_Case_One)
    {
        m_objOne->label = label;
        if(m_case == DC_Case_One)
            wxButton::SetLabel(label);
    }
    else
    {
        m_objTwo->label = label;
        if(m_case == DC_Case_Two)
            wxButton::SetLabel(label);
    }
}

void dcButton::SetBitMap(dcButtonCase cs, const wxBitmap& bmp, wxDirection dir)
{
    if(cs == DC_Case_One)
    {
        m_objOne->bitmap = bmp;
        if(m_case == DC_Case_One)
            wxButton::SetBitmap(bmp, dir);
    }
    else
    {
        m_objTwo->bitmap = bmp;
        if(m_case == DC_Case_Two)
            wxButton::SetBitmap(bmp, dir);
    }
}

void dcButton::Connect()
{
    if(!m_linked)
    {
        wxButton::Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                          wxCommandEventHandler(dcButton::dcEventFunction),
                          NULL,
                          this);

         m_linked = true;
    }
}

void dcButton::Disconnect()
{
    if(m_linked)
    {
        wxButton::Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                             wxCommandEventHandler(dcButton::dcEventFunction),
                             NULL,
                             this);

        m_linked = false;
    }
}

void dcButton::dcSetObject(dcButtonCase cs, dcButtonObject* obj)
{
    dcButtonObject * m_obj = NULL;

    if(obj == NULL)
        m_obj = new dcButtonObject();
    else
        m_obj = obj;

    if(cs == DC_Case_One)
    {
        wxDELETE(m_objOne);
        m_objOne = m_obj;
    }
    else
    {
        wxDELETE(m_objTwo);
        m_objTwo = m_obj;
    }
}

void dcButton::SetActiveObject(dcButtonObject* obj)
{
    dcSetObject(m_case, obj);

    /// Propagation
    SetActiveCase(m_case);
}

void dcButton::dcEventFunction(wxCommandEvent& event)
{
    wxEventFunction m_func;
	wxEvtHandler * handler = GetParent()->GetEventHandler();

	 if(m_case == DC_Case_One)
     {
        if (m_objOne->func != NULL)
		{
			m_func = static_cast<wxEventFunction>(m_objOne->func);
			(handler->*m_func)(event);
		}
		SetActiveCase(DC_Case_Two);
     }
     else
     {
         if(m_objTwo->func != NULL)
         {
             m_func = static_cast<wxEventFunction>(m_objTwo->func);
			(handler->*m_func)(event);
         }
         SetActiveCase(DC_Case_One);
     }
}
