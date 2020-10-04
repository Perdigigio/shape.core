#include "asset/image.hh"

#include "stream/reader.hh"
#include "stream/writer.hh"

#include "video/device.hh"
#include "video/buffer.hh"

struct REFDevice
{
	typedef typename intptr_t handle_t;
	typedef typename uint32_t offset_t;
	typedef typename uint32_t length_t;
	typedef typename uint32_t bitset_t;

	static int grab(intptr_t h)
	{
		//!
		//!

		return (h == 0) ? 0 : ++(*(int *)h);
	}

	static int drop(intptr_t h)
	{
		int ref = (h == 0) ? 0 : --(*(int *)h);

		//!
		//!

		if (ref == 0)
		{
			delete (int *)h;
		}

		//!
		//!

		return ref;
	}
};

#include <iostream>
#include <sstream>


int main()
{
	std::stringstream l_I;

	uint32_t l_flags =
		shape::CoreAssetImageFlags_HasW |
		shape::CoreAssetImageFlags_HasH |
		shape::CoreAssetImageFlags_HasD;

	shape::CoreAssetImage l_OImage{ l_flags, 8, 2, 2, 2 };
	shape::CoreAssetImage l_IImage;

	l_OImage.save<shape::CoreStreamWriter>(l_I.seekp(0));
	l_IImage.load<shape::CoreStreamReader>(l_I.seekg(0));

	if (l_IImage.save<shape::CoreStreamWriter>(std::cout)) shape::CoreError::error("Error (i'm lying)");
	if (!l_IImage.save<shape::CoreStreamWriter>(std::cout)) shape::CoreError::error("Error (not lying)");


	int * _1 = new int(1);
	int * _2 = new int(1);

	shape::CoreVideoDevice<REFDevice> l_device1((intptr_t)(_1));
	shape::CoreVideoDevice<REFDevice> l_device2((intptr_t)(_2));
	shape::CoreVideoDevice<REFDevice> l_device3;

	l_device3 = l_device1;
	l_device2 = l_device1;

	return 0;
}