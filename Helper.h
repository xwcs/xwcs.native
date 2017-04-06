#pragma once

#include <libbool/cpp2cli-api.h>
#include <vcclr.h>
#include <exception>
#include <msclr\marshal.h>

using namespace System;

namespace xwcs {
	namespace native {
		namespace boolexpr {
			public ref class Helper
			{

				xw::boolexpr::Expression* _expression;

			public:
				Helper();

				~Helper();

				// finalize
				!Helper();

				System::String^ ToDNF(System::String^ expr);
			};
		}
	}
}

