#pragma once
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

//// convert python list to std::vector
//template<typename T>
//inline
//std::vector<T> toStdVector(const boost::python::object& iterable)
//{
//	return std::vector<T>(boost::python::stl_input_iterator<T>(iterable),
//						  boost::python::stl_input_iterator<T>());
//}

// convert python types to user defined C++ types
template<typename PyType>
bool isPyType(PyObject* pObj);

template<>
inline bool isPyType<boost::python::dict>(PyObject* pObj)
{
	return PyDict_Check(pObj);
}

template<typename CType, typename PyType = boost::python::object>
struct pyToCppConverter
{
	static void registerConverter()
	{
		boost::python::converter::registry::push_back(
			&convertible,
			&construct,
			boost::python::type_id<CType>());
	}

	static void* convertible(PyObject* pObj)
	{
		if (!isPyType<PyType>(pObj))
			return nullptr;

		return pObj;
	}

	// Convert obj_ptr into a QString
	static void construct(PyObject* pObj,
						  boost::python::converter::rvalue_from_python_stage1_data* data)
	{
		using namespace boost::python;

		// Grab pointer to memory into which to construct the new CType
		void* storage = (
			(converter::rvalue_from_python_storage<CType>*)
			data)->storage.bytes;

		// Use borrowed to construct the object so that a reference
		// count will be properly handled.
		handle<> hndl(borrowed(pObj));
		new (storage) CType(extract<PyType>(object(hndl)));

		// Stash the memory chunk pointer for later use by boost.python
		data->convertible = storage;
	}
};

template<typename Container>
struct pySequenceToCppContainerConverter
{
	static void registerConverter()
	{
		boost::python::converter::registry::push_back(
			&convertible,
			&construct,
			boost::python::type_id<Container>());
	}

	static void* convertible(PyObject* pObj)
	{
		if (!PySequence_Check(pObj))
			return nullptr;

		return pObj;
	}

	// Convert obj_ptr into a QString
	static void construct(PyObject* pObj,
						  boost::python::converter::rvalue_from_python_stage1_data* data)
	{
		using namespace boost::python;
		using value_type = Container::value_type;

		// Grab pointer to memory into which to construct the new QString
		void* storage = (
			(converter::rvalue_from_python_storage<Container>*)
			data)->storage.bytes;

		// Use borrowed to construct the object so that a reference
		// count will be properly handled.
		handle<> hndl(borrowed(pObj));
		new (storage) Container(boost::python::stl_input_iterator<value_type>(object(hndl)),
								boost::python::stl_input_iterator<value_type>());

		// Stash the memory chunk pointer for later use by boost.python
		data->convertible = storage;
	}
};
