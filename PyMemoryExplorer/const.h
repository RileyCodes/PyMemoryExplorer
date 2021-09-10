#pragma once

#define LOG_ERRLEN 4
#define CODE_POSITION -1

#define MAX_INSTANCE_COUNT 500


enum class ErrorType
{
	Err_OK,
	Err_GetPy27ModuleAddress,
	Err_Py27DictDummy,
	Err_InterpreterState,
	Err_InterpreterState2,
	Err_Tstate_head,
	Err_FrameObject,
	Err_frameGlobal,
	Err_GCNotFound,
	Err_ReadGCTableFailed
};

struct SmallStringBuffer
{
	char buffer[600];
};

struct TinyStringBuffer
{
	char buffer[32];
};

struct SmallWStringBuffer
{
	wchar_t buffer[600];
};


enum class LogErrLevel
{
	Info,
	Warning,
	Error
};

enum class LogType
{
	TooManyInstance
};


enum class ObjectId
{
	GCTableObjs,
	DictEntries,
	DictEntries_Long,
	DictEntries_Int
};

struct GuradReport
{
	int Count;
	int id;
};

#define NUM_GENERATIONS 3
#define GEN_HEAD(n) ((pyPtr)&generations[n].head)
#define GEN_HEAD_X64(n) (&generations[n].head)
#define FROM_GC(g) ((pyPtr )(((pyPtr)g)+ sizeof(PyGC_Head)))
#define GC_BEGIN_ADDRESS 0x00;
#define DICT_FACT_NUM 5
#define GC_OBJECT_MAX   4000000
#define DATA_BUFFER_MAX 5242880


#define CHECK_IS_INITED \
	if(!this->isReady) return false; \
	if (this->remoteAddr == NULL) \
		return false;

struct ResultInfo
{
	ErrorType lastError = ErrorType::Err_OK;
};
