#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

using boost::property_tree::ptree;
using namespace std;

class ConfigManager
{
	protected:
		string mConfigPath;
		ptree mPropertyTree;

	public:
		ConfigManager(const string &filePath = "settings.info") :
			mConfigPath(filePath)
		{
			read_info(mConfigPath, mPropertyTree);
		}

		template<typename T>
		T getValue(const string &key, const T &defaultValue = T())
		{
			return mPropertyTree.get<T>(key, defaultValue);
		}
};

#endif
