#ifndef _GUI_SYSTEM_H_
#define _GUI_SYSTEM_H_

#include "System.hpp"
#include <boost/serialization/singleton.hpp>

using namespace boost::serialization;

class GuiSystem : public ISystem, public singleton<GuiSystem>
{
    private:
        // MyGui ....

    public:
        GuiSystem();
        ~GuiSystem();

        // Inherited from ISystem
        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
