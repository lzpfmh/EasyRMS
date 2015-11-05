/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef _Easy_HLS_API_H
#define _Easy_HLS_API_H

#ifdef _WIN32
#define EasyHLS_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#else
#define EasyHLS_API
#define Easy_APICALL 
#endif

#define Easy_Record_Handle void*

enum{
	TS_TYPE_PAT = 0x01000000,
	TS_TYPE_PMT = 0x02000000,
	TS_TYPE_PES = 0x03f00000,

	TS_TYPE_PES_AUDIO         = 0x03100000,
	TS_TYPE_PES_VIDEO_I_FRAME = 0x03200000,
	TS_TYPE_PES_VIDEO_P_FRAME = 0x03400000,
	TS_TYPE_PES_VIDEO_E_FRAME = 0x03800000,
};

typedef enum _ENUM_RECORD_TYPE
{
	RECORD_TYPE_OSS,
	RECORD_TYPE_FILE
}ENUM_RECORD_TYPE;

#ifdef __cplusplus
extern "C"
{
#endif
	
	/* OSS ��ʼ�� ȫ�ֵ���һ�� */
	EasyHLS_API int EasyRecord_OSS_Initialize(const char* bucket_name, const char* oss_endpoint, size_t oss_port, const char* access_key_id, const char* access_key_secret);
	
	/* OSS ��Դ���� ȫ�ֵ���һ�� */
	EasyHLS_API void EasyRecord_OSS_Deinitialize();

	EasyHLS_API void Easy_APICALL EasyRecord_SetRecordType(ENUM_RECORD_TYPE type);

	/* ����HLSSession  ����Ϊ���ֵ */
	EasyHLS_API Easy_Record_Handle Easy_APICALL EasyRecord_Session_Create(/*int nCapacity,*/ bool bAllowCache, int version);

	/* ����HLS���� strRootDir:��/��β��Ŀ¼ strSubDir:��/��β��Ŀ¼ strMediaName:ý�����ơ�nTargetDuration:������Ƭʱ�� */
	EasyHLS_API void Easy_APICALL EasyRecord_ResetStreamCache(Easy_Record_Handle handle, const char * strRootDir, const char* strSubDir, const char* strMediaName, int nTargetDuration);
	
	/* ��ȡ����HLSSession��m3u8�ļ� */
	EasyHLS_API const char*  Easy_APICALL EasyRecord_GetM3U8File(Easy_Record_Handle handle);
	
	/* �����Ƶ */
	EasyHLS_API int Easy_APICALL EasyRecord_VideoMux(Easy_Record_Handle handle, unsigned int uiFrameType, unsigned char *data, int dataLength, unsigned long long pcr, unsigned long long pts, unsigned long long dts);
	
	/* �����Ƶ */
	EasyHLS_API int Easy_APICALL EasyRecord_AudioMux(Easy_Record_Handle handle, unsigned char *data, int dataLength, /*u64 pcr,*/ unsigned long long pts, unsigned long long dts=~0);

	/* �ͷ�HLSSession */
	EasyHLS_API void Easy_APICALL EasyRecord_Session_Release(Easy_Record_Handle handle);

#ifdef __cplusplus
}
#endif

#endif