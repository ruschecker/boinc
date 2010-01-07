// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "ViewNotifications.h"
#endif

#include "stdwx.h"
#include "BOINCGUIApp.h"
#include "BOINCBaseFrame.h"
#include "MainDocument.h"
#include "AdvancedFrame.h"
#include "BOINCTaskCtrl.h"
#include "ViewNotifications.h"
#include "Events.h"
#include "error_numbers.h"


#include "res/mess.xpm"


IMPLEMENT_DYNAMIC_CLASS(CViewNotifications, CBOINCBaseView)

BEGIN_EVENT_TABLE (CViewNotifications, CBOINCBaseView)
END_EVENT_TABLE ()


CViewNotifications::CViewNotifications()
{}


CViewNotifications::CViewNotifications(wxNotebook* pNotebook) :
    CBOINCBaseView(pNotebook)
{
    CTaskItemGroup* pGroup = NULL; 
    CTaskItem*      pItem = NULL; 

    //
    // Setup View
    //
    wxFlexGridSizer* itemFlexGridSizer = new wxFlexGridSizer(2, 0, 0);
    wxASSERT(itemFlexGridSizer);

    itemFlexGridSizer->AddGrowableRow(0);
    itemFlexGridSizer->AddGrowableCol(1);
    
    m_pTaskPane = new CBOINCTaskCtrl(this, ID_TASK_NOTIFICATIONSVIEW, DEFAULT_TASK_FLAGS);
    wxASSERT(m_pTaskPane);

	m_pHtmlPane = new wxHtmlWindow(this, ID_HTML_NOTIFICATIONSVIEW, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO | wxHSCROLL | wxVSCROLL);
	wxASSERT(m_pHtmlPane);

    itemFlexGridSizer->Add(m_pTaskPane, 1, wxGROW|wxALL, 1);
    itemFlexGridSizer->Add(m_pHtmlPane, 1, wxGROW|wxALL, 1);

    SetSizer(itemFlexGridSizer);

    Layout();

    pGroup = new CTaskItemGroup( _("News Feeds") ); 
    m_TaskGroups.push_back( pGroup ); 

    pItem = new CTaskItem( 
        _("BOINC"), 
        _("Display the latest news about BOINC"), 
        ID_TASK_NEWS_BOINC  
    ); 
    pGroup->m_Tasks.push_back( pItem ); 

    m_TaskGroups.push_back( pGroup ); 

    // Create Task Pane Items
    m_pTaskPane->UpdateControls();
}


CViewNotifications::~CViewNotifications() {
}


wxString& CViewNotifications::GetViewName() {
    static wxString strViewName(wxT("Notices"));
    return strViewName;
}


wxString& CViewNotifications::GetViewDisplayName() {
    static wxString strViewName(_("Notices"));
    return strViewName;
}


const char** CViewNotifications::GetViewIcon() {
    return mess_xpm;
}


const int CViewNotifications::GetViewRefreshRate() {
    return 10;
}

const int CViewNotifications::GetViewCurrentViewPage() {
     return VW_NOTIF;
}


bool CViewNotifications::OnSaveState(wxConfigBase* WXUNUSED(pConfig)) {
    return true;
}


bool CViewNotifications::OnRestoreState(wxConfigBase* WXUNUSED(pConfig)) {
    return true;
}


void CViewNotifications::OnListRender( wxTimerEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewNotifications::OnListRender - Function Begin"));

    CMainDocument*  pDoc   = wxGetApp().GetDocument();
    wxString strHTML;
    wxString strItems;
    wxString strTemp;
    wxDateTime dtBuffer;
    NOTICE* pNotice = NULL;
    int iNoticeCount = 0;
    unsigned int iNoticeIndex = 0;


    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));
	wxASSERT(m_pHtmlPane);

    iNoticeCount = pDoc->GetNoticeCount();

    if (iNoticeCount == -1) {
        
        strItems +=   _("Retrieving notices now...");

    } else {

        // Pre-allocate buffer size so string concat is much faster
        strItems.Alloc(4096*iNoticeCount);

        for (iNoticeIndex = 0; iNoticeIndex < (unsigned int)iNoticeCount; iNoticeIndex++) {
            pNotice = pDoc->notice(iNoticeIndex);

            if (pNotice) {

                strItems += wxT("<p></p>");
                strItems += wxT("<table border=2 width=100%%>");
                strItems += wxT("  <tr>");
                strItems += wxT("    <td>");

                strItems +=   _("Diag: ");
                strTemp.Printf(wxT("index(%d)/seqno(%d)"), iNoticeIndex, pNotice->seqno);
                strItems += strTemp;

                strItems += wxT("      <br>");
                strItems +=   _("Title: ");

                strItems += wxString(pNotice->title, wxConvUTF8);

                strItems += wxT("      <br>");
                strItems +=   _("Date: ");

                dtBuffer.Set((time_t)pNotice->arrival_time);
                strItems += dtBuffer.Format();

                strItems += wxT("    </td>");
                strItems += wxT("  </tr>");
                strItems += wxT("  <tr>");
                strItems += wxT("    <td>");
                strItems += wxString(pNotice->description.c_str(), wxConvUTF8);
                strItems += wxT("    </td>");
                strItems += wxT("  </tr>");
                strItems += wxT("</table>");
                strItems += wxT("<p></p>");

            }
        }
    }

    strHTML  = wxT("<html>");
    strHTML += wxT("<head>");
    strHTML += wxT("</head>");
    strHTML += wxT("<body>");
    strHTML += strItems;
    strHTML += wxT("</body>");
    strHTML += wxT("</html>");

    m_pHtmlPane->SetPage( strHTML );

    wxLogTrace(wxT("Function Start/End"), wxT("CViewNotifications::OnListRender - Function End"));
}
