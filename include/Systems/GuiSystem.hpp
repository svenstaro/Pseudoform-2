#ifndef _GUI_SYSTEM_H_
#define _GUI_SYSTEM_H_

#include "System.hpp"
#include <boost/serialization/singleton.hpp>

#include "Systems/GraphicSystem.hpp"
#include "Managers/LogManager.hpp"
#include "Managers/ResourceManager.hpp"

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

using namespace boost::serialization;

class GuiSystem : public ISystem, public singleton<GuiSystem>
{
    private:
		MyGUI::Gui *mGUI;
		MyGUI::OgrePlatform *mPlatform;

    public:
        GuiSystem();
        ~GuiSystem();

        // Inherited from ISystem
        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
