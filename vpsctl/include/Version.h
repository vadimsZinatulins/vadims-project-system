#pragma once

class Version final
{
public:
	Version() = default;
	Version(unsigned int major, unsigned int minor);
	~Version() = default;

	void setMajorVersion(unsigned int version);
	void setMinorVersion(unsigned int version);

	unsigned int getMajorVersion() const;
	unsigned int getMinorVersion() const;
private:
	char m_version;
};
