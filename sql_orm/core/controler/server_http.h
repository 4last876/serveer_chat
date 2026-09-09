#include "../includes.h"

class IRoute{
    public:
    ~IRoute(){}

    virtual void route() = 0;

};

struct HeadeWM {
    struct context {};

    void before_handle(crow::request& req,crow::response& res,context& ctx) {
    res.add_header("Access-Control-Allow-Origin","*");
    }

    void after_handle(crow::request& req,crow::response& res,context& ctx) {
        std::cout << "Запрос обработан\n";
    }
};

class server{
    std::vector<std::shared_ptr<IRoute>> routes;
    crow::App<HeadeWM>& app;

    int port = 0;
    std::string host = "";



    public:

    server(crow::App<HeadeWM>& app_,std::string host_,int port_) : app(app_),host(host_),port(port_){
        app.multithreaded();
        app.bindaddr(host);
        app.port(port);
    }

    void run(){
        app.run();
    }

    void add_route(std::shared_ptr<IRoute> route){
    routes.push_back(route);
    }

    void init_routes(){
        for(auto& route : routes){
            route->route();
        }
    }
};
