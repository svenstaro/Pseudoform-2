#include "Managers/ConfigManager.hpp"

ConfigManager::ConfigManager()
{
    mDefaultPath = "settings.info";
    _forcePtree(mDefaultPath);
    read_info(mDefaultPath, mPtreeList[mDefaultPath]);
}

void ConfigManager::_forcePtree(const string& configPath)
{
    if (mPtreeList.count(configPath) == 0)
    {
        mPtreeList.insert(make_pair(configPath, ptree()));
    }
}

vector<string> ConfigManager::getListValue(const string& key, const string& ownConfig)
{
    vector<string> listValues;
    ptree workTree;

    if (key == "") LOG_META("Trying to get config value of empty key!");
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
