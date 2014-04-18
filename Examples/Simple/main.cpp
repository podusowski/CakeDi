#include <iostream>

#include "DependencyInjection/Registry.hpp"
#include "DependencyInjection/Inject.hpp"

class IDownloader
{
public:
    virtual void download(std::string url) = 0;
    virtual ~IDownloader() {}
};

class HttpDownloader : public IDownloader
{
public:
    void download(std::string url)
    {
        std::cout << "downloading " << url << " through http" << std::endl;
    }
};

class Browser
{
public:
    void doStuff()
    {
        m_downloader->download("http://rusted.pl");
    }

private:
    Cake::DependencyInjection::Inject<IDownloader> m_downloader;
};

int main()
{
    Cake::DependencyInjection::Registry r;
    r.forInterface<IDownloader>().use<HttpDownloader>();

    Browser b;
    b.doStuff();
}
