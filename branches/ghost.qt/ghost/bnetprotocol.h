/*

   Copyright [2008] [Trevor Hogan]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   CODE PORTED FROM THE ORIGINAL GHOST PROJECT: http://ghost.pwner.org/

*/

#ifndef BNETPROTOCOL_H
#define BNETPROTOCOL_H

//
// CBNETProtocol
//

#include "includes.h"
#define BNET_HEADER_CONSTANT 255

class CIncomingGameHost;
class CIncomingChatEvent;
class CIncomingFriendList;
class CIncomingClanList;

class CBNETProtocol
{
public:
	enum Protocol {
		SID_NULL					= 0,	// 0x0
		SID_STOPADV					= 2,	// 0x2
		SID_GETADVLISTEX			= 9,	// 0x9
		SID_ENTERCHAT				= 10,	// 0xA
		SID_JOINCHANNEL				= 12,	// 0xC
		SID_CHATCOMMAND				= 14,	// 0xE
		SID_CHATEVENT				= 15,	// 0xF
		SID_CHECKAD					= 21,	// 0x15
		SID_STARTADVEX3				= 28,	// 0x1C
		SID_DISPLAYAD				= 33,	// 0x21
		SID_NOTIFYJOIN				= 34,	// 0x22
		SID_PING					= 37,	// 0x25
		SID_LOGONRESPONSE			= 41,	// 0x29
		SID_NETGAMEPORT				= 69,	// 0x45
		SID_AUTH_INFO				= 80,	// 0x50
		SID_AUTH_CHECK				= 81,	// 0x51
		SID_AUTH_ACCOUNTLOGON		= 83,	// 0x53
		SID_AUTH_ACCOUNTLOGONPROOF	= 84,	// 0x54
		SID_WARDEN					= 94,	// 0x5E
		SID_FRIENDSLIST				= 101,	// 0x65
		SID_FRIENDSUPDATE			= 102,	// 0x66
		SID_CLANMEMBERLIST			= 125,	// 0x7D
		SID_CLANMEMBERSTATUSCHANGE	= 127	// 0x7F
	};

	enum KeyResult {
		KR_GOOD				= 0,
		KR_OLD_GAME_VERSION	= 256,
		KR_INVALID_VERSION	= 257,
		KR_ROC_KEY_IN_USE	= 513,
		KR_TFT_KEY_IN_USE	= 529
	};

	enum IncomingChatEvent {
		EID_SHOWUSER			= 1,	// received when you join a channel (includes users in the channel and their information)
		EID_JOIN				= 2,	// received when someone joins the channel you're currently in
		EID_LEAVE				= 3,	// received when someone leaves the channel you're currently in
		EID_WHISPER				= 4,	// received a whisper message
		EID_TALK				= 5,	// received when someone talks in the channel you're currently in
		EID_BROADCAST			= 6,	// server broadcast
		EID_CHANNEL				= 7,	// received when you join a channel (includes the channel's name, flags)
		EID_USERFLAGS			= 9,	// user flags updates
		EID_WHISPERSENT			= 10,	// sent a whisper message
		EID_CHANNELFULL			= 13,	// channel is full
		EID_CHANNELDOESNOTEXIST	= 14,	// channel does not exist
		EID_CHANNELRESTRICTED	= 15,	// channel is restricted
		EID_INFO				= 18,	// broadcast/information message
		EID_ERROR				= 19,	// error message
		EID_EMOTE				= 23	// emote
	};

private:
	QByteArray m_ClientToken;			// set in constructor
	QByteArray m_LogonType;				// set in RECEIVE_SID_AUTH_INFO
	QByteArray m_ServerToken;			// set in RECEIVE_SID_AUTH_INFO
	QByteArray m_MPQFileTime;			// set in RECEIVE_SID_AUTH_INFO
	QByteArray m_IX86VerFileName;		// set in RECEIVE_SID_AUTH_INFO
	QByteArray m_ValueStringFormula;		// set in RECEIVE_SID_AUTH_INFO
	QByteArray m_KeyState;				// set in RECEIVE_SID_AUTH_CHECK
	QByteArray m_KeyStateDescription;	// set in RECEIVE_SID_AUTH_CHECK
	QByteArray m_Salt;					// set in RECEIVE_SID_AUTH_ACCOUNTLOGON
	QByteArray m_ServerPublicKey;		// set in RECEIVE_SID_AUTH_ACCOUNTLOGON
	QByteArray m_UniqueName;				// set in RECEIVE_SID_ENTERCHAT

public:
	CBNETProtocol( );
	~CBNETProtocol( );

