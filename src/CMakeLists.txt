set(Pseudoform_srcs
	Core/GameApplication.cpp
	Core/Utils.cpp
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
	${SFML_LIBARIES}
	${OGRE_LIBARIES}
	${BULLET_LIBRARIES}
)
