#include <v8.h>
#include <node.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <string>
#include <string.h>

#define THROW(message) ThrowException(Exception::TypeError(String::New(message)))

using namespace node;
using namespace v8;

//that's a test
struct user_data
{
  char *line;
};

static Handle<Value> ftok(const Arguments& args)
{
  HandleScope scope;
  if(args.Length() < 2) return THROW("usage ftok(pathname,progid)");
  if(!args[0]->IsString()) return THROW("pathname must be an string");
  if(!args[1]->IsInt32()) return THROW("progid must be an integer");
  String::Utf8Value pathname(args[0]);
  int progid = args[1]->Int32Value();
  return(scope.Close(Integer::New(ftok(*pathname,progid))));
}

static Handle<Value> msgget(const Arguments &args)
{
  HandleScope scope;
  if(args.Length() < 2) return THROW("usage msgget(key,flags)");
  if(!args[0]->IsInt32()) return THROW("key must be an integer");
  if(!args[1]->IsInt32()) return THROW("flags must be an integer");
  int key = args[0]->Int32Value();
  int flags = args[1]->Int32Value();
  return(scope.Close(Integer::New(msgget(key,flags))));
}

static Handle<Value> msgsnd(const Arguments &args)
{
  HandleScope scope;
  if(args.Length() < 2) return THROW("usage msgsnd(msgid,message)");
  if(!args[0]->IsInt32()) return THROW("msgid must be an integer");
  if(!args[1]->IsString()) return THROW("message must be an string");
  int msgid = args[0]->Int32Value();
  String::Utf8Value message(args[1]);
  struct user_data udata;
  udata.line = strdup(*message);
  return(scope.Close(Integer::New(msgsnd(msgid,&udata, sizeof(struct user_data) - sizeof(long), 0))));
}

extern "C" {
  static void init(Handle<Object> target)
  {
    NODE_SET_METHOD(target, "ftok", ftok);
    NODE_SET_METHOD(target, "msgget", msgget);
    NODE_SET_METHOD(target, "msgsnd",msgsnd);
  }

  NODE_MODULE(svipc, init);
}