	QByteArray GetClientToken( )				{ return m_ClientToken; }
	QByteArray GetLogonType( )				{ return m_LogonType; }
	QByteArray GetServerToken( )				{ return m_ServerToken; }
	QByteArray GetMPQFileTime( )				{ return m_MPQFileTime; }
	QByteArray GetIX86VerFileName( )			{ return m_IX86VerFileName; }
	QString GetIX86VerFileNameString( )		{ return m_IX86VerFileName; }
	QByteArray GetValueStringFormula( )		{ return m_ValueStringFormula; }
	QString GetValueStringFormulaString( )	{ return m_ValueStringFormula; }
	QByteArray GetKeyState( )				{ return m_KeyState; }
	QString GetKeyStateDescription( )		{ return m_KeyStateDescription; }
	QByteArray GetSalt( )					{ return m_Salt; }
	QByteArray GetServerPublicKey( )			{ return m_ServerPublicKey; }
	QByteArray GetUniqueName( )				{ return m_UniqueName; }

	// receive functions

	bool RECEIVE_SID_NULL( QByteArray data );
	CIncomingGameHost *RECEIVE_SID_GETADVLISTEX( QByteArray data );
	bool RECEIVE_SID_ENTERCHAT( QByteArray data );
	CIncomingChatEvent *RECEIVE_SID_CHATEVENT( QByteArray data );
	bool RECEIVE_SID_CHECKAD( QByteArray data );
	bool RECEIVE_SID_STARTADVEX3( QByteArray data );
	QByteArray RECEIVE_SID_PING( QByteArray data );
	bool RECEIVE_SID_LOGONRESPONSE( QByteArray data );
	bool RECEIVE_SID_AUTH_INFO( QByteArray data );
	bool RECEIVE_SID_AUTH_CHECK( QByteArray data );
	bool RECEIVE_SID_AUTH_ACCOUNTLOGON( QByteArray data );
	bool RECEIVE_SID_AUTH_ACCOUNTLOGONPROOF( QByteArray data );
	QByteArray RECEIVE_SID_WARDEN( QByteArray data );
	QVector<CIncomingFriendList *> RECEIVE_SID_FRIENDSLIST( QByteArray data );
	QVector<CIncomingClanList *> RECEIVE_SID_CLANMEMBERLIST( QByteArray data );
	CIncomingClanList *RECEIVE_SID_CLANMEMBERSTATUSCHANGE( QByteArray data );

	// send functions

