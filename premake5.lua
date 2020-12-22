workspace "lord"
	configurations { "debug", "release" }
	warnings "extra"

	BASE_DIR = path.getabsolute(".")
	targetdir (BASE_DIR .. "/_bin")
	objdir (BASE_DIR .. "/_bin/obj")

	filter "configurations:debug"
		symbols "on"

	filter "configurations:release"
		optimize "on"


include "vm"
include "lc"
include "cli"
