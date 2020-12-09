workspace "lord"
	configurations { "debug", "release" }
	warnings "extra"

	BASE_DIR = path.getabsolute(".")
	targetdir (BASE_DIR .. "/bin")
	objdir (BASE_DIR .. "/bin/obj")

	filter "configurations:debug"
		symbols "on"

	filter "configurations:release"
		optimize "on"


include "lord"
