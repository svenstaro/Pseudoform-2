set(Pseudoform_srcs
    Managers/Entities/Object.cpp
    Managers/Entities/Entity.cpp
    Managers/EventManager.cpp
    Managers/EntityManager.cpp
    Managers/ResourceManager.cpp
    Managers/LogManager.cpp
    Managers/ConfigManager.cpp
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
)
