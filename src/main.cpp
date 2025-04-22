#include <dpp/dpp.h>

const std::string BOT_TOKEN = getenv("BOT_TOKEN");

class my_http_server_request : public dpp::http_server_request {
public:
    [[nodiscard]] std::string get_path() const noexcept { return path; }
    [[nodiscard]] std::string get_method() const noexcept { return request_type; }
};

void handle_request(dpp::http_server_request& req, const std::string_view& content) {
    req.set_status(200)
       .set_response_header("Content-Type", "text/html")
       .set_response_body(content.data());
}

int main() {
    dpp::cluster bot(BOT_TOKEN);

    dpp::http_server server(&bot, "0.0.0.0", 3011, [](dpp::http_server_request* req_ptr) {
        auto* req = static_cast<my_http_server_request*>(req_ptr);

        if (req->get_method() == "GET") {
            if (req->get_path() == "/hello") {
                handle_request(*req, "<h1>Helo world</h1>");
                return;
            }
        }
        handle_request(*req, "<h1>Default endpoint</h1>");
    });

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t&) {
        std::cout << "Bot started as " << bot.me.username << '\n';
    });

    bot.start(dpp::st_wait);
    return 0;
}
