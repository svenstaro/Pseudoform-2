#ifndef _UTILS_H_
#define _UTILS_H_

#include <boost/serialization/singleton.hpp>
#include <boost/format.hpp>
#include <boost/signals2.hpp>

using namespace boost;
using namespace boost::serialization;

#define FORMAT(parentString, params) (boost::format(parentString) % params).str()
#define NEW_EVENT(Signature, Name) typedef SlotObject< signals2::signal<Signature> > Name;

class Utils : public singleton<Utils>
{
    protected:

    public:
        Utils()
        {
        }

        ~Utils()
        {
        }

        // We really needn't in this
        enum renderType {
            OPENGL,
            DIRECT3D
        } mRenderer;
        renderType *renderer() { return &mRenderer; }
};

#endif
