#include "DebugLog.hpp"
#include "DebugLog.cpp"

#include <iostream>
#include <string>

using namespace std;

class base_class
{
protected:
	int counter;
public:
	base_class(const std::string& param)
		: counter(0)
	{
		DEBUG_METHOD();
		DEBUG_VALUE_OF(counter);
		DEBUG_VALUE_OF(param);
	}

	int foobar()
	{
		DEBUG_METHOD();
		foo();
		bar();
		DEBUG_VALUE_OF(counter);
		return counter;
	}

	void foo()
	{
		DEBUG_METHOD();	
		++counter;
	}

	virtual void bar()
	{
		DEBUG_METHOD();
		++counter;
	}

	friend std::ostream& operator<< (std::ostream& stream, const base_class& base);
};

 std::ostream& operator<< (std::ostream& stream, const base_class& base)
 {
	 return stream << "counter is" << base.counter;
 }

class class_a : public base_class
{
public:
	class_a(const std::string& param)
		: base_class(param)
	{
		DEBUG_METHOD();
	}

	virtual void bar()
	{
		DEBUG_METHOD();
		counter += a_helper(1, 10, 'a');
	}

	int a_helper(int x, int y, char z)
	{
		DEBUG_METHOD();
		DEBUG_VALUE_OF(x);
		DEBUG_VALUE_OF(y);
		DEBUG_VALUE_OF(z);
		return x + y + static_cast<int>(z);
	}
};

int main(int /*argc*/, char** /*argv*/)
{
    DEBUG_SET_STREAM(cout);
	DEBUG_METHOD();
    std::vector<int> integer_list;
	class_a a("setec astronomy");
	integer_list.push_back(a.foobar());
	return 0;
}

