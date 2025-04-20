#include <dpp/dpp.h>
// include http server

const std::string BOT_TOKEN = getenv("BOT_TOKEN");

void respond(dpp::http_server_request &request)
{
    // Handle the request and send a response
    request.set_status(200).set_response_header("Content-Type", "text/html").set_response_body("<h1>Hello, World!</h1>");
}

void response_to_hello(dpp::http_server_request &request)
{
    // Handle the request and send a response
    request.set_status(200).set_response_header("Content-Type", "text/html").set_response_body("<h1>Hello world from D++!</h1>");
}

class my_http_server_request : public dpp::http_server_request
{
public:
    std::string get_path() const
    {
        return path;
    }
    std::string get_method() const
    {
        return request_type;
    }
};

int main()
{

    dpp::cluster cluster = dpp::cluster();
    dpp::cluster bot(BOT_TOKEN);

    dpp::http_server *server{nullptr};
    server = new dpp::http_server(&cluster, "0.0.0.0", 3011, [&cluster](dpp::http_server_request* request) {
            my_http_server_request *req = static_cast<my_http_server_request*>(request);
            std::string method = req->get_method();
            std::string path = req->get_path();
            if(path == "/hello" && method == "GET")
            {
                response_to_hello(*request);
            }else {
                respond(*request);
            }
        });
    cluster.start(dpp::st_return); // Start the bot in blocking mode
    bot.on_slashcommand([](const dpp::slashcommand_t &event)
                        {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        } });

    bot.on_ready([&](const dpp::ready_t &event)
                 {


        std::cout << "Bot is ready! Logged in as " << bot.me.username << std::endl;
    });

    bot.start(dpp::st_wait); // Start the bot in blocking mode
    // Start the bot in a separate thread (non-blocking mode)
    std::cout << "Bot stopped." << std::endl;
    return 0;
}
