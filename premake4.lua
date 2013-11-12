solution "Djinn"
	configurations { "Debug", "Release" }

	project "DjinnCompiler"
		targetname "djinn"
		prebuildcommands {
			"lemon -Tsrc/parser/lempar.c src/parser/parser.y",
			"ragel src/lexer/lexer.rl -o src/lexer/lexer.c"
		}
		kind "ConsoleApp"
		language "C"
		includedirs {"include"}
		files { "src/lexer/lexer.c", "src/utils/*.c" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols", "ExtraWarnings" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

if (_ACTION == "clean") then
	print "Deep cleaning project..."
	os.rmdir("obj")
	os.remove("src/lexer/lexer.c")
	os.remove("src/parser/parser.c")
	os.remove("src/parser/parser.h")
	os.remove("src/parser/parser.out")
end