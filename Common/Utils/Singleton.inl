namespace Utils
{

template<typename T>
T* Singleton<T>::m_Instance = nullptr;

template <typename T>
inline T* Singleton<T>::getInstance()
{
    if(m_Instance == nullptr)
    {
        m_Instance = Singleton<T>::createInstance();
    }
    return m_Instance;
}

template <typename T>
Singleton<T>::Singleton()
{
    m_Instance = static_cast<T*>(this);
}

template <typename T>
Singleton<T>::~Singleton()
{
    if(m_Instance != nullptr)
    {
        delete m_Instance;
    }
    m_Instance = nullptr;
}

template <typename T>
T* Singleton<T>::createInstance()
{
    return new T();
}

}