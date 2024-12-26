#include "DebugLog.hpp"

#include <vector>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

DEBUG_USING_NAMESPACE

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
		DEBUG_VALUE_AND_TYPE_OF(*this);
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

class class_b : public base_class
{
private:
	bool will_fail;
public:
	class_b(const bool wf)
		: base_class("default b param"), will_fail(wf)
	{
		DEBUG_METHOD();
	}

	virtual void bar()
	{
		DEBUG_METHOD();
		DEBUG_VALUE_OF(will_fail);
		if (will_fail)
		{
			DEBUG_MESSAGE("throwing an exception as I was configured to fail");
			throw std::exception("bound to happend");
		}
		else
		{
			base_class::bar();
		}
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	DEBUG_METHOD();
	try
	{
		std::vector<int> integer_list;
		class_a a("setec astronomy");
		integer_list.push_back(a.foobar());

		class_b b1(false);

		integer_list.push_back(b1.foobar());

		DEBUG_MESSAGE("all methods called, compiling results");
		DEBUG_VALUE_OF_COLLECTION(integer_list);

		// Run it again in a way that will throw an exception
		class_b b2(true);
		integer_list.push_back(b2.foobar());

	}
	catch(std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

