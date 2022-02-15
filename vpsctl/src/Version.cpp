#include "Version.h"

Version::Version(unsigned int major, unsigned int minor) :
	m_version(((major & 0x0f) << 4) | (minor & 0x0f)) 
{
}

void Version::setMajorVersion(unsigned int version) 
{
	m_version = (m_version & 0x0f) | ((version & 0x0f) << 4);
}

void Version::setMinorVersion(unsigned int version) 
{
	m_version = (m_version & 0xf0) | (version & 0x0f);
}

unsigned int Version::getMajorVersion() const 
{
	return (m_version & 0xf0) >> 4;
}

unsigned int Version::getMinorVersion() const 
{
	return m_version & 0x0f;
}

