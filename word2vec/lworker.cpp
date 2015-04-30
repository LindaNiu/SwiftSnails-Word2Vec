#include "swiftsnails.h"
#include "word2vec_local2.h"
#define NDEBUG
using namespace swift_snails;
using namespace fms;
using namespace std;


int main(int argc, char* argv[]) {
    // init config
    CMDLine cmdline(argc, argv);
    string param_help = cmdline.registerParameter("help", "this screen");
    string param_config_path = cmdline.registerParameter("config", "path of config file");
    string param_data_path = cmdline.registerParameter("data", "path of dataset, text only!");
    // parse parameters
    if(cmdline.hasParameter(param_help) || argc == 1) {
        cout << endl;
        cout << "===================================================================" << endl;
        cout << "master server main program" << endl;
        cout << "===================================================================" << endl;
        cmdline.print_help();
        cout << endl;
        cout << endl;
        return 0;
    }
    if(!cmdline.hasParameter(param_config_path)) {
        LOG(ERROR) << "missing parameter: config";
        return 0;
    }
    if(!cmdline.hasParameter(param_data_path)) {
        LOG(ERROR) << "missing parameter: data";
        return 0;
    }
    std::string config_path;
    std::string data_path;
    if(cmdline.hasParameter(param_config_path)) {
        config_path = cmdline.getValue(param_config_path);
    }
    if(cmdline.hasParameter(param_data_path)) {
        data_path = cmdline.getValue(param_data_path);
    }

    global_config().load_conf(config_path);
    global_config().parse();

    int num_iters = global_config().get_config("num_iters").to_int32();
    int len_vec = global_config().get_config("len_vec").to_int32();
    int window = global_config().get_config("window").to_int32();
    int negative = global_config().get_config("negative").to_int32();
    /*
    SkipGram alg(num_iters, len_vec, window, negative);
    alg.set_data_path(data_path);

    SwiftWorker<SkipGram> worker(config_path, alg); 
    worker();
    */

    Word2Vec word2vec(data_path);
    //word2vec.train();
    SwiftWorker<Word2Vec> worker(config_path, word2vec); 
    word2vec();
    worker();

    return 0;
}

