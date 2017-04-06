#include "stdafx.h"
#include "Helper.h"

namespace xwcs {
	namespace native {
		namespace boolexpr {
			Helper::Helper() : _expression(new xw::boolexpr::Expression())
			{

			}

			Helper::!Helper()
			{
				if (_expression) {
					delete _expression;
					_expression = NULL;
				}
			}

			System::String^ Helper::ToDNF(System::String^ expr)
			{
				IntPtr str(0);
				try {
					str = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(expr);
					return gcnew String(_expression->ToDNF((const char*)str.ToPointer()));
				}
				catch (const std::exception& e)
				{
					throw gcnew Exception(msclr::interop::marshal_as<String^>(e.what()));
				}
				catch (...)
				{
					throw gcnew Exception("Unknown C++ exception");
				}
				finally{
					// clean
					if (str.ToPointer() != NULL) System::Runtime::InteropServices::Marshal::FreeHGlobal(str);
				}
			}

			Helper::~Helper()
			{
				if (_expression) {
					delete _expression;
					_expression = NULL;
				}
			}

		}
	}
}
