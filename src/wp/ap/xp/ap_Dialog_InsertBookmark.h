/* AbiWord
 * Copyright (C) 2000 AbiSource, Inc.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */

#ifndef AP_DIALOG_INSERTBOOKMARK_H
#define AP_DIALOG_INSERTBOOKMARK_H

#include "xap_Dialog.h"
#include "ut_xml.h"
#include "fv_View.h"
#include "pd_Document.h"
#include "ut_string.h"

#define BOOKMARK_SIZE_LIMIT 30
class XAP_Frame;

class AP_Dialog_InsertBookmark : public XAP_Dialog_NonPersistent
{
public:
	AP_Dialog_InsertBookmark(XAP_DialogFactory * pDlgFactory,
			     XAP_Dialog_Id id);
	virtual ~AP_Dialog_InsertBookmark(void);

	virtual void		 runModal(XAP_Frame * pFrame) = 0;

	typedef enum { a_OK=0, a_CANCEL=1 } tAnswer;

	tAnswer				getAnswer(void) const;
	void            	setAnswer(tAnswer a);
	UT_uint32			getExistingBookmarksCount() const;
	const XML_Char *	getNthExistingBookmark(UT_uint32 n) const;
	const XML_Char *	getBookmark() const;
	void				setBookmark(const XML_Char * mark);
	void				setDoc(FV_View * pView);
	
private:
	PD_Document *		m_pDoc;
	
	AP_Dialog_InsertBookmark::tAnswer	m_answer;
	XML_Char			m_pBookmark[BOOKMARK_SIZE_LIMIT + 1];
};

#endif /* AP_DIALOG_TOGGLECASE_H */
