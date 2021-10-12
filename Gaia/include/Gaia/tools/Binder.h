#ifndef H__BINDER_040920111725__H
#define H__BINDER_040920111725__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <functional>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
/// Fonctions providing an easier interface to bind the member function 
/// pointers to the widgets.
///////////////////////////////////////////////////////////////////////////////
namespace gaia
{
	///1 argument functions
	template<class T, class Class, class Instance>
	inline std::function<void(typename T)> bind1(void (Class::*myFunction)(T), Instance myInstance)
	{
		return std::bind(myFunction, myInstance, _1);
	}

	/////1 argument functions
	//template<class T, class Class>
	//inline std::function1<void, T> bind1(void (Class::*myFunction)(T), Instance myInstance)
	//{
	//	return std::bind(myFunction, myInstance, _1);
	//}

	///2 arguments functions
	template<class T1, class T2, class Class, class Instance>
	inline std::function<void(typename T1, typename T2)> bind2(void (Class::*myFunction)(T1, T2), Instance myInstance)
	{
		return std::bind(myFunction, myInstance, _1, _2);
	}

	///3 arguments functions
	template<class T1, class T2, class T3, class Class, class Instance>
	inline std::function<void(T1, T2, T3)> bind3(void (Class::*myFunction)(T1, T2, T3), Instance myInstance)
	{
		return std::bind(myFunction, myInstance, _1, _2, _3);
	}

	///4 arguments functions
	template<class T1, class T2, class T3, class T4, class Class, class Instance>
	inline std::function<void(T1, T2, T3, T4)> bind4(void (Class::*myFunction)(T1, T2, T3, T4), Instance myInstance)
	{
		return std::bind(myFunction, myInstance, _1, _2, _3, _4);
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Utility class providing an interface for function binding.
	///
	/// It encapsulates a std::function.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	class FunctionHandler
	{
	public:
		FunctionHandler()
		{
		}

		template<class Class, class Instance>
		explicit FunctionHandler(void (Class::*function)(T), Instance instance)
		{
			myFunction = std::bind(function, instance, std::placeholders::_1);
		}

		explicit FunctionHandler(void (*function)(T))
		{
			myFunction = std::bind(function, std::placeholders::_1);
		}

		bool isDefined() const 
		{
			return (bool)myFunction;
		}

		void operator() (T ev)//(T ev)
		{
			myFunction(ev);
		}

		//void operator() (const T ev)
		//{
		//	myFunction(ev);
		//}

		operator bool () const { return isDefined(); }

	protected:
		std::function<void(T)> myFunction;
	};

	////Specialization for references
	//template<class T>
	//class FunctionHandler<T&>
	//{
	//public:
	//	FunctionHandler()
	//	{
	//	}

	//	template<class Class, class Instance>
	//	FunctionHandler(void (Class::*function)(T&), Instance instance)
	//	{
	//		myFunction = std::bind(function, instance, _1);
	//	}

	//	FunctionHandler(void (*function)(T&))
	//	{
	//		myFunction = std::bind(function,_1);
	//	}

	//	bool isDefined() const 
	//	{
	//		return myFunction != NULL;
	//	}

	//	void operator() (T& ev)//(T ev)
	//	{
	//		myFunction(ev);
	//	}

	//	//void operator() (const T ev)
	//	//{
	//	//	myFunction(ev);
	//	//}

	//	operator bool () const { return !this->isDefined(); }

	//protected:
	//	std::function1<void, T&> myFunction;
	//};

	template<class T, class Class, class Instance>
	FunctionHandler<T> my_bind(void (Class::*function)(T), Instance instance)
	{
		return FunctionHandler<T>(function, instance);
	}

	template<class T>
	FunctionHandler<T> my_bind(void (*function)(T))
	{
		return FunctionHandler<T>(function);
	}

} //end namespace

#endif