#include "CMyBass.h"
#include <iostream>

#pragma comment(lib,"bass.lib")
CMyBass::~CMyBass(){
	if (!m_MusicList.empty())
	{
		for (MLI it=m_MusicList.begin();it!=m_MusicList.end();++it)
		{
			BASS_StreamFree(it->second);
		}
		m_MusicList.clear();
	}
	if (!m_SoundList.empty())
	{
		for (MLI it=m_SoundList.begin();it!=m_SoundList.end();++it)
		{
			BASS_StreamFree(it->second);
		}
		m_SoundList.clear();
	}
	BASS_Free();
}
CMyBass::CMyBass(){
	m_isInit=false;
}
CMyBass::CMyBass(const CMyBass& that){}
CMyBass& CMyBass::operator = (const CMyBass& that){return *this;}
BOOL CMyBass::Init()
{
	if (!m_isInit)
	{
		if(BASS_Init(-1,44100,0,NULL,0))
		{
			m_isInit=true;
			return TRUE;
		}
	}else
	{
		return TRUE;
	}
	return FALSE;
}
CMyBass* CMyBass::GetInstance()
{
	static CMyBass m_Instance;
	return &m_Instance;
}
int CMyBass::LoadSound(string soundPath,DWORD flags)//��������
{
	HSTREAM hs=0;
	MLI _findReturn=m_SoundList.find(soundPath);
	if (_findReturn!=m_SoundList.end())//�Ѿ�����
	{
		return _findReturn->second;
	}else//��δ���ع����������
	{
		hs=BASS_StreamCreateFile(FALSE,soundPath.c_str(),0,0,flags);//���ļ���������

		if (hs==NULL){//����ʧ��
			return hs;
		}else//���سɹ�
		{
			m_SoundList.insert(make_pair(soundPath,hs));//�����б�
		}
	}
	return hs;

}
int CMyBass::LoadMusic(string musicPath,DWORD flags)
{
	HSTREAM hs=0;
	MLI _findReturn=m_MusicList.find(musicPath);
	if (_findReturn!=m_MusicList.end())//�Ѿ�����
	{
		return _findReturn->second;
	}else//��δ���ع����������
	{
		hs=BASS_StreamCreateFile(FALSE,musicPath.c_str(),0,0,flags);//���ļ���������

		if (hs==NULL){//����ʧ��
			return hs;
		}else//���سɹ�
		{
			m_MusicList.insert(make_pair(musicPath,hs));//�����б�
		}
	}
	return hs;
}
BOOL CMyBass::PlaySound(string sName)//������Ч
{
	MLI _findReturn=m_SoundList.find(sName);
	if (_findReturn!=m_SoundList.end())//����
	{
		return BASS_ChannelPlay(_findReturn->second,TRUE);
	}
	return FALSE;
}
BOOL CMyBass::PlayMusic(string sName,BOOL restart)//��������
{
	MLI _findReturn=m_MusicList.find(sName);
	if (_findReturn!=m_MusicList.end())//����
	{
		return BASS_ChannelPlay(_findReturn->second,restart);
	}
	return FALSE;
}

int CMyBass::GetData(string sName,void* buf)
{
	MLI _findReturn=m_MusicList.find(sName);
	if (_findReturn!=m_MusicList.end())//����
	{
		return BASS_ChannelGetData(_findReturn->second,buf,2147483648);
	}
	return 0;
}