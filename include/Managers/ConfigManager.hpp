#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/foreach.hpp>

#include "Managers/LogManager.hpp"

#include <vector>
#include <map>

using namespace boost::serialization;
using boost::property_tree::ptree;
using namespace std;

#define CONFIG(key, type, def) ConfigManager::get_mutable_instance().getValue<type>(key, def)
class ConfigManager : public singleton<ConfigManager>
{
    protected:
        string mDefaultPath;
        map<string, ptree> mPtreeList;

        void _forcePtree(const string &configPath);

    public:
        ConfigManager();

        template<typename T>
        T getValue(const string &key, const T &defaultValue = T(), const string &ownConfig = "")
        {
            if (key == "") LOG_META("Trying to get config value of empty key!");
            if (ownConfig != "")
            {
                _forcePtree(ownConfig);
                return mPtreeList[ownConfig].get<T>(key, defaultValue);
            }
            else
            {
                return mPtreeList[mDefaultPath].get<T>(key, defaultValue);
            }
        }
        vector<string> getListValue(const string &key, const string &ownConfig = "");
};

#endif
