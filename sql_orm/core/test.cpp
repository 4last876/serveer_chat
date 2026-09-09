#include "dominal_model/model.h"
#include "repositories/api.h"
#include "service/chat_logic.h"
#include "controler/server_fasade.h"

int main(){
std::shared_ptr<DB_API> api = std::make_shared<SQLite_API>();
api->connect("lol.db");
std::shared_ptr<MODEL_API> repositories = std::make_shared<Specific_API_V1>(api);
std::shared_ptr<Ichat_logic> chat_logic_api = std::make_shared<chat_logic>(repositories);
std::shared_ptr<server_fasade> server_fasade_api = std::make_shared<server_fasade>(chat_logic_api,"192.168.1.10",9090);
server_fasade_api->run();
api->disconnect();
}
//JSON SOON