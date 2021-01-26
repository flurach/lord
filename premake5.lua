workspace "lord"
	configurations { "debug", "release" }

	architecture "x64"
	toolset "clang"
	warnings "extra"

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
	cppdialect "C++17"
	pchheader "lp/lp.hh"

	includedirs { INCLUDES }
	files { "lp/**.cc" }

project "lc"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	pchheader "lc/lc.hh"

	includedirs { INCLUDES }
	files { "lc/**.cc" }

project "cli"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetname "lord"

	includedirs { INCLUDES }
	files { "cli/**.cc" }
	links { "lc", "lp", "readline" }
