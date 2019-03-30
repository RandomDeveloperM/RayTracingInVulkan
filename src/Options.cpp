#include "Options.hpp"
#include "Utilities/Exception.hpp"
#include <boost/program_options.hpp>
#include <iostream>

using namespace boost::program_options;

Options::Options(const int argc, const char* argv[])
{
	options_description desc("Ray tracer options");
	desc.add_options()
		("help", "Display help message.")
		("width", value<uint32_t>(&Width)->default_value(1280), "Set framebuffer width.")
		("height", value<uint32_t>(&Height)->default_value(720), "Set framebuffer height.")
		("fullscreen", bool_switch(&Fullscreen)->default_value(false), "Toggle fullscreen vs windowed.");

	variables_map vm;
	store(command_line_parser(argc, argv).options(desc).run(), vm);
	notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		Throw(Help());
	}
}
