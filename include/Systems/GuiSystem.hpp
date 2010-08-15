#ifndef _GUI_SYSTEM_H_
#define _GUI_SYSTEM_H_

#include "System.hpp"
#include <boost/serialization/singleton.hpp>
#include "Core/Singleton.hpp"

#include "Systems/GraphicSystem.hpp"
#include "Managers/LogManager.hpp"
#include "Managers/ResourceManager.hpp"

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

using namespace boost::serialization;

class GuiSystem : public ISystem, public ISingleton<GuiSystem>
{
    private:
		MyGUI::Gui *mGUI;
		MyGUI::OgrePlatform *mPlatform;

    public:
        GuiSystem();
        ~GuiSystem();

        MyGUI::Gui *getGui() const { return mGUI; }
        // TODO: Check whether resource name is in list
        void loadLayout(const string &name) { MyGUI::LayoutManager::getInstance().load(name); }

        // Inherited from ISystem
        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