	QByteArray SEND_PROTOCOL_INITIALIZE_SELECTOR( );
	QByteArray SEND_SID_NULL( );
	QByteArray SEND_SID_STOPADV( );
	QByteArray SEND_SID_GETADVLISTEX( QString gameName );
	QByteArray SEND_SID_ENTERCHAT( );
	QByteArray SEND_SID_JOINCHANNEL( QString channel );
	QByteArray SEND_SID_CHATCOMMAND( QString command );
	QByteArray SEND_SID_CHECKAD( );
	QByteArray SEND_SID_STARTADVEX3( unsigned char state, QByteArray mapGameType, QByteArray mapFlags, QByteArray mapWidth, QByteArray mapHeight, QString gameName, QString hostName, uint32_t upTime, QString mapPath, QByteArray mapCRC, QByteArray mapSHA1, uint32_t hostCounter );
	QByteArray SEND_SID_NOTIFYJOIN( QString gameName );
	QByteArray SEND_SID_PING( QByteArray pingValue );
	QByteArray SEND_SID_LOGONRESPONSE( QByteArray clientToken, QByteArray serverToken, QByteArray passwordHash, QString accountName );
	QByteArray SEND_SID_NETGAMEPORT( uint16_t serverPort );
	QByteArray SEND_SID_AUTH_INFO( unsigned char ver, bool TFT, uint32_t localeID, QString countryAbbrev, QString country );
	QByteArray SEND_SID_AUTH_CHECK( bool TFT, QByteArray clientToken, QByteArray exeVersion, QByteArray exeVersionHash, QByteArray keyInfoROC, QByteArray keyInfoTFT, QString exeInfo, QString keyOwnerName );
	QByteArray SEND_SID_AUTH_ACCOUNTLOGON( QByteArray clientPublicKey, QString accountName );
	QByteArray SEND_SID_AUTH_ACCOUNTLOGONPROOF( QByteArray clientPasswordProof );
	QByteArray SEND_SID_WARDEN( QByteArray wardenResponse );
	QByteArray SEND_SID_FRIENDSLIST( );
	QByteArray SEND_SID_CLANMEMBERLIST( );

	// other functions

private:
	bool AssignLength( QByteArray &content );
	bool ValidateLength( QByteArray &content );
};

//
// CIncomingGameHost
//

class CIncomingGameHost
{
private:
	QByteArray m_IP;
	uint16_t m_Port;
	QString m_GameName;
	QByteArray m_HostCounter;

public:
	CIncomingGameHost( QByteArray &nIP, uint16_t nPort, QString nGameName, QByteArray &nHostCounter );
	~CIncomingGameHost( );

	QByteArray GetIP( )			{ return m_IP; }
	QString GetIPString( );
	uint16_t GetPort( )			{ return m_Port; }
	QString GetGameName( )		{ return m_GameName; }
	QByteArray GetHostCounter( )	{ return m_HostCounter; }
};

//
// CIncomingChatEvent
//

class CIncomingChatEvent
{
private:
	CBNETProtocol :: IncomingChatEvent m_ChatEvent;
	uint32_t m_Ping;
	QString m_User;
	QString m_Message;

public:
	CIncomingChatEvent( CBNETProtocol :: IncomingChatEvent nChatEvent, uint32_t nPing, QString nUser, QString nMessage );
	~CIncomingChatEvent( );

	CBNETProtocol :: IncomingChatEvent GetChatEvent( )	{ return m_ChatEvent; }
	uint32_t GetPing( )									{ return m_Ping; }
	QString GetUser( )									{ return m_User; }
	QString GetMessage( )								{ return m_Message; }
};

//
// CIncomingFriendList
//

class CIncomingFriendList
{
private:
	QString m_Account;
	unsigned char m_Status;
	unsigned char m_Area;
	QString m_Location;

public:
	CIncomingFriendList( QString nAccount, unsigned char nStatus, unsigned char nArea, QString nLocation );
	~CIncomingFriendList( );

	QString GetAccount( )		{ return m_Account; }
	unsigned char GetStatus( )	{ return m_Status; }
	unsigned char GetArea( )	{ return m_Area; }
	QString GetLocation( )		{ return m_Location; }
	QString GetDescription( );

private:
	QString ExtractStatus( unsigned char status );
	QString ExtractArea( unsigned char area );
	QString ExtractLocation( QString location );
};

//
// CIncomingClanList
//

class CIncomingClanList
{
private:
	QString m_Name;
	unsigned char m_Rank;
	unsigned char m_Status;

public:
	CIncomingClanList( QString nName, unsigned char nRank, unsigned char nStatus );
	~CIncomingClanList( );

	QString GetName( )			{ return m_Name; }
	QString GetRank( );
	QString GetStatus( );
	QString GetDescription( );
};

#endif