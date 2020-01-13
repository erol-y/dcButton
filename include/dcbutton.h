/////////////////////////////////////////////////////////////////////////////
// Name:        dcbutton.h
// Purpose:     Dual case button declaration on wxButton
// Author:      erol-y
// Revision:    v1.0 (First public release)
// Created:     01/02/2020
// Copyright:   (c) erol-y
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DCBUTTON_H_INCLUDED
#define DCBUTTON_H_INCLUDED

#include <wx/button.h>

/// At least, we need...
#if wxCHECK_VERSION(2,9,1)

enum dcButtonCase{
    DC_Case_One,
    DC_Case_Two
};


struct dcButtonObject
{
    wxString label;

    wxBitmap bitmap;

	wxEventFunction func;

    dcButtonObject()
    : bitmap(wxNullBitmap), func(NULL)
    {}
};

class dcButton : public wxButton
{
public:
    /**
    * There is no special ctor (yet).
    * Create it like a wxButton.
    */
    dcButton();

    dcButton(wxWindow *parent,
             wxWindowID id,
             const wxString& label = wxEmptyString,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0,
             const wxValidator& validator = wxDefaultValidator,
             const wxString& name = wxButtonNameStr);

    ~dcButton();

    /// Switch to
    void SetActiveCase(dcButtonCase);

    dcButtonCase GetActiveCase() const { return m_case; }

    void SetLabel(dcButtonCase, const wxString&);

	inline void SetLabel(const wxString& state1, const wxString& state2)
	{
		SetLabel(DC_Case_One, state1); SetLabel(DC_Case_Two, state2);
	}

    void SetBitMap(dcButtonCase, const wxBitmap&, wxDirection = wxLEFT);

	inline void SetBitMap(const wxBitmap& bmp1, wxDirection dir1,
						  const wxBitmap& bmp2, wxDirection dir2)
	{
		SetBitMap(DC_Case_One, bmp1, dir1); SetBitMap(DC_Case_Two, bmp2, dir2);
	}

	inline void SetBitMap(const wxBitmap& bmp1, const wxBitmap& bmp2)
	{
		SetBitMap(DC_Case_One, bmp1); SetBitMap(DC_Case_Two, bmp2);
	}

	template <typename T, typename A>
	void SetEventFunction(dcButtonCase cs, void (T::*f)(A&))
    {
        if(cs == DC_Case_One)
        {
#if wxCHECK_VERSION(3,1,2)
            m_objOne->func = wxEventFunctionCast(static_cast<void (wxEvtHandler::*)(A&)>(f));
#else
            m_objOne->func = reinterpret_cast<wxEventFunction>(f);
#endif // wxCHECK_VERSION
        }
        else
        {
#if wxCHECK_VERSION(3,1,2)
            m_objTwo->func = wxEventFunctionCast(static_cast<void (wxEvtHandler::*)(A&)>(f));
#else
            m_objTwo->func = reinterpret_cast<wxEventFunction>(f);
#endif // wxCHECK_VERSION
        }
    }

	template <typename T1, typename A1, typename T2, typename A2>
	void SetEventFunction(void (T1::*func1)(A1&), void (T2::*func2)(A2&))
	{
		SetEventFunction(DC_Case_One, func1); SetEventFunction(DC_Case_Two, func2);
	}

	/**
	* It is a batch method to set props.
	* If object is null, it will reset props.
	* However, it would NOT be affected until case had been realized.
	*/
    void dcSetObject(dcButtonCase, dcButtonObject *);

    /**
    * Use it to set props of current case.
    * If object is null, it will reset props.
    */
    void SetActiveObject(dcButtonObject *);

    void Connect();

    void Disconnect();

private:
    // Active case.
    dcButtonCase m_case;

    bool m_linked;

    dcButtonObject * m_objOne;

    dcButtonObject * m_objTwo;

    void Init();

	void dcEventFunction(wxCommandEvent& event);

	wxDECLARE_NO_COPY_CLASS(dcButton);
};

#endif // wxCHECK_VERSION

#endif // DCBUTTON_H_INCLUDED
