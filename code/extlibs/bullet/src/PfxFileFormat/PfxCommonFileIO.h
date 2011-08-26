/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_COMMON_FILE_IO_H__
#define __PFX_COMMON_FILE_IO_H__

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "PfxCommonTypes.h"

#define INDENT_MAX		32
#define TAG_STR_MAX		32
#define LINEBUFF_MAX	256

///////////////////////////////////////////////////////////////////////////////
// File IO

class PfxCommonFileIO
{
protected:
	FILE	*mFp;

public:
	PfxCommonFileIO() {}
	virtual ~PfxCommonFileIO() {}

	virtual bool open(const char *filename) = 0;
	inline void close();
	inline void reset();
	inline bool isEof();
};

inline
void PfxCommonFileIO::close()
{
	if(mFp) fclose(mFp);
}

inline
void PfxCommonFileIO::reset()
{
	if(mFp) rewind(mFp);
}

inline
bool PfxCommonFileIO::isEof()
{
	return feof(mFp)!=0;
}

///////////////////////////////////////////////////////////////////////////////
// File Reader

class PfxCommonFileReader : public PfxCommonFileIO
{
private:
	char	mTag[TAG_STR_MAX];
	char	mLineBuff[LINEBUFF_MAX];

	bool isSame(char *s1,char *s2);
	bool isToken(char c);

	void getLine(char *line,int n);
	void readTag(char *line,char *tag);

public:
	virtual bool open(const char *filename);

	bool getNextTag();
	bool isSameTag(char *tag);
	void readString(char *str,int n);
	void readUInt32(PfxUInt32 &value);
	void readBool(bool &value);
	void readInt32(PfxInt32 &value);
	void readIndex3(PfxUInt32 &value0,PfxUInt32 &value1,PfxUInt32 &value2);
	void readFloat3(PfxFloat &value0,PfxFloat &value1,PfxFloat &value2);
	void readFloat(PfxFloat &value);
	void readFloat3(PfxFloat3 &value);
	void readFloat4(PfxFloat4 &value);
	void readMatrix3(PfxMatrix3 &value);
};

///////////////////////////////////////////////////////////////////////////////
// File Writer

class PfxCommonFileWriter : public PfxCommonFileIO
{
private:
	int		mIndentCnt;
	char	mIndents[INDENT_MAX];

	void indentUp();
	void indentDown();

public:
	virtual bool open(const char *filename);

	void writeOpenTag(const char *name);
	void writeCloseTag();
	void writeString(const char *name,const char *str);
	void writeBool(const char *name,bool value);
	void writeUInt32(const char *name,PfxUInt32 value);
	void writeInt32(const char *name,PfxInt32 value);
	void writeIndex3(const char *name,PfxUInt32 value0,PfxUInt32 value1,PfxUInt32 value2);
	void writeFloat3(const char *name,PfxFloat value0,PfxFloat value1,PfxFloat value2);
	void writeFloat(const char *name,PfxFloat value);
	void writeFloat3(const char *name,const PfxFloat3 &value);
	void writeFloat4(const char *name,const PfxFloat4 &value);
	void writeMatrix3(const char *name,const PfxMatrix3 &value);
};

#endif /* __PFX_FILE_IO_H__ */
