#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

#include "PseudoformAdditional.hpp"
#include "PseudoformCore.hpp"

#include <vector>
#include <map>

using boost::property_tree::ptree;
using namespace std;

class ConfigManager
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
		ConfigManager(const string &configPath = "settings.info")
		{
                    mDefaultPath = configPath;
                    _forcePtree(configPath);
                    read_info(configPath, mPtreeList[configPath]);
		}

		template<typename T>
		T getValue(const string &key, const T &defaultValue = T(), const string &ownConfig = "")
		{
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

                    if (ownConfig != "")
                    {
                        _forcePtree(ownConfig);
                        workTree = mPtreeList[ownConfig];
                    }
                    else
                    {
                        workTree = mPtreeList[mDefaultPath];
                    }

                    bforeach(ptree::value_type &value, workTree.get_child(key))
                    {
                        listValues.push_back(value.second.data());
                    }

                    return listValues;
                }
};

#endif
