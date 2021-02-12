workspace "lord"
	architecture "x64"
	configurations { "debug", "release" }

	toolset "clang"
	warnings "extra"
	cppdialect "C++17"

	BASE_DIR = path.getabsolute(".")
	targetdir (BASE_DIR .. "/bin")
	objdir (BASE_DIR .. "/bin/obj")
	INCLUDES = {
		(BASE_DIR .. "/lp"),
		(BASE_DIR .. "/lc"),
		(BASE_DIR .. "/cli")
	}

	filter "configurations:debug"
		symbols "on"

	filter "configurations:release"
		optimize "on"
		defines { "NDEBUG" }


project "lp"
	kind "SharedLib"
	language "C++"
	pchheader "lp/lp.hh"

	includedirs { INCLUDES }
	files { "lp/**.cc" }

project "lc"
	kind "SharedLib"
	language "C++"
	pchheader "lc/lc.hh"

	includedirs { INCLUDES }
	files { "lc/**.cc" }

project "cli"
	kind "ConsoleApp"
	language "C++"
	targetname "lord"

	includedirs { INCLUDES }
	files { "cli/**.cc" }
	links { "lc", "lp", "readline" }
