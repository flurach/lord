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


project "vm"
	basedir "vm"
	kind "SharedLib"
	language "C"

	includedirs { "src" }
	files { "src/**.c" }


project "lp"
	basedir "lp"
	kind "SharedLib"
	language "C"

	includedirs { "." }
	files { "**.c" }


project "lc"
	basedir "lc"
	kind "SharedLib"
	language "C"

	includedirs {
		".",
		(BASE_DIR .. "/lp/src")
	}
	files { "**.c" }


project "cli"
	basedir "cli"
	kind "ConsoleApp"
	language "C"

	targetname "lord"

	includedirs {
		".",
		(BASE_DIR .. "/lc/"),
		(BASE_DIR .. "/lp/"),
		(BASE_DIR .. "/vm/"),
	}
	files { "**.c" }
	links { "lc", "lp", "vm" }
