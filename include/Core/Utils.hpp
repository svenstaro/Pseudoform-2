#ifndef _UTILS_H_
#define _UTILS_H_

#include <boost/serialization/singleton.hpp>
#include <boost/format.hpp>
#include <boost/signals2.hpp>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
using namespace boost::serialization;

#define FORMAT(parentString, params) (boost::format(parentString) % params).str()
#define NEW_EVENT(Signature, Name) typedef SlotObject< signals2::signal<Signature> > Name;

class Utils : public singleton<Utils>
{
    protected:
        string mDimension;
    public:
        Utils() : mDimension("2D") { }
        ~Utils() { }

        const string getDimension() const { return mDimension; }
        void setDimension(string &d) 
        {
            boost::to_lower(d);
            if (d == "2d")
            {
                mDimension = "2D";
                #define TWO_DIMENSIONS
            }
            else if (d == "3d")
            {
                mDimension = "3D";
                #define THREE_DIMENSIONS
            }
        }
};

#endif
