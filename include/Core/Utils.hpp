#ifndef _UTILS_H_
#define _UTILS_H_

#include <boost/serialization/singleton.hpp>
#include <boost/format.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/signals2.hpp>
#include <boost/algorithm/string.hpp>

#include <Ogre.h>

#include "Managers/LogManager.hpp"

using namespace std;
using namespace boost;
using namespace boost::serialization;
using namespace boost::posix_time;

#define FORMAT(parentString, params) (boost::format(parentString) % params).str()
#define NEW_EVENT(Signature, Name) typedef SlotObject< signals2::signal<Signature> > Name;

class Utils : public singleton<Utils>
{
    protected:
		string mMediaPath;
        string mDimension;
        ptime mTimeStamp;

        void createPlane(Ogre::Mesh *newMesh);
        void createSphere(Ogre::Mesh *newMesh);
        void createCube(Ogre::Mesh *newMesh);
    public:
        Utils() : mDimension("2D") { }
        ~Utils() { }

        const string getMediaPath() const;
        const string getDimension() const;
        void setDimension(string &d);
        ptime getCurrentTime() const;

        void setMediaPath(const string &path);

        // For time measuring
        void writeTimestamp();
        string getTimeDifference();
};

#endif
