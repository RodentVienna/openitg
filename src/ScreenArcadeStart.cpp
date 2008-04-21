/* Basic screen functions */
#include "global.h"
#include "RageLog.h"
#include "RageUtil.h"
#include "ActorFrame.h"
#include "ThemeManager.h"
#include "ScreenManager.h"
#include "ScreenArcadeStart.h"

/* Serial number functions */
#include "MiscITG.h"

/* USBDevice tests */
#include "io/USBDevice.h"

/* Input board loading/testing */
#include "io/USBDriver.h"
#include "io/PIUIO.h"
#include "io/ITGIO.h"

/* InputHandler loading */
#include "RageInput.h"
#include "InputMapper.h"
#include "arch/InputHandler/InputHandler_Iow.h"
#include "arch/InputHandler/InputHandler_PIUIO.h"

#define NEXT_SCREEN	THEME->GetMetric( m_sName, "NextScreen" )

REGISTER_SCREEN_CLASS( ScreenArcadeStart );

ScreenArcadeStart::ScreenArcadeStart( CString sClassName ) : ScreenWithMenuElements( sClassName )
{
	LOG->Trace( "ScreenArcadeStart::ScreenArcadeStart()" );
}

void ScreenArcadeStart::Init()
{
	CString sGameSerial = GetSerialNumber();

	ScreenWithMenuElements::Init();

	m_Error.LoadFromFont( THEME->GetPathF( "ScreenArcadeStart", "error" ) );
	m_Error.SetName( "Error" );
	SET_XY_AND_ON_COMMAND( m_Error );
	this->AddChild( &m_Error );

	this->SortByDrawOrder();

	/* are there any errors with loading the I/O board? */
	m_bBoardError = !LoadHandler();

	if( !m_bBoardError )
		m_bUSBError = !Refresh();
}

ScreenArcadeStart::~ScreenArcadeStart()
{
	LOG->Trace( "ScreenArcadeStart::~ScreenArcadeStart()" );
}

void ScreenArcadeStart::Update( float fDeltaTime )
{
	Screen::Update( fDeltaTime );

	if( m_bFirstUpdate )
		m_Timer.Touch();

	if( !m_bBoardError )
	{
		m_bUSBError = !Refresh();

		// problem was fixed, or we timed out
		if( !m_bUSBError || m_Timer.Ago() > 10.0f )
		{
			this->PlayCommand( "Off" );
			StartTransitioning( SM_GoToNextScreen );
		}
	}

	m_Error.SetText( m_sMessage );
}

void ScreenArcadeStart::Input( const DeviceInput& DeviceI, const InputEventType type, const GameInput &GameI, const MenuInput &MenuI, const StyleInput &StyleI )
{
	if( type != IET_FIRST_PRESS && type != IET_SLOW_REPEAT )
		return;	// ignore

	Screen::Input( DeviceI, type, GameI, MenuI, StyleI );	// default handler
}

void ScreenArcadeStart::MenuStart( PlayerNumber pn )
{
	if(!IsTransitioning())
	{
		this->PlayCommand( "Off" );
		// if they can get here through means of keyboard, joystick/JPAC, the hell wid'it
		g_sInputType = "Self";
		StartTransitioning( SM_GoToNextScreen );
	}
}

void ScreenArcadeStart::HandleScreenMessage( const ScreenMessage SM )
{
	switch( SM )
	{
	case SM_GoToNextScreen:
	case SM_GoToPrevScreen:
		SCREENMAN->SetNewScreen( NEXT_SCREEN );
		break;
	}
}

void ScreenArcadeStart::MenuStart( PlayerNumber pn )
{
	if(!IsTransitioning())
	{
		this->PlayCommand( "Off" );
		StartTransitioning( SM_GoToNextScreen );		
	}
}

void ScreenArcadeStart::DrawPrimitives()
{
	Screen::DrawPrimitives();
}

bool ScreenArcadeStart::Refresh()
{
	float fTimer = 10.0f - m_Timer.Ago();

	if( !HubIsConnected() )
	{
		m_sMessage = ssprintf(
			"The memory card hub is not connected.\nPlease consult the service manual for details.\n\n"
			"Connect the USB hub to continue,\nor wait %.0f seconds for this warning to automatically dismiss.",
			fTimer );
		return false;
	}

	return true;
}

bool ScreenArcadeStart::LoadHandler()
{
	vector<USBDevice> vDevices;
	GetUSBDeviceList( vDevices );

	// this makes it so much easier to keep track of. --Vyhd
	enum Board { BOARD_NONE, BOARD_ITGIO, BOARD_PIUIO };

	Board iBoard = BOARD_NONE;
	
	for( unsigned i = 0; i < vDevices.size(); i++ )
	{
		if( vDevices[i].IsITGIO() )
			iBoard = BOARD_ITGIO;
		else if( vDevices[i].IsPIUIO() )
			iBoard = BOARD_PIUIO;

		// early abort if we found something
		if( iBoard != BOARD_NONE )
			break;
	}

	USBDriver *pDriver;

	if( iBoard == BOARD_ITGIO )
		pDriver = new ITGIO;
	else if( iBoard == BOARD_PIUIO )
		pDriver = new PIUIO;
	else
#ifdef ITG_ARCADE
	{
		m_sMessage = "The input/lights controller is not connected or is not receiving power.\n\nPlease consult the service manual.";
		return false;
	}
#else
	{
		/* HACK: return true if PC, even though it doesn't load. */
		LOG->Warn( "ScreenArcadeStart: I/O board not found. Continuing anyway..." );
		g_sInputType = "Home";
		return true;
	}
#endif

	/* Attempt a connection */
	if( !pDriver->Open() )
	{	
		m_sMessage = "The input/lights controller could not be initialized.\n\nPlease consult the service manual.";

		SAFE_DELETE( pDriver );
		return false;
	}

	pDriver->Close();
	SAFE_DELETE( pDriver );

	if( iBoard == BOARD_ITGIO )
		INPUTMAN->AddHandler( new InputHandler_Iow );
	else if( iBoard == BOARD_PIUIO )
		INPUTMAN->AddHandler( new InputHandler_PIUIO );
	else
		ASSERT(0);

	LOG->Trace( "Remapping joysticks after loading driver." );

	INPUTMAPPER->AutoMapJoysticksForCurrentGame();
	INPUTMAPPER->SaveMappingsToDisk();

	return true;
}

/*
 * Copyright (c) 2008 BoXoRRoXoRs
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
