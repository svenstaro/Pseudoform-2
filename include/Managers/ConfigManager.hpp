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

        void _forcePtree(const string &configPath)
        {
            if (mPtreeList.count(configPath) == 0)
            {
                mPtreeList.insert(make_pair(configPath, ptree()));
            }
        }

    public:
        ConfigManager()
        {
            mDefaultPath = "settings.info";
            _forcePtree(mDefaultPath);
            read_info(mDefaultPath, mPtreeList[mDefaultPath]);
        }

        template<typename T>
        T getValue(const string &key, const T &defaultValue = T(), const string &ownConfig = "")
        {
            if (key == "") LOG("Trying to get config value of empty key!");
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

        vector<string> getListValue(const string &key, const string &ownConfig = "")
        {
            vector<string> listValues;
            ptree workTree;

            if (key == "") LOG("Trying to get config value of empty key!");
            if (ownConfig != "")
            {
                _forcePtree(ownConfig);
                workTree = mPtreeList[ownConfig];
            }
            else
            {
                workTree = mPtreeList[mDefaultPath];
            }

            BOOST_FOREACH(ptree::value_type &value, workTree.get_child(key))
            {
                listValues.push_back(value.second.data());
            }

            return listValues;
        }
};

#endif
