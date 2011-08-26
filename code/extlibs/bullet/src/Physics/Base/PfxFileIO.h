/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_FILE_IO_H__
#define __PFX_FILE_IO_H__

#include "Physics/Base/PhysicsCommon.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#define INDENT_MAX		32
#define TAG_STR_MAX		32
#define LINEBUFF_MAX	256

///////////////////////////////////////////////////////////////////////////////
// File IO

class PfxFileIO
{
protected:
	FILE	*mFp;

public:
	PfxFileIO() {}
	virtual ~PfxFileIO() {}

	virtual bool open(const char *filename) = 0;
	inline void close();
	inline void reset();
	inline bool isEof();
};

inline
void PfxFileIO::close()
{
	if(mFp) fclose(mFp);
}

inline
void PfxFileIO::reset()
{
	if(mFp) rewind(mFp);
}

inline
bool PfxFileIO::isEof()
{
	return feof(mFp)!=0;
}

///////////////////////////////////////////////////////////////////////////////
// File Reader

class PfxFileReader : public PfxFileIO
{
private:
	char	mTag[TAG_STR_MAX];
	char	mLineBuff[LINEBUFF_MAX];

	inline bool isSame(char *s1,char *s2);
	inline bool isToken(char c);

	inline void getLine(char *line,int n);
	inline void readTag(char *line,char *tag);

public:
	virtual bool open(const char *filename);

	inline bool getNextTag();
	inline bool isSameTag(char *tag);
	inline void readString(char *str,int n);
	inline void readUint32(uint32_t &value);
	inline void readBool(bool &value);
	inline void readInt32(int32_t &value);
	inline void readFloat(float &value);
	inline void readVector3(Vector3 &value);
	inline void readMatrix3(Matrix3 &value);
	inline void readQuat(Quat &value);
	inline void readIndex3(uint32_t &value0,uint32_t &value1,uint32_t &value2);
	inline void readFloat3(float &value0,float &value1,float &value2);
};

inline
bool PfxFileReader::open(const char *filename)
{
	mFp = fopen(filename,"r");
	if(!mFp) return false;
	return true;
}

inline
bool PfxFileReader::getNextTag()
{
	if(isEof()) return false;
	getLine(mLineBuff,LINEBUFF_MAX);
	readTag(mLineBuff,mTag);
	return true;
}

inline
bool PfxFileReader::isSameTag(char *tag)
{
	return isSame(mTag,tag);
}

inline
void PfxFileReader::getLine(char *line,int n)
{
	if(mFp) fgets(line,n,mFp);
}

inline
bool PfxFileReader::isSame(char *s1,char *s2)
{
	return strcmp(s1,s2)==0;
}

inline
bool PfxFileReader::isToken(char c)
{
	return (c==' ' || c=='\t' || c=='\n' || c=='\r' || c==',');
}

inline
void PfxFileReader::readTag(char *line,char *tag)
{
	char *cur = line;
	char *s,*e;
	s = e = NULL;

	tag[0] = '\0';
	while(*cur!='\0') {
		if(!isToken(*cur) && !s && !e) {
			s = cur;
		}
		if(isToken(*cur) && s && !e){
			e = cur;
			assert(e-s<=TAG_STR_MAX);
			strncpy(tag,s,e-s);
			tag[e-s] = '\0';
			return;
		}
		cur++;
	}
}

inline
void PfxFileReader::readString(char *str,int n)
{
	char *cur = mLineBuff;
	char *s,*e;
	s = e = NULL;

	str[0] = '\0';
	while(*cur!='\0') {
		if(*cur=='\"' && !s && !e) {
			s = ++cur;
		}
		if(*cur=='\"' && s && !e){
			e = cur;
			int sz = PFX_MIN(e-s,n-1);
			strncpy(str,s,sz);
			str[sz] = '\0';
			return;
		}
		cur++;
	}
}

inline
void PfxFileReader::readUint32(uint32_t &value)
{
	char dummy[TAG_STR_MAX];
	sscanf(mLineBuff,"%s %d",dummy,&value);
}

inline
void PfxFileReader::readBool(bool &value)
{
	uint32_t tmp;
	readUint32(tmp);
	value = (bool)tmp;
}

inline
void PfxFileReader::readInt32(int32_t &value)
{
	char dummy[TAG_STR_MAX];
	sscanf(mLineBuff,"%s %d",dummy,&value);
}

inline
void PfxFileReader::readFloat(float &value)
{
	char dummy[TAG_STR_MAX];
	sscanf(mLineBuff,"%s %f",dummy,&value);
}

inline
void PfxFileReader::readVector3(Vector3 &value)
{
	char dummy[TAG_STR_MAX];
	float f[3];
	sscanf(mLineBuff,"%s %f %f %f\n",dummy,&f[0],&f[1],&f[2]);
	value = Vector3(f[0],f[1],f[2]);
}

inline
void PfxFileReader::readMatrix3(Matrix3 &value)
{
	char dummy[TAG_STR_MAX];
	float f[9];
	sscanf(mLineBuff,"%s %f %f %f %f %f %f %f %f %f\n",dummy,
		&f[0],&f[1],&f[2],  // col0
		&f[3],&f[4],&f[5],  // col1
		&f[6],&f[7],&f[8]); // col2
	value.setCol0(Vector3(f[0],f[1],f[2]));
	value.setCol1(Vector3(f[3],f[4],f[5]));
	value.setCol2(Vector3(f[6],f[7],f[8]));
}

