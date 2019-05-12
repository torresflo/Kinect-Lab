#ifndef UTILS_MEMORYHELPER_HPP
#define UTILS_MEMORYHELPER_HPP

#define SafeDelete(pointer) \
{							\
	if (pointer != nullptr) \
	{						\
		delete pointer;		\
		pointer = nullptr;	\
	}						\
}

#define SafeDeleteArray(pointer) \
{							\
	if (pointer != nullptr) \
	{						\
		delete[] pointer;	\
		pointer = nullptr;	\
	}						\
}

#endif //UTILS_MEMORYHELPER_HPP