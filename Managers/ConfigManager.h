#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "Core/Additional/txml/txml.hpp"
#include "Core/AppIncludes.h"

#include <stdexcept>

using namespace std;
using namespace txml;

class ConfigManager
{
	protected:
		string mConfigPath;

		document mConfigHandle;
		element *mRootElement;

	public:
		ConfigManager(const string &filePath = "settings.xml") :
			mConfigPath(filePath)
		{
			mConfigHandle = mConfigPath.c_str();

			if (mConfigHandle.Error())
				throw std::runtime_error("Root error(" + mConfigPath + "): " + mConfigHandle.ErrorDesc());

			mRootElement = mConfigHandle.RootElement();
		}

		~ConfigManager()
		{
			delete mRootElement;
		}

		template<class T>
		T getValue(const string &key, const string &defaultValue = "")
		{
			return mRootElement->attrib<T>(key, defaultValue);
		}
};

#endif
