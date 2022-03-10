#ifndef METHOD_H
#define METHOD_H

#include <string>
#include <json/value.h>

namespace method {
	static const std::string METHOD = "method";

	class Method {
	public:
		bool method(const Json::Value &root, Json::Value &response);
	};
};

extern handler* tv_handlers[];
extern int tv_handler_num;

#endif /* METHOD_H */
