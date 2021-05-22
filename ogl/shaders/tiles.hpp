#pragma once

#include "programBase.hpp"

namespace Shaders
{
	namespace Programs
	{
		struct TilesAccessor : ProgramBase
		{
			using ProgramBase::ProgramBase;

			TilesAccessor(Shaders::ProgramId program) :
				ProgramBase(program),
				hSizeUniform(program, "hSize")
			{
			}

			Uniforms::UniformController2f hSizeUniform;
		};

		struct Tiles : TilesAccessor
		{
			Tiles() :
				TilesAccessor(Shaders::LinkProgram(Shaders::CompileShaders("ogl/shaders/tiles.vs",
					"ogl/shaders/tiles.gs", "ogl/shaders/tiles.fs"), { {0, "bPos"}, {1, "bColor"} }))
			{
			}

			Tiles(const Tiles&) = delete;

			~Tiles()
			{
				glDeleteProgram(getProgramId());
			}
		};
	}
}
