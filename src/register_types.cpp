#include "register_types.h"
#include "entidades/jugador.h"
#include "entidades/enemigos.h"
#include "entidades/espectros/espectro_gris.h"
#include "entidades/enemigos_simples/mouse.h"
#include "entidades/enemigos_simples/chocobo.h"
#include "entidades/enemigos_simples/ojo_espectral.h"
#include "mapa.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    ClassDB::register_class<Player2D>();
    ClassDB::register_class<MainMapa>();
    ClassDB::register_class<EspectroGris>();
    ClassDB::register_class<Raton>();
    ClassDB::register_class<Chocobo>();
    ClassDB::register_class<OjoEspectral>();
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}

