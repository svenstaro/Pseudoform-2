set(Pseudoform_srcs
    Managers/Entities/Camera.cpp
    Managers/Entities/Light.cpp
    Managers/Entities/Object.cpp
    Managers/Entities/Entity.cpp
    Managers/StateManager.cpp
    Managers/EventManager.cpp
    Managers/EntityManager.cpp
    Managers/ResourceManager.cpp
    Managers/LogManager.cpp
    Managers/ConfigManager.cpp
    Core/Utils.cpp
    Core/GameApplication.cpp
    Systems/GraphicSystem.cpp
    Systems/PhysicSystem.cpp
    Systems/InputSystem.cpp
    Systems/GuiSystem.cpp
    Systems/SoundSystem.cpp
)

add_library(Pseudoform STATIC
	${Pseudoform_srcs}
)

target_link_libraries(Pseudoform
	${Boost_LIBRARIES}
	${SFML_LIBRARY}
	${OGRE_LIBRARIES}
	${BULLET_LIBRARIES}
    ${MYGUI_LIBRARIES}
    ${MYGUI_PLATFORM_LIBRARIES}
)
