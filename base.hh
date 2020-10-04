#ifndef SHAPE_CORE_BASE_HH__GUARD
#define SHAPE_CORE_BASE_HH__GUARD

namespace shape
{

	struct CoreError
	{
		static void error(const char *);
		static void raise(const char *);
		template<typename ...Args> static void error(const char *, const Args&...);
		template<typename ...Args> static void raise(const char *, const Args&...);
	};

} // namespace shape

#endif