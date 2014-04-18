#include <iostream>
#include <string>
#include <memory>

#include "DependencyInjection/Registry.hpp"
#include "DependencyInjection/Inject.hpp"

// imagine simple web browser which downloads some content and diplays it

// stuff that downloads content - other parts of the system use IDownloader type

class IDownloader
{
public:
    virtual std::string download(std::string url) = 0;
    virtual ~IDownloader() {}
};

class HttpDownloader : public IDownloader
{
public:
    std::string download(std::string url)
    {
        std::cout << "downloading " << url << " through http" << std::endl;
        return url + " content";
    }
};

// subsystem which displays stuff, also, other parts sees it only through IDisplay

class IDisplay
{
public:
    virtual void show(std::string) = 0;
    virtual ~IDisplay() {}
};

class ConsoleDisplay : public IDisplay
{
public:
    void show(std::string what)
    {
        std::cout << what << std::endl;
    }
};

// our browser implementation

class Browser
{
public:
    void doStuff()
    {
        auto content = m_downloader->download("http://rusted.pl");

        // of course it doesn't have to be a class member so you can spare
        // some bytes when you need to do some things less often
        Cake::DependencyInjection::Inject<IDisplay> display;
        display->show(content);
    }

private:
    // we want to use IDownloader in our Browser, but we don't care how
    // it's created
    Cake::DependencyInjection::Inject<IDownloader> m_downloader;
};

// type binding and usage

int main()
{
    Cake::DependencyInjection::Registry r;

    // use concrete TYPE, which means that new instance will be created
    // each time when Inject is constructed
    r.forInterface<IDownloader>().use<HttpDownloader>();

    // we pass concrete object to use() function, so single instance will be
    // used acros application
    auto display = std::make_shared<ConsoleDisplay>();
    r.forInterface<IDisplay>().use(display);

    Browser b;
    b.doStuff();
}
