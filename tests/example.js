#!/usr/bin/env node
//#define IPC_CREAT  00001000   /* create if key is nonexistent */
//#define IPC_EXCL   00002000   /* fail if key exists */
//#define IPC_NOWAIT 00004000   /* return error on wait */
svipc = require('../svipc');

function ord(str)
{
	return(str.charCodeAt(0));
}

key = svipc.ftok('/tmp',ord('X'));
msgid = svipc.msgget(key,0666|00001000); //IPC_CREAT
//console.log(msgid);
svipc.msgsnd(msgid,"myfoobar");
