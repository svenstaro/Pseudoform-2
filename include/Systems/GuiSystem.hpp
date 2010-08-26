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

#include <map>

using namespace boost::serialization;
using namespace std;

class GuiSystem : public ISystem, public ISingleton<GuiSystem>
{
    private:
		MyGUI::Gui *mGUI;
		MyGUI::OgrePlatform *mPlatform;

		map<string, MyGUI::VectorWidgetPtr> mWidgetLayouts;

    public:
        GuiSystem();
        ~GuiSystem();

        MyGUI::Gui *handle() const { return mGUI; }

        void loadLayout(const string &name);
        void unloadLayout(const string &name);

        // Inherited from ISystem
        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
