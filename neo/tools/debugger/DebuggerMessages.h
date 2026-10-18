/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#ifndef DEBUGGERMESSAGES_H_
#define DEBUGGERMESSAGES_H_

enum EDebuggerMessage
{
	DBMSG_UNKNOWN,
	DBMSG_CONNECT,
	DBMSG_CONNECTED,
	DBMSG_DISCONNECT,
	DBMSG_ADDBREAKPOINT,
	DBMSG_REMOVEBREAKPOINT,
	DBMSG_HITBREAKPOINT,
	DBMSG_RESUME,
	DBMSG_RESUMED,
	DBMSG_BREAK,
	DBMSG_PRINT,
	DBMSG_INSPECTVARIABLE,
	DBMSG_INSPECTCALLSTACK,
	DBMSG_INSPECTTHREADS,
	DBMSG_STEPOVER,
	DBMSG_STEPINTO,
	DBMSG_INSPECTSCRIPTS,
	DBMSG_EXECCOMMAND,
	// Protocol 2. Sent by the server after it connected: int protocol version, int capabilities
	// (DBCAP_*). A client that doesn't know these messages ignores them, and the ones above
	// keep their meaning.
	DBMSG_VERSION,
	// step until the stopped thread returned from the function it is stopped in
	DBMSG_STEPOUT,
	// client: int flags (DBERR_*): which of the scripts' errors and warnings stop the game
	DBMSG_BREAKONERRORS,
	// server, right before the DBMSG_BREAK of a stop at a script error or warning:
	// byte 1 for an error (the game drops the map once resumed), 0 for a warning; string message
	DBMSG_SCRIPTERROR,

	// While stopped, about any thread (DBMSG_INSPECTTHREADS' numbers), the stopped one too.
	// A frame is named by its scope depth: -1 for the function the thread is in, else the
	// index of the function's entry on the thread's call stack.

	// client: int thread; server: int thread, then as DBMSG_INSPECTCALLSTACK
	// (a short depth of 0 when there is no such thread)
	DBMSG_INSPECTTHREADCALLSTACK,
	// client: int thread, short scope depth; server: int thread, short scope depth,
	// short count, then count times string name, string value, byte kind (DBVAR_*)
	DBMSG_INSPECTVARIABLES,
	// client: int thread, short scope depth, string name, string value (as the server writes
	// values); server: int thread, short scope depth, string name, byte 1 if set, then the
	// value it has now (or why it was not set)
	DBMSG_SETVARIABLE,
	// client: string entity name; server: string entity name, then as DBMSG_INSPECTVARIABLES'
	// count and variables (DBVAR_FIELD: its script object's, DBVAR_SPAWNARG)
	DBMSG_INSPECTENTITY,
	// client: int line: the stopped thread goes on from that line of the function it is in;
	// server: int line, 0 when it can't; int the statement it goes on from
	DBMSG_SETNEXTSTATEMENT
};

// DBMSG_VERSION's protocol version and capabilities
const int DEBUGGER_PROTOCOL_VERSION = 2;
enum {
	DBCAP_STEPOUT = 1,				// DBMSG_STEPOUT
	DBCAP_INSPECT = 2,				// the game answers DBMSG_INSPECTTHREADCALLSTACK, DBMSG_INSPECTVARIABLES,
									// DBMSG_SETVARIABLE, DBMSG_INSPECTENTITY, DBMSG_SETNEXTSTATEMENT
	DBCAP_BREAKONERRORS = 4			// DBMSG_BREAKONERRORS, DBMSG_SCRIPTERROR
};

// DBMSG_BREAKONERRORS' flags
enum {
	DBERR_ERRORS = 1,				// script errors (idInterpreter::Error)
	DBERR_WARNINGS = 2				// script warnings (idInterpreter::Warning)
};

// DBMSG_INSPECTVARIABLES' and DBMSG_INSPECTENTITY's kinds
enum {
	DBVAR_LOCAL = 0,				// a parameter or local variable of the function
	DBVAR_FIELD = 1,				// a field of the object the function is a method of (or the entity's)
	DBVAR_SPAWNARG = 2				// one of an entity's spawn args
};

#endif // DEBUGGER_MESSAGES_H_