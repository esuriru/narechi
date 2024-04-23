namespace narechi::utils
{
    template<typename T>
    class singleton
    {
    public:
        static T& get()
        {
            static T instance;
            return instance;
        }

        // Remove copy operators
        void operator=(const singleton&) = delete;
        singleton(const singleton&) = delete;

    protected:
        singleton() {}
        virtual ~singleton() {}
    };
}