inline
void PfxFileReader::readQuat(Quat &value)
{
	char dummy[TAG_STR_MAX];
	float f[4];
	sscanf(mLineBuff,"%s %f %f %f %f\n",dummy,&f[0],&f[1],&f[2],&f[3]);
	value = Quat(f[0],f[1],f[2],f[3]);
}

inline
void PfxFileReader::readIndex3(uint32_t &value0,uint32_t &value1,uint32_t &value2)
{
	char dummy[TAG_STR_MAX];
	sscanf(mLineBuff,"%s %d %d %d\n",dummy,&value0,&value1,&value2);
}

inline
void PfxFileReader::readFloat3(float &value0,float &value1,float &value2)
{
	char dummy[TAG_STR_MAX];
	sscanf(mLineBuff,"%s %f %f %f\n",dummy,&value0,&value1,&value2);
}

///////////////////////////////////////////////////////////////////////////////
// File Writer

class PfxFileWriter : public PfxFileIO
{
private:
	int		mIndentCnt;
	char	mIndents[INDENT_MAX];

	inline void indentUp();
	inline void indentDown();

public:
	virtual bool open(const char *filename);

	inline void writeOpenTag(const char *name);
	inline void writeCloseTag();
	inline void writeString(const char *name,const char *str);
	inline void writeBool(const char *name,bool value);
	inline void writeUint32(const char *name,uint32_t value);
	inline void writeInt32(const char *name,int32_t value);
	inline void writeFloat(const char *name,float value);
	inline void writeVector3(const char *name,const Vector3 &value);
	inline void writeMatrix3(const char *name,const Matrix3 &value);
	inline void writeQuat(const char *name,const Quat &value);
	inline void writeIndex3(const char *name,uint32_t value0,uint32_t value1,uint32_t value2);
	inline void writeFloat3(const char *name,float value0,float value1,float value2);
};

inline
bool PfxFileWriter::open(const char *filename)
{
	mFp = fopen(filename,"w");
	if(!mFp) return false;
	mIndentCnt = 0;
	mIndents[0] = '\0';
	return true;
}


inline
void PfxFileWriter::indentUp()
{
	assert(mIndentCnt < INDENT_MAX);
	mIndents[mIndentCnt] = '\t';
	mIndents[++mIndentCnt] = '\0';
}

inline
void PfxFileWriter::indentDown()
{
	assert(mIndentCnt > 0);
	mIndents[--mIndentCnt] = '\0';
}

inline
void PfxFileWriter::writeOpenTag(const char *name)
{
	fprintf(mFp,"%s%s\n",mIndents,name);
	fprintf(mFp,"%s{\n",mIndents);
	indentUp();
}

inline
void PfxFileWriter::writeCloseTag()
{
	indentDown();
	fprintf(mFp,"%s}\n",mIndents);
}

inline
void PfxFileWriter::writeString(const char *name,const char *str)
{
	fprintf(mFp,"%s%s \"%s\"\n",mIndents,name,str);
}

inline
void PfxFileWriter::writeBool(const char *name,bool value)
{
	writeUint32(name,(uint32_t)value);
}

inline
void PfxFileWriter::writeUint32(const char *name,uint32_t value)
{
	fprintf(mFp,"%s%s %u\n",mIndents,name,value);
}

inline
void PfxFileWriter::writeInt32(const char *name,int32_t value)
{
	fprintf(mFp,"%s%s %d\n",mIndents,name,value);
}

inline
void PfxFileWriter::writeFloat(const char *name,float value)
{
	fprintf(mFp,"%s%s %.5f\n",mIndents,name,value);
}

inline
void PfxFileWriter::writeVector3(const char *name,const Vector3 &value)
{
	fprintf(mFp,"%s%s %.5f %.5f %.5f\n",mIndents,name,
		(float)value[0],(float)value[1],(float)value[2]);
}

inline
void PfxFileWriter::writeMatrix3(const char *name,const Matrix3 &value)
{
	fprintf(mFp,"%s%s %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f\n",mIndents,name,
		(float)value[0][0],(float)value[0][1],(float)value[0][2],  // col0
		(float)value[1][0],(float)value[1][1],(float)value[1][2],  // col1
		(float)value[2][0],(float)value[2][1],(float)value[2][2]); // col2
}

inline
void PfxFileWriter::writeQuat(const char *name,const Quat &value)
{
	fprintf(mFp,"%s%s %.5f %.5f %.5f %.5f\n",mIndents,name,
		(float)value[0],(float)value[1],(float)value[2],(float)value[3]);
}

inline
void PfxFileWriter::writeIndex3(const char *name,uint32_t value0,uint32_t value1,uint32_t value2)
{
	fprintf(mFp,"%s%s %u %u %u\n",mIndents,name,value0,value1,value2);
}

inline
void PfxFileWriter::writeFloat3(const char *name,float value0,float value1,float value2)
{
	fprintf(mFp,"%s%s %.5f %.5f %.5f\n",mIndents,name,value0,value1,value2);
}

#endif /* __PFX_FILE_IO_H__ */
