#ifndef _UTILS_H_
#define _UTILS_H_

#include <boost/serialization/singleton.hpp>
#include <boost/format.hpp>

using namespace boost;
using namespace boost::serialization;

#define FORMAT(parentString, params) (boost::format(parentString) % params).str()

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
