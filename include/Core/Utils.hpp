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
#include "Core/Types.hpp"

using namespace std;
using namespace boost;
using namespace boost::serialization;
using namespace boost::posix_time;

// Make formatted string. Usage: FORMAT("some %1% string %2%", firstArg % secondArg);
#define FORMAT(parentString, params) (boost::format(parentString) % params).str()
#define NEW_EVENT(Signature, Name) typedef SlotObject< signals2::signal<Signature> > Name;

// Check the location exists
#define LOCATION(path) Utils::get_mutable_instance().checkLocation(path)

#define utils (Utils::get_mutable_instance())
#define utilsConst (Utils::get_const_instance())

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

        string checkLocation(const string &path);
        const string getMediaPath() const;
        void setMediaPath(const string &path);

        const string getDimension() const;
        void setDimension(string &d);

        // For time measuring
        ptime getCurrentTime() const;
        void writeTimestamp();
        string getTimeDifference();

        string bool2string(bool var) { return(var ? "true" : "false"); }
        string vec2string(const vec3 &v) { return FORMAT("vec3(x=%1%;y=%2%;z=%3%)", v.x % v.y % v.z); }
        string vec2string(const vec2 &v) { return FORMAT("vec2(x=%1%;y=%2%)", v.x % v.y); }
        string quat2string(const quat &q) { return FORMAT("quat(w=%1%;x=%2%;y=%3%;z=%4%)", q.w % q.x % q.y % q.z); }
        string color2string(const colour &c) { return FORMAT("color(r=%1%;g=%2%;b=%3%;a=%4%)", c.r % c.g % c.b % c.a); }
};

#endif
