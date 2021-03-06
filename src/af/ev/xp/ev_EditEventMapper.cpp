/* AbiSource Program Utilities
 * Copyright (C) 1998 AbiSource, Inc.
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  
 * 02110-1301 USA.
 */

#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ut_types.h"
#include "ev_EditMethod.h"
#include "ev_EditBinding.h"
#include "ev_EditEventMapper.h"


EV_EditEventMapper::EV_EditEventMapper(EV_EditBindingMap * pebm)
{
	UT_ASSERT(pebm);
	m_pebmTopLevel = pebm;

	m_pebmInProgress = nullptr;
}

EV_EditEventMapperResult EV_EditEventMapper::Mouse(EV_EditBits eb,
												   EV_EditMethod ** ppEM)
{
	UT_ASSERT(ppEM);

	if (!m_pebmInProgress)
		m_pebmInProgress = m_pebmTopLevel;

	EV_EditBinding * peb = m_pebmInProgress->findEditBinding(eb);
	if (!peb)							// bogus key
	{
		EV_EditEventMapperResult r = (  (m_pebmInProgress==m_pebmTopLevel)
									  ? EV_EEMR_BOGUS_START
									  : EV_EEMR_BOGUS_CONT);
		m_pebmInProgress = nullptr;
		return r;
	}

	EV_EditBindingType t = peb->getType();
	switch (t)
	{
	case EV_EBT_PREFIX:
		m_pebmInProgress = peb->getMap();
		UT_ASSERT(m_pebmInProgress);
		return EV_EEMR_INCOMPLETE;

	case EV_EBT_METHOD:
		*ppEM = peb->getMethod();
		m_pebmInProgress = nullptr;
		return EV_EEMR_COMPLETE;

	default:
		UT_ASSERT(0);
		m_pebmInProgress = nullptr;
		return EV_EEMR_BOGUS_START;
	}
}

EV_EditEventMapperResult EV_EditEventMapper::Keystroke(EV_EditBits eb,
													   EV_EditMethod ** ppEM)
{
	UT_ASSERT(ppEM);

	if (!m_pebmInProgress)
		m_pebmInProgress = m_pebmTopLevel;

	EV_EditBinding * peb = m_pebmInProgress->findEditBinding(eb);
	if (!peb)							// bogus key
	{
		EV_EditEventMapperResult r = (  (m_pebmInProgress==m_pebmTopLevel)
									  ? EV_EEMR_BOGUS_START
									  : EV_EEMR_BOGUS_CONT);
		m_pebmInProgress = nullptr;
		return r;
	}

	EV_EditBindingType t = peb->getType();
	switch (t)
	{
	case EV_EBT_PREFIX:
		m_pebmInProgress = peb->getMap();
		UT_ASSERT(m_pebmInProgress);
		return EV_EEMR_INCOMPLETE;

	case EV_EBT_METHOD:
		*ppEM = peb->getMethod();
		m_pebmInProgress = nullptr;
		return EV_EEMR_COMPLETE;

	default:
		UT_ASSERT(0);
		m_pebmInProgress = nullptr;
		return EV_EEMR_BOGUS_START;
	}
}

const char * EV_EditEventMapper::getShortcutFor(const EV_EditMethod * pEM) const
{
	UT_ASSERT(pEM);

	// lookup the keyboard shortcut bound to pEM, if any

	return m_pebmTopLevel->getShortcutFor(pEM);
}
