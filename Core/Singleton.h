#ifndef _SINGLETON_H_
#define _SINGLETON_H_

// Outside ogre abstraction
template <typename T>
class ISingleton
{
	private:
		ISingleton(const ISingleton<T> &);
		ISingleton &operator=(const ISingleton<T> &);
		static void destroyInstance()
		{
			delete mInstance;
		}

	protected:
		static T *mInstance;

	public:
		ISingleton() 
		{
			mInstance = static_cast<T*>(this);

			// We don't wanna care about deleting global singleton-objects
			atexit(destroyInstance);
		}

		virtual ~ISingleton()
		{
			mInstance = 0;
		}

		static T &get()
		{
			if (!mInstance) mInstance = new T();
			return (*mInstance);
		}

		static T *getPtr()
		{
			if (!mInstance) mInstance = new T();
			return mInstance;
		}
};

#endif
