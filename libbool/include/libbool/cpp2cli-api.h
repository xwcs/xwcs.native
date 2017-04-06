#ifndef _H_cpp2cli_api
#define _H_cpp2cli_api

#ifdef HW_UNIX
#ifndef DECLSPECIFIER
#define DECLSPECIFIER 
#define EXPIMP_TEMPLATE
#endif
#else  /* def HW_UNIX */
#if defined(libbool_EXPORTS)
#ifndef DECLSPECIFIER
#define DECLSPECIFIER __declspec(dllexport)
#define EXPIMP_TEMPLATE 
#endif
#else
#ifndef DECLSPECIFIER
#define DECLSPECIFIER __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif
#endif
#endif  /* else def HW_UNIX */


namespace xw {
	namespace boolexpr {

		namespace det {
			class DECLSPECIFIER char_ptr {
				char* _ptr;
				size_t _capacity;
			public :
				char_ptr(size_t len = 4096);
				~char_ptr();
				void save(const char* what);
				const char* c_str() const;
			};
		}

		class DECLSPECIFIER Expression {
			det::char_ptr _lastDnf;
		public:
			Expression() : _lastDnf() {}
			const char* ToDNF(const char * expr);
		};
	}
}

#endif  /* _H_cpp2cli_api */
