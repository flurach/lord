project "cli"
	kind "ConsoleApp"
	language "C"
	targetname "lord"

	includedirs {
		"src",
		(BASE_DIR .. "/lc/src"),
		(BASE_DIR .. "/lp/src"),
		(BASE_DIR .. "/vm/src"),
	}
	files { "src/**.c" }
	links { "lc", "lp", "vm" }
