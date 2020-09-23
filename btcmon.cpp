#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <curl/curl.h>
#include <CommCtrl.h>
#include <time.h>


using namespace std;

HCURSOR cross = LoadCursor(NULL, IDC_CROSS);
HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);

HFONT mainfont = CreateFont(18, 0 , 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

HFONT pricefont = CreateFont(34, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

HFONT axisfont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

HFONT yaxisfont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

//IDs
int CRRC = 201;
int COIN = 202;
int GRAPH = 203;

//initial dropdown selections
//usd
int init_curr = 8;
//btc
int init_coin = 22;

CURL *curl;

//currencies available on coingecko api
TCHAR currencies[55][10] =
{

  TEXT("btc"),
  TEXT("eth"),
  TEXT("ltc"),
  TEXT("bch"),
  TEXT("bnb"),
  TEXT("eos"),
  TEXT("xrp"),
  TEXT("xlm"),
  TEXT("usd"),
  TEXT("aed"),
  TEXT("ars"),
  TEXT("aud"),
  TEXT("bdt"),
  TEXT("bhd"),
  TEXT("bmd"),
  TEXT("brl"),
  TEXT("cad"),
  TEXT("chf"),
  TEXT("clp"),
  TEXT("cny"),
  TEXT("czk"),
  TEXT("dkk"),
  TEXT("eur"),
  TEXT("gbp"),
  TEXT("hkd"),
  TEXT("huf"),
  TEXT("idr"),
  TEXT("ils"),
  TEXT("inr"),
  TEXT("jpy"),
  TEXT("krw"),
  TEXT("kwd"),
  TEXT("lkr"),
  TEXT("mmk"),
  TEXT("mxn"),
  TEXT("myr"),
  TEXT("nok"),
  TEXT("nzd"),
  TEXT("php"),
  TEXT("pkr"),
  TEXT("pln"),
  TEXT("rub"),
  TEXT("sar"),
  TEXT("sek"),
  TEXT("sgd"),
  TEXT("thb"),
  TEXT("try"),
  TEXT("twd"),
  TEXT("uah"),
  TEXT("vef"),
  TEXT("vnd"),
  TEXT("zar"),
  TEXT("xdr"),
  TEXT("xag"),
  TEXT("xau")

};

//200+ most popular coins according to some website
TCHAR coins [221][3][30] =
{
    //id , symbol, name
    { TEXT("0x") , TEXT("zrx") , TEXT("0x") },
    { TEXT("aelf") , TEXT("elf") , TEXT("aelf") },
    { TEXT("aeternity") , TEXT("ae") , TEXT("Aeternity") },
    { TEXT("aion") , TEXT("aion") , TEXT("Aion") },
    { TEXT("akropolis") , TEXT("akro") , TEXT("Akropolis") },
    { TEXT("algorand") , TEXT("algo") , TEXT("Algorand") },
    { TEXT("alibabacoin") , TEXT("abbc") , TEXT("ABBC") },
    { TEXT("ampleforth") , TEXT("ampl") , TEXT("Ampleforth") },
    { TEXT("ankr") , TEXT("ankr") , TEXT("Ankr") },
    { TEXT("aragon") , TEXT("ant") , TEXT("Aragon") },
    { TEXT("ardor") , TEXT("ardr") , TEXT("Ardor") },
    { TEXT("ark") , TEXT("ark") , TEXT("Ark") },
    { TEXT("augur") , TEXT("rep") , TEXT("Augur") },
    { TEXT("aurora") , TEXT("aoa") , TEXT("Aurora") },
    { TEXT("balancer") , TEXT("bal") , TEXT("Balancer") },
    { TEXT("bancor") , TEXT("bnt") , TEXT("Bancor Network Token") },
    { TEXT("band-protocol") , TEXT("band") , TEXT("Band Protocol") },
    { TEXT("basic-attention-token") , TEXT("bat") , TEXT("Basic Attention Token") },
    { TEXT("beam") , TEXT("beam") , TEXT("BEAM") },
    { TEXT("beats-token") , TEXT("bts") , TEXT("Beats Token") },
    { TEXT("binancecoin") , TEXT("bnb") , TEXT("Binance Coin") },
    { TEXT("binance-usd") , TEXT("busd") , TEXT("Binance USD") },
    { TEXT("bitcoin") , TEXT("btc") , TEXT("Bitcoin") },
    { TEXT("bitcoin-cash") , TEXT("bch") , TEXT("Bitcoin Cash") },
    { TEXT("bitcoin-cash-sv") , TEXT("bsv") , TEXT("Bitcoin SV") },
    { TEXT("bitcoin-diamond") , TEXT("bcd") , TEXT("Bitcoin Diamond") },
    { TEXT("bitcoin-gold") , TEXT("btg") , TEXT("Bitcoin Gold") },
    { TEXT("bitflexo-native-token") , TEXT("bnt") , TEXT("BitFlexo Native Token") },
    { TEXT("bitshares") , TEXT("bts") , TEXT("BitShares") },
    { TEXT("bittorrent-2") , TEXT("btt") , TEXT("BitTorrent") },
    { TEXT("blockstack") , TEXT("stx") , TEXT("Blockstack") },
    { TEXT("blocktrade") , TEXT("btt") , TEXT("Blocktrade") },
    { TEXT("bluzelle") , TEXT("blz") , TEXT("Bluzelle") },
    { TEXT("bora") , TEXT("bora") , TEXT("BORA") },
    { TEXT("bytecoin") , TEXT("bcn") , TEXT("Bytecoin") },
    { TEXT("bytom") , TEXT("btm") , TEXT("Bytom") },
    { TEXT("bzx-protocol") , TEXT("bzrx") , TEXT("bZx Protocol") },
    { TEXT("cardano") , TEXT("ada") , TEXT("Cardano") },
    { TEXT("celer-network") , TEXT("celr") , TEXT("Celer Network") },
    { TEXT("celsius-degree-token") , TEXT("cel") , TEXT("Celsius Network") },
    { TEXT("chainlink") , TEXT("link") , TEXT("ChainLink") },
    { TEXT("chiliz") , TEXT("chz") , TEXT("Chiliz") },
    { TEXT("compound-coin") , TEXT("comp") , TEXT("Compound Coin") },
    { TEXT("compound-governance-token") , TEXT("comp") , TEXT("Compound") },
    { TEXT("concertvr") , TEXT("cvt") , TEXT("concertVR") },
    { TEXT("concierge-io") , TEXT("ava") , TEXT("Travala.com") },
    { TEXT("cortex") , TEXT("ctxc") , TEXT("Cortex") },
    { TEXT("cosmos") , TEXT("atom") , TEXT("Cosmos") },
    { TEXT("coti") , TEXT("coti") , TEXT("COTI") },
    { TEXT("cronos-coin") , TEXT("cro") , TEXT("Cronos Coin") },
    { TEXT("crypterium") , TEXT("crpt") , TEXT("Crypterium") },
    { TEXT("crypto-com-chain") , TEXT("cro") , TEXT("Crypto.com Coin") },
    { TEXT("cybervein") , TEXT("cvt") , TEXT("CyberVeinToken") },
    { TEXT("dai") , TEXT("dai") , TEXT("Dai") },
    { TEXT("dash") , TEXT("dash") , TEXT("Dash") },
    { TEXT("decentraland") , TEXT("mana") , TEXT("Decentraland") },
    { TEXT("decentralized-advertising") , TEXT("dad") , TEXT("DAD") },
    { TEXT("decred") , TEXT("dcr") , TEXT("Decred") },
    { TEXT("dent") , TEXT("dent") , TEXT("Dent") },
    { TEXT("digibyte") , TEXT("dgb") , TEXT("DigiByte") },
    { TEXT("digitex-futures-exchange") , TEXT("dgtx") , TEXT("Digitex Futures Exchange") },
    { TEXT("divi") , TEXT("divi") , TEXT("Divi") },
    { TEXT("dogecoin") , TEXT("doge") , TEXT("Dogecoin") },
    { TEXT("dxchain") , TEXT("dx") , TEXT("DxChain Token") },
    { TEXT("elastos") , TEXT("ela") , TEXT("Elastos") },
    { TEXT("eldorado-token") , TEXT("erd") , TEXT("ELDORADO TOKEN") },
    { TEXT("electroneum") , TEXT("etn") , TEXT("Electroneum") },
    { TEXT("elrond") , TEXT("erd") , TEXT("Elrond") },
    { TEXT("energi") , TEXT("nrg") , TEXT("Energi") },
    { TEXT("energy-web-token") , TEXT("ewt") , TEXT("Energy Web Token") },
    { TEXT("enjincoin") , TEXT("enj") , TEXT("Enjin Coin") },
    { TEXT("eos") , TEXT("eos") , TEXT("EOS") },
    { TEXT("ethereum") , TEXT("eth") , TEXT("Ethereum") },
    { TEXT("ethereum-classic") , TEXT("etc") , TEXT("Ethereum Classic") },
    { TEXT("ethlend") , TEXT("lend") , TEXT("Aave") },
    { TEXT("ethos") , TEXT("vgx") , TEXT("Voyager Token") },
    { TEXT("fantom") , TEXT("ftm") , TEXT("Fantom") },
    { TEXT("farmatrust") , TEXT("ftt") , TEXT("FarmaTrust") },
    { TEXT("fetch-ai") , TEXT("fet") , TEXT("Fetch.ai") },
    { TEXT("firstenergy-token") , TEXT("fet") , TEXT("FirstEnergy Token") },
    { TEXT("flexacoin") , TEXT("fxc") , TEXT("Flexacoin") },
    { TEXT("freetip") , TEXT("ftt") , TEXT("FreeTip") },
    { TEXT("fsn") , TEXT("fsn") , TEXT("FUSION") },
    { TEXT("ftx-token") , TEXT("ftt") , TEXT("FTX Token") },
    { TEXT("funfair") , TEXT("fun") , TEXT("FunFair") },
    { TEXT("game-x-coin") , TEXT("gxc") , TEXT("GameXCoin") },
    { TEXT("gatechain-token") , TEXT("gt") , TEXT("Gatechain Token") },
    { TEXT("gdac-token") , TEXT("gt") , TEXT("GDAC Token") },
    { TEXT("gnosis") , TEXT("gno") , TEXT("Gnosis") },
    { TEXT("golem") , TEXT("gnt") , TEXT("Golem") },
    { TEXT("grin") , TEXT("grin") , TEXT("Grin") },
    { TEXT("gxchain") , TEXT("gxc") , TEXT("GXChain") },
    { TEXT("harmony") , TEXT("one") , TEXT("Harmony") },
    { TEXT("havven") , TEXT("snx") , TEXT("Synthetix Network Token") },
    { TEXT("hedera-hashgraph") , TEXT("hbar") , TEXT("Hedera Hashgraph") },
    { TEXT("hedgetrade") , TEXT("hedg") , TEXT("HedgeTrade") },
    { TEXT("hive") , TEXT("hive") , TEXT("Hive") },
    { TEXT("holotoken") , TEXT("hot") , TEXT("Holo") },
    { TEXT("hotnow") , TEXT("hot") , TEXT("HotNow") },
    { TEXT("hshare") , TEXT("hc") , TEXT("HyperCash") },
    { TEXT("huobi-pool-token") , TEXT("hpt") , TEXT("Huobi Pool Token") },
    { TEXT("huobi-token") , TEXT("ht") , TEXT("Huobi Token") },
    { TEXT("husd") , TEXT("husd") , TEXT("HUSD") },
    { TEXT("hydro-protocol") , TEXT("hot") , TEXT("Hydro Protocol") },
    { TEXT("hyperion") , TEXT("hyn") , TEXT("Hyperion") },
    { TEXT("icon") , TEXT("icx") , TEXT("ICON") },
    { TEXT("iexec-rlc") , TEXT("rlc") , TEXT("iExec RLC") },
    { TEXT("iostoken") , TEXT("iost") , TEXT("IOST") },
    { TEXT("iota") , TEXT("miota") , TEXT("IOTA") },
    { TEXT("iotex") , TEXT("iotx") , TEXT("IoTeX") },
    { TEXT("iris-network") , TEXT("iris") , TEXT("IRISnet") },
    { TEXT("just") , TEXT("jst") , TEXT("JUST") },
    { TEXT("kava") , TEXT("kava") , TEXT("Kava") },
    { TEXT("kleros") , TEXT("pnk") , TEXT("Kleros") },
    { TEXT("komodo") , TEXT("kmd") , TEXT("Komodo") },
    { TEXT("kucoin-shares") , TEXT("kcs") , TEXT("KuCoin Shares") },
    { TEXT("kusama") , TEXT("ksm") , TEXT("Kusama") },
    { TEXT("kyber-network") , TEXT("knc") , TEXT("Kyber Network") },
    { TEXT("leo-token") , TEXT("leo") , TEXT("LEO Token") },
    { TEXT("lisk") , TEXT("lsk") , TEXT("Lisk") },
    { TEXT("litecoin") , TEXT("ltc") , TEXT("Litecoin") },
    { TEXT("loki-network") , TEXT("loki") , TEXT("Loki Network") },
    { TEXT("loopring") , TEXT("lrc") , TEXT("Loopring") },
    { TEXT("maidsafecoin") , TEXT("maid") , TEXT("MaidSafeCoin") },
    { TEXT("maker") , TEXT("mkr") , TEXT("Maker") },
    { TEXT("matic-network") , TEXT("matic") , TEXT("Matic Network") },
    { TEXT("melon") , TEXT("mln") , TEXT("Melon") },
    { TEXT("menlo-one") , TEXT("one") , TEXT("Menlo One") },
    { TEXT("molecular-future") , TEXT("mof") , TEXT("Molecular Future") },
    { TEXT("monaco") , TEXT("mco") , TEXT("MCO") },
    { TEXT("monacoin") , TEXT("mona") , TEXT("MonaCoin") },
    { TEXT("monero") , TEXT("xmr") , TEXT("Monero") },
    { TEXT("monexcoin") , TEXT("mxc") , TEXT("Monexcoin") },
    { TEXT("mxc") , TEXT("mxc") , TEXT("Machine Xchange Coin") },
    { TEXT("nano") , TEXT("nano") , TEXT("Nano") },
    { TEXT("nem") , TEXT("xem") , TEXT("NEM") },
    { TEXT("neo") , TEXT("neo") , TEXT("NEO") },
    { TEXT("nervos-network") , TEXT("ckb") , TEXT("Nervos Network") },
    { TEXT("nexo") , TEXT("nexo") , TEXT("NEXO") },
    { TEXT("nimiq-2") , TEXT("nim") , TEXT("Nimiq") },
    { TEXT("nuls") , TEXT("nuls") , TEXT("Nuls") },
    { TEXT("numeraire") , TEXT("nmr") , TEXT("Numeraire") },
    { TEXT("ocean-protocol") , TEXT("ocean") , TEXT("Ocean Protocol") },
    { TEXT("okb") , TEXT("okb") , TEXT("OKB") },
    { TEXT("omisego") , TEXT("omg") , TEXT("OMG Network") },
    { TEXT("one") , TEXT("one") , TEXT("One") },
    { TEXT("ontology") , TEXT("ont") , TEXT("Ontology") },
    { TEXT("orbs") , TEXT("orbs") , TEXT("Orbs") },
    { TEXT("origin-protocol") , TEXT("ogn") , TEXT("Origin Protocol") },
    { TEXT("origintrail") , TEXT("trac") , TEXT("OriginTrail") },
    { TEXT("pax-gold") , TEXT("paxg") , TEXT("PAX Gold") },
    { TEXT("paxos-standard") , TEXT("pax") , TEXT("Paxos Standard") },
    { TEXT("penta") , TEXT("pnt") , TEXT("Penta Network Token") },
    { TEXT("perlin") , TEXT("perl") , TEXT("Perlin") },
    { TEXT("pivx") , TEXT("pivx") , TEXT("PIVX") },
    { TEXT("pnetwork") , TEXT("pnt") , TEXT("pNetwork") },
    { TEXT("power-ledger") , TEXT("powr") , TEXT("Power Ledger") },
    { TEXT("project-pai") , TEXT("pai") , TEXT("Project Pai") },
    { TEXT("pundi-x") , TEXT("npxs") , TEXT("Pundi X") },
    { TEXT("qtum") , TEXT("qtum") , TEXT("Qtum") },
    { TEXT("quant-network") , TEXT("qnt") , TEXT("Quant") },
    { TEXT("ravencoin") , TEXT("rvn") , TEXT("Ravencoin") },
    { TEXT("reddcoin") , TEXT("rdd") , TEXT("Reddcoin") },
    { TEXT("republic-protocol") , TEXT("ren") , TEXT("REN") },
    { TEXT("request-network") , TEXT("req") , TEXT("Request") },
    { TEXT("reserve-rights-token") , TEXT("rsr") , TEXT("Reserve Rights Token") },
    { TEXT("rif-token") , TEXT("rif") , TEXT("RIF Token") },
    { TEXT("ripio-credit-network") , TEXT("rcn") , TEXT("Ripio Credit Network") },
    { TEXT("ripple") , TEXT("xrp") , TEXT("XRP") },
    { TEXT("siacoin") , TEXT("sc") , TEXT("Siacoin") },
    { TEXT("solana") , TEXT("sol") , TEXT("Solana") },
    { TEXT("solve-care") , TEXT("solve") , TEXT("SOLVE") },
    { TEXT("stasis-eurs") , TEXT("eurs") , TEXT("STASIS EURO") },
    { TEXT("steem") , TEXT("steem") , TEXT("Steem") },
    { TEXT("stellar") , TEXT("xlm") , TEXT("Stellar") },
    { TEXT("storj") , TEXT("storj") , TEXT("Storj") },
    { TEXT("stox") , TEXT("stx") , TEXT("Stox") },
    { TEXT("stratis") , TEXT("strat") , TEXT("Stratis") },
    { TEXT("streamr-datacoin") , TEXT("data") , TEXT("Streamr DATAcoin") },
    { TEXT("super-zero") , TEXT("sero") , TEXT("SERO") },
    { TEXT("swipe") , TEXT("sxp") , TEXT("Swipe") },
    { TEXT("swissborg") , TEXT("chsb") , TEXT("SwissBorg") },
    { TEXT("switcheo") , TEXT("swth") , TEXT("Switcheo") },
    { TEXT("syscoin") , TEXT("sys") , TEXT("Syscoin") },
    { TEXT("terra-luna") , TEXT("luna") , TEXT("Terra") },
    { TEXT("tether") , TEXT("usdt") , TEXT("Tether") },
    { TEXT("tezos") , TEXT("xtz") , TEXT("Tezos") },
    { TEXT("tezos-iou") , TEXT("xtz") , TEXT("Tezos IOU") },
    { TEXT("the-midas-touch-gold") , TEXT("tmtg") , TEXT("The Midas Touch Gold") },
    { TEXT("theta-fuel") , TEXT("tfuel") , TEXT("Theta Fuel") },
    { TEXT("theta-token") , TEXT("theta") , TEXT("Theta Network") },
    { TEXT("thorchain") , TEXT("rune") , TEXT("Thorchain") },
    { TEXT("thunder-token") , TEXT("tt") , TEXT("ThunderCore") },
    { TEXT("tomochain") , TEXT("tomo") , TEXT("TomoChain") },
    { TEXT("tron") , TEXT("trx") , TEXT("TRON") },
    { TEXT("true-usd") , TEXT("tusd") , TEXT("TrueUSD") },
    { TEXT("unibright") , TEXT("ubt") , TEXT("Unibright") },
    { TEXT("usd-coin") , TEXT("usdc") , TEXT("USD Coin") },
    { TEXT("utrust") , TEXT("utk") , TEXT("UTRUST") },
    { TEXT("valix") , TEXT("vlx") , TEXT("Vallix") },
    { TEXT("vechain") , TEXT("vet") , TEXT("VeChain") },
    { TEXT("velas") , TEXT("vlx") , TEXT("Velas") },
    { TEXT("verge") , TEXT("xvg") , TEXT("Verge") },
    { TEXT("vethor-token") , TEXT("vtho") , TEXT("VeThor Token") },
    { TEXT("v-id-blockchain") , TEXT("vidt") , TEXT("V-ID blockchain") },
    { TEXT("v-systems") , TEXT("vsys") , TEXT("V.SYSTEMS") },
    { TEXT("waltonchain") , TEXT("wtc") , TEXT("Waltonchain") },
    { TEXT("wanchain") , TEXT("wan") , TEXT("Wanchain") },
    { TEXT("waves") , TEXT("waves") , TEXT("Waves") },
    { TEXT("wawllet") , TEXT("win") , TEXT("WCoin") },
    { TEXT("wax") , TEXT("waxp") , TEXT("WAX") },
    { TEXT("waykichain") , TEXT("wicc") , TEXT("WaykiChain") },
    { TEXT("wazirx") , TEXT("wrx") , TEXT("WazirX") },
    { TEXT("wink") , TEXT("win") , TEXT("WINk") },
    { TEXT("wirex") , TEXT("wxt") , TEXT("Wirex") },
    { TEXT("zb-token") , TEXT("zb") , TEXT("ZB Token") },
    { TEXT("zcash") , TEXT("zec") , TEXT("Zcash") },
    { TEXT("zcoin") , TEXT("xzc") , TEXT("Zcoin") },
    { TEXT("zencash") , TEXT("zen") , TEXT("Horizen") },
    { TEXT("zerobank") , TEXT("zb") , TEXT("ZeroBank") },
    { TEXT("zilliqa") , TEXT("zil") , TEXT("Zilliqa") }

};

//storing timestamps and price values for graph, as recd from api
struct grawdata {
    long int tst = 0;
    double price = 0;
    string label = "";
};

//this is the final data which will be used to plot the graph
struct gdata {
    int x = 0;
    int y = 0;
    string label = "";
};

struct notch {
    int coord = 0;
    string label = "";
};

grawdata json_dump[800];
gdata coords[300];
//x axis map (not the graph line)
//time label for each x pixel
string xmap[1200];
//same but with price labels for y
string ymap[1200];
//notches
notch xnotch[1300];
notch ynotch[1300];

int gx = 110;
//gx,gy is the lower left corner
int gy = 500;
int ypadding = 10;
int xpadding = 10;
int notch_xpad = 100;
int notch_ypad = 100;
int gheight = 400;
int gwidth = 800;
int gstatus = 0;

bool mouse_over_graph = false;
//whether mouse is over/close to a graph coord
int cfocus = -1;
int cfocus_x_final = 0;
int cfocus_y_final = 0;
int old_mouse_x = 0;
int old_mouse_y = 0;
int mouse_x = 0;
int mouse_y = 0;
int mouse_dx = 0;
int mouse_dy = 0;

//used as region to update in redrawwindow
POINT upd[12];

int min_idx = 0;
int max_idx = 0;
string minpricestr;
string maxpricestr;

string str_price = "loading.";
double cur_price = 0;
double old_price = 0;

string coin_ratio = ": 1";
int coin_sz = coin_ratio.size();
LPCSTR coinptr = coin_ratio.c_str();

string glabel = "graph:";
int glabelsz = glabel.size();
LPCSTR glabelptr = glabel.c_str();


HPEN blackpen = CreatePen(PS_SOLID,2,RGB(0,0,0));
HPEN axespen = CreatePen(PS_SOLID, 2, RGB(200, 200, 200));
HPEN hilopen = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
HPEN bluepen = CreatePen(PS_SOLID, 1, RGB(100, 100, 255));
HPEN outerbluepen1 = CreatePen(PS_SOLID, 2, RGB(120, 120, 255));
HPEN outerbluepen2 = CreatePen(PS_SOLID, 4, RGB(200, 200, 255));
HPEN outerbluepen3 = CreatePen(PS_SOLID, 8, RGB(220, 220, 255));

string ids = coins[init_coin][0];
string vcs = currencies[init_curr];
string price_url = "https://api.coingecko.com/api/v3/simple/price";
string final_url = price_url + "?ids=" + ids + "&vs_currencies=" + vcs;
string api_days[4] = {"1","7","30","365"};


//update every n milliseconds
static int update_interval = 2000;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CryptoWindowsApp");


//auto resize y axis text
void ytxtauto() {
    DeleteObject(yaxisfont);
    int maxl = minpricestr.length();
    int fsize = 20;
    if ((int) maxpricestr.length() > maxl) {
        maxl = maxpricestr.length();
    }
    if (maxl > 10) {
        fsize = 20 - (maxl/3);
    }

    yaxisfont = CreateFont(fsize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
}


//math formatting of price string
string prettystr(string pstr) {
    string outstr = "";
    bool dec = false;
    if (pstr.find(".") != string::npos) {
        dec = true;
    }
    else {
        dec = false;
    }
    //add commas for numbers over 999
    int ccount = 0;
    for (int c = pstr.length(); c-- > 0; ){ // c goes to zero
        if (dec) {
            if (pstr[c] == '.') {
                //if there is a decimal point only show two digits after it
                outstr = pstr.substr(c, 3);
                dec = false;
            }
        }
        else {
            ccount++;
            //every third character, add a comma in front
            if ((ccount > 2) & (c!=0)) {
                outstr = "," + pstr.substr(c, 1) + outstr;
                ccount = 0;
            }
            else {
                outstr = pstr.substr(c, 1) + outstr;
            }
        }
    }
    return outstr;
}


size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void start_curl(string &output,string addr) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, addr.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
    }
}

void stop_curl() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    curl = NULL;
}

void get_graph(string coin, string currency, string days) {


    //api elements for 30d: 722 (hourly), 7d: 168 (hourly), 1d : 287 (5 minutely) 
    //0 for high-low, 0< no. of hourly intervals, e.g. every 4 hours
    
    int mode = 4;
    if (days=="30"){
        mode = 4;
    }
    if (days == "7") {
        mode = 1;
    }
    if (days == "1") {
        mode = 2;
    }
    string url;
    string raw;
    string elmnt;
    char outp[200];
    int start = 0;
    int end;
    int ct = 0;
    long tst;
    std::string::size_type sz;
    time_t rawtime;
    struct tm timeinfo;

    url = "https://api.coingecko.com/api/v3/coins/"+coin+"/market_chart?vs_currency="+currency+"&days="+days;

    stop_curl();
    start_curl(raw, url);
    curl_easy_perform(curl);
    stop_curl();
    start_curl(str_price, final_url);

    start = raw.find(":") + 2;
    raw = raw.substr(start);
    end = raw.find("]]");
    raw = raw.substr(0,end);
    end = 0;

    double gmax = 0;
    double gmin = 0;
    double gstepy;

    string tempt;
    double temppr;

    double hi = 0;
    long hitst = 0;
    string hilbl = "";
    double lo = 0;
    long lotst = 0;
    string lolbl = "";

    tm cdate;
    cdate.tm_year = 0;
    cdate.tm_mday = 0;
    cdate.tm_mon = 0;
    int idx = 0;

    while (raw.find("[",start) != std::string::npos) {
        ct++;

        start = raw.find("[", end) + 1;
        end = raw.find("]",start);
        elmnt = raw.substr(start, end-start);
        //here we reduce the timestamp given by coingecko, from ms to s
        tempt = elmnt.substr(0,10);
        //price
        temppr = stod(elmnt.substr(elmnt.find(",") + 1));

        
        tst = stol(tempt,&sz);
        rawtime = (const time_t)tst;
        localtime_s(&timeinfo,&rawtime);

        //high-low mode is 0 or anything below
        if (mode < 1) {
            //see if this is the highest or lowest price for this day - only then will it be used for the graph
            if ((cdate.tm_year == timeinfo.tm_year) & (cdate.tm_mon == timeinfo.tm_mon) & (cdate.tm_mday == timeinfo.tm_mday)) {
                if (temppr > hi) {
                    hi = temppr;
                    hitst = tst;
                    strftime(outp, sizeof(outp), " @ %H:%M %d %b", &timeinfo);
                    hilbl = elmnt.substr(elmnt.find(",") + 1);
                    hilbl = prettystr(hilbl);
                    hilbl = hilbl + outp;

                }
                if (temppr < lo) {
                    lo = temppr;
                    lotst = tst;
                    strftime(outp, sizeof(outp), " @ %H:%M %d %b", &timeinfo);
                    lolbl = elmnt.substr(elmnt.find(",") + 1);
                    lolbl = prettystr(lolbl);
                    lolbl = lolbl + outp;
                }
            }
            //if we've changed date then update the current date
            //and set this first price val as both highest and lowest for this day
            //but first store the highest and lowest etc for the previous day
            //unless we're on the first loop iteration in which case we update first and store after
            else {

                if (ct != 1) {
                    //store in chronological order
                    if (lotst < hitst) {
                        json_dump[idx].price = lo;
                        json_dump[idx].tst = lotst;
                        json_dump[idx].label = lolbl;

                        idx++;

                        json_dump[idx].price = hi;
                        json_dump[idx].tst = hitst;
                        json_dump[idx].label = hilbl;

                        idx++;
                    }
                    else {
                        json_dump[idx].price = hi;
                        json_dump[idx].tst = hitst;
                        json_dump[idx].label = hilbl;

                        idx++;

                        json_dump[idx].price = lo;
                        json_dump[idx].tst = lotst;
                        json_dump[idx].label = lolbl;

                        idx++;
                    }
                }


                /*
                if ((ct > 650) || (ct < 11)) {
                    if (cdate.tm_year != 0) {
                        strftime(outp, sizeof(outp), "hi - lo results for date: %H:%M:%S %d %m %y\n", &cdate);
                        OutputDebugString(outp);
                    }
                    sprintf_s(outp, 200, "hi: %.12f\n", hi);
                    OutputDebugString(outp);
                    sprintf_s(outp, 200, "lo: %.12f\n", lo);
                    OutputDebugString(outp);
                }*/

                cdate = timeinfo;
                hi = temppr;
                hitst = tst;
                lo = temppr;
                lotst = tst;
                strftime(outp, sizeof(outp), " @ %H:%M %d %b", &timeinfo);
                lolbl = elmnt.substr(elmnt.find(",") + 1);
                lolbl = prettystr(lolbl);
                lolbl = lolbl + outp;
                hilbl = lolbl;



            }
        } //end of mode 0 or -ve (hi-lo)
        else {

        //hourly interval mode

            //if we reached the number of hours in mode, dump json
            if (ct > mode) {

                strftime(outp, sizeof(outp), " @ %H:%M %d %b", &timeinfo);

                json_dump[idx].price = temppr;
                json_dump[idx].tst = tst;
                json_dump[idx].label = prettystr(to_string(temppr)) + outp; 

                idx++;
                ct = 0;
            }
        }

    }/*end of while loop*/

    //if we're high-low mode
    if (mode < 1) {
        //this is done because at the end of the while loop no change of date is detected
        //so we need to store high and low info in chronological order
        if (lotst < hitst) {
            json_dump[idx].price = lo;
            json_dump[idx].tst = lotst;
            json_dump[idx].label = lolbl;

            idx++;

            json_dump[idx].price = hi;
            json_dump[idx].tst = hitst;
            json_dump[idx].label = hilbl;

            idx++;
        }
        else {
            json_dump[idx].price = hi;
            json_dump[idx].tst = hitst;
            json_dump[idx].label = hilbl;

            idx++;

            json_dump[idx].price = lo;
            json_dump[idx].tst = lotst;
            json_dump[idx].label = lolbl;

            idx++;
        }
    }

    int k = 0;
    gmin = json_dump[k].price;
    gmax = json_dump[k].price;

    for (k = 0; k < idx; k++) {

        if (json_dump[k].price > gmax) {
            gmax = json_dump[k].price;
            max_idx = k;
        }
        if (json_dump[k].price < gmin) {
            gmin = json_dump[k].price;
            min_idx = k;
        }

        sprintf_s(outp, 200, "item %d\n", k);
        OutputDebugString(outp);
        sprintf_s(outp, 200, "price: %f\n", json_dump[k].price);
        OutputDebugString(outp);
        sprintf_s(outp, 200, "tst: %ld\n", json_dump[k].tst);
        OutputDebugString(outp);
        OutputDebugString(json_dump[k].label.c_str());
        OutputDebugString("\n");
    }

    sprintf_s(outp, 200, "max price: %f\n", gmax);
    OutputDebugString(outp);
    sprintf_s(outp, 200, "min price: %f\n", gmin);
    OutputDebugString(outp);
    //sprintf_s(outp, 200, "json_dump[min_idx].price: %f\n", json_dump[min_idx].price);
    //OutputDebugString(outp);

    //only useful in hilo mode:
    //sprintf_s(outp, 200, "total elements in array are %d\n", ct);
    //OutputDebugString(outp);

    


    //the price in each y pixel 
    gstepy =  ( (gmax-gmin)/(gheight));
    //seconds in each x pixel for tst , for x axis 
    int gstepxs = 1; // done to avoid IDE warnings
    if (idx > 0) { // done to avoid IDE warnings
        gstepxs = (int)(json_dump[idx - 1].tst - json_dump[0].tst) / gwidth;
    }
    
    for (k = 0; k <= idx; k++) {
        if (k == idx) {
            coords[k].label = "[end]";
            //the last x coord is the graph width
            //nb: this can only be done right at the end, because gwidth is 
            //used to calculate the hours in each xpixel
            if (k > 0) {//this is done purely to avoid IDE warnings
                gwidth = coords[k - 1].x;
            }
        }
        else {
            //arbitrary number to make it small enough to fit the window
            coords[k].x = (json_dump[k].tst - json_dump[0].tst)/((json_dump[idx - 1].tst - json_dump[0].tst) / gwidth);
            coords[k].y = (int) (( json_dump[k].price - gmin)/gstepy);
            coords[k].label = json_dump[k].label;
        }
    }
    
    //the price for each y axis pixel is stored in ymap
    double tempstep = 0;
    int nidy = 0;

    for (k = 0; k < gheight; k++) {
        tempstep = k * gstepy;
        ymap[k] = prettystr(to_string(gmin + tempstep));
        //for now just the first and last y pixels have notches
        if (k == 0) {
            ynotch[nidy].label = ymap[k];
            ynotch[nidy].coord = k;
            nidy++;
        } 
        if (k == (gheight - 1)) {
            ynotch[nidy].label = ymap[k];
            ynotch[nidy].coord = k;
            nidy++;
            ynotch[nidy].label = "[end]";
        }
    }

    //the time and date for each x axis pixel is stored in xmap
    int last_date = 0;
    int current_date = 0;
    int nidx = 0;
    //how many times the x axis will be divided into labeled notches
    int xdivs = 3;
    int xdstep;
    if ((days == "7") || (days == "30")) {
        xdstep = (int)(stoi(days) / xdivs);
    }
    if (days == "365") {
        xdstep = (int)(12 / xdivs);
    }
    if (days == "1") {
        xdstep = (int)(24 / xdivs);
    }

    //clean xnotch array - otherwise it will mess up if its not the first use
    for (k = 0; k < 1300; k++) {
        xnotch[k].coord = 0;
        xnotch[k].label = "";
    }

    for (k = 0; k < gwidth; k++) {
        //sprintf_s(outp, 200, "iteration no: %d\n", k);
        //OutputDebugString(outp);
        tst = json_dump[0].tst + (k* gstepxs);
        rawtime = (const time_t)tst;
        localtime_s(&timeinfo, &rawtime);
        if (k == 0) {
            //if looking at one year then only go month by month - if 7/30d day by day - if 24h hour by hour
            if ((days == "7") || (days=="30")) {
                last_date = timeinfo.tm_mday;
            }
            if (days == "365") {
                last_date = timeinfo.tm_mon;
            }
            if (days == "1") {
                last_date = timeinfo.tm_hour;
            }
        }
        else {
            if ((days == "7") || (days == "30")) {
                current_date = timeinfo.tm_mday;
            }
            if (days == "365") {
                current_date = timeinfo.tm_mon;
            }
            if (days == "1") {
                current_date = timeinfo.tm_hour;
            }
            if (last_date != current_date) {
                //date has changed, add a notch on x axis
                xnotch[nidx].coord = k;
                
                if ((days == "7") || (days == "30")) {
                    strftime(outp, sizeof(outp), "%d %b", &timeinfo);
                }
                if (days == "365") {
                    strftime(outp, sizeof(outp), "%d %b '%y", &timeinfo);
                }
                if (days == "1") {
                    //should be %H:%M but its rounded to 00 because sometimes it comes out as :01 or :02
                    strftime(outp, sizeof(outp), "%H:00 %d %b", &timeinfo);
                }
                //the first and last notches are always labeled + larger
                if (nidx == 0) {
                    xnotch[nidx].label = outp;
                }
                else {
                    //labeled notches between first and last (based on xdivs)
                    int xd = 1;
                    for (xd = 1; xd <= xdivs; xd++) {
                        if (nidx == (xd * xdstep)) {
                            xnotch[nidx].label = outp;
                            break;
                        }
                    }
                }
                nidx++;
                if ((days == "7") || (days == "30")) {
                    last_date = timeinfo.tm_mday;
                }
                if (days == "365") {
                    last_date = timeinfo.tm_mon;
                }
                if (days == "1") {
                    last_date = timeinfo.tm_hour;
                }
            }
        }

        strftime(outp, sizeof(outp), "%H:%M %d %b", &timeinfo);
        xmap[k] = outp;
        if (k == (gwidth - 1)) {
            xmap[k + 1] = "[end]";
            if ((days == "7") || (days == "30")) {
                strftime(outp, sizeof(outp), "%d %b", &timeinfo);
            }
            if (days == "365") {
                strftime(outp, sizeof(outp), "%d %b '%y", &timeinfo);
            }
            if (days == "1") {
                strftime(outp, sizeof(outp), "%H:00 %d %b", &timeinfo);
            }
            xnotch[nidx-1].label = outp;
            xnotch[nidx].label = "[end]";
            //OutputDebugString("finished xmap and xnotch\n");
        }
    }
    minpricestr = (coords[min_idx].label.substr(0, coords[min_idx].label.find("@")));
    maxpricestr = (coords[max_idx].label.substr(0, coords[max_idx].label.find("@")));
}

void draw_graph(HDC devc) {

    SetTextColor(devc, RGB(120, 120, 120));
    SelectObject(devc, yaxisfont);
    int k = 0;
    SelectObject(devc, hilopen);

    for (k = 0; k < sizeof(coords); k++) {
        if (coords[k].label == "[end]") {
            break;
        }
        else {
            //SetPixelV(devc, gx+coords[k].x, gy+coords[k].y, RGB(0, 0, 0));
            if (k == 0) {
                MoveToEx(devc, gx + coords[k].x, gy - coords[k].y, NULL);
            }
            else {
                LineTo(devc, gx + coords[k].x, gy - coords[k].y);
            }
            
        }
    }
    
    //draw axes
    SelectObject(devc, axespen);

    //y axis
    MoveToEx(devc, gx , gy + coords[min_idx].y + ypadding, NULL);
    LineTo(devc, gx , gy  - coords[max_idx].y - ypadding);

    //min and max y notches
    MoveToEx(devc, gx - 20, gy - coords[min_idx].y, NULL);
    LineTo(devc, gx , gy - coords[min_idx].y);
    TextOut(devc, gx - notch_xpad, gy - coords[min_idx].y - 10, minpricestr.c_str(), minpricestr.size());

    MoveToEx(devc, gx - 20, gy - coords[max_idx].y, NULL);
    LineTo(devc, gx, gy - coords[max_idx].y);
    TextOut(devc, gx - notch_xpad, gy - coords[max_idx].y - 10 , maxpricestr.c_str(), maxpricestr.size());

    SelectObject(devc, axisfont);
    int g = 0;
    //x axis
    MoveToEx(devc, gx , gy + ypadding + coords[min_idx].y, NULL);
    LineTo(devc, gx  + gwidth + xpadding, gy + ypadding +  coords[min_idx].y);
    for (g = 0; g < sizeof(xnotch); g++) {
        if (xnotch[g].label != "[end]") {
            //normal notches without a label
            if (xnotch[g].label == "") {
                MoveToEx(devc, gx + xnotch[g].coord, gy + ypadding + coords[min_idx].y, NULL);
                LineTo(devc, gx + xnotch[g].coord, gy + ypadding + coords[min_idx].y + 5);
                //SetPixelV(devc, gx + g, gy + ypadding + coords[min_idx].y + 20, RGB(0, 0, 0));
                //OutputDebugString("xnotch\n");           
            }
            else {
                //labeled notches
                MoveToEx(devc, gx + xnotch[g].coord, gy + ypadding + coords[min_idx].y, NULL);
                LineTo(devc, gx + xnotch[g].coord, gy + ypadding + coords[min_idx].y + 10);
                TextOut(devc, gx - 20 + xnotch[g].coord, gy + ypadding + coords[min_idx].y + 20, xnotch[g].label.c_str(), xnotch[g].label.size());
            }

        }
        else {
            break;
        }
    }

    cfocus = -1;
    for (k = 0; k < sizeof(coords); k++) {
        if (coords[k].label == "[end]") {
            break;
        }
        else {
            if ( (mouse_x < (gx + coords[k].x + 10)) & (mouse_x > (gx + coords[k].x - 10)) & (mouse_y < (gy - coords[k].y + 10)) & (mouse_y > (gy - coords[k].y - 10))) {
                cfocus = k;
                //OutputDebugString("coord in focus\n");
                break;
            }
        }
    }

    //mouse over graph
    if (mouse_over_graph) {
        if (cfocus!=-1) {
            cfocus_x_final = gx + coords[cfocus].x;
            cfocus_y_final = gy - coords[cfocus].y;
            if (gx + coords[cfocus].x > (gx + gwidth + xpadding - 50)) {
                cfocus_x_final -= 100;
            }
            if (cfocus_y_final < (gy - coords[max_idx].y + 50)) {
                cfocus_y_final += 10;
            }
            TextOut(devc, cfocus_x_final, cfocus_y_final, coords[cfocus].label.c_str(), coords[cfocus].label.size());
        }
        else {
            //horizontal line
            MoveToEx(devc, gx, mouse_y, NULL);
            LineTo(devc, mouse_x, mouse_y);
            //vertical line
            MoveToEx(devc, mouse_x, gy + ypadding, NULL);
            LineTo(devc, mouse_x, mouse_y);
            //y axis label
            TextOut(devc, gx - notch_xpad, mouse_y, ymap[gy - mouse_y].c_str(), ymap[gy - mouse_y].size());
            //x axis label
            TextOut(devc, mouse_x - xpadding - xpadding - xpadding, gy + ypadding + coords[min_idx].y + 20, xmap[mouse_x - gx].c_str(), xmap[mouse_x - gx].size());

        }
    }

    SetTextColor(devc, RGB(0, 0, 0));
    SelectObject(devc, mainfont);
    
}

int WINAPI WinMain(_In_ HINSTANCE hThisInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszArgument, _In_ int nCmdShow)
{

    start_curl(str_price,final_url);

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = NULL;
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;
    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("btc"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        1024,                 /* The programs width */
        600,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );


    HWND hwndParent = hwnd; // Handle to the parent window

    //combo boxes: currency, coin, graph

    HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | CBS_AUTOHSCROLL | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
        180, 10, 55, 300, hwndParent, (HMENU) CRRC, hThisInstance, NULL);
    SendMessage(hWndComboBox, WM_SETFONT, WPARAM(mainfont), TRUE);
    int  k = 0;
    for (k = 0; k < (sizeof(currencies) / sizeof(*currencies)); k ++)
    {
        // Add string to combobox.
        SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>(currencies[k]));
    }
    // Send the CB_SETCURSEL message to display an initial item (WPARAM)
    //  in the selection field  
    SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)init_curr, (LPARAM)0);

    HWND hWndCOINComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | CBS_AUTOHSCROLL | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
        260, 10, 100, 300, hwndParent, (HMENU)COIN, hThisInstance, NULL);
    SendMessage(hWndCOINComboBox, WM_SETFONT, WPARAM(mainfont), TRUE);
    k = 0;
    for (k = 0; k < (sizeof(coins) / sizeof(*coins)); k++)
    {
        // Add string to combobox.
        SendMessage(hWndCOINComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>(coins[k][2]));
    }
    // Send the CB_SETCURSEL message to display an initial item (WPARAM)
    SendMessage(hWndCOINComboBox, CB_SETCURSEL, (WPARAM)init_coin, (LPARAM)0);

    HWND hWndGRAPHComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | CBS_AUTOHSCROLL | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
        450, 10, 70, 300, hwndParent, (HMENU)GRAPH, hThisInstance, NULL);
    SendMessage(hWndGRAPHComboBox, WM_SETFONT, WPARAM(mainfont), TRUE);
    // Add strings to combobox.
    SendMessage(hWndGRAPHComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>("off"));
    SendMessage(hWndGRAPHComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>("24H"));
    SendMessage(hWndGRAPHComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>("7D"));
    SendMessage(hWndGRAPHComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>("30D"));
    SendMessage(hWndGRAPHComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, reinterpret_cast<LPARAM>("1Y"));
    // Send the CB_SETCURSEL message to display an initial item (WPARAM)
    SendMessage(hWndGRAPHComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);


    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    SetTimer(hwnd, 1, update_interval, (TIMERPROC)NULL);
    //do this to trigger timer straight away, rather than wait for update_interval
    PostMessage(hwnd, WM_TIMER, 1, 0);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0) > 0)
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    HGDIOBJ cpen = NULL;
    switch (message)                 
    {
    case WM_DESTROY:
        stop_curl();
        DeleteObject(blackpen);
        DeleteObject(bluepen);
        KillTimer(hwnd, 1);
        PostQuitMessage(0);      
        break;
    case WM_PAINT:

        hdc = BeginPaint(hwnd, &ps);

        
        SelectObject(hdc, mainfont);
        //:1
        TextOut(hdc, 240, 12, coinptr, coin_sz);
        //graph:
        TextOut(hdc, 400, 12, glabelptr, glabelsz);

        if (gstatus != 0) {
            draw_graph(hdc);
        }

        if (cur_price > old_price) {
            SetTextColor(hdc, RGB(0, 200, 0));
        }
        else {
            if (cur_price < old_price) {
                SetTextColor(hdc, RGB(200, 0, 0));
            }
        }
        
        SelectObject(hdc, pricefont);
        //price
        TextOut(hdc, 15, 8, str_price.c_str(), str_price.size());

        EndPaint(hwnd, &ps);
        break;

    case WM_MOUSEMOVE:
        //LOWORD is x coord, HIWORD y
        //if the graph is on, detect when mouse is in graph area
        if (gstatus != 0) {

            old_mouse_x = mouse_x;
            old_mouse_y = mouse_y;
            mouse_x = LOWORD(lParam);
            mouse_y = HIWORD(lParam);
            mouse_dx = mouse_x - old_mouse_x;
            mouse_dy = mouse_y - old_mouse_y;

            if ((mouse_x > gx) & (mouse_x < (gx + gwidth + xpadding )) & (mouse_y > (gy - gheight - ypadding)) & (mouse_y< (gy + ypadding) )) {
                if (!mouse_over_graph) {
                    mouse_over_graph = true;
                    SetCursor(cross);
                }

                
                if (cfocus != -1) {
                    upd[0].x = cfocus_x_final;
                    upd[0].y = cfocus_y_final;

                    upd[1].x = upd[0].x + 200;
                    upd[1].y = upd[0].y;

                    upd[2].x = upd[1].x;
                    upd[2].y = upd[0].y + 200;

                    upd[3].x = upd[0].x;
                    upd[3].y = upd[0].y + 200;

                    upd[4].x = upd[0].x;
                    upd[4].y = upd[0].y;

                    upd[5].x = NULL;
                    upd[5].y = NULL;

                    upd[6].x = NULL;
                    upd[6].y = NULL;

                    upd[7].x = NULL;
                    upd[7].y = NULL;

                    upd[8].x = NULL;
                    upd[8].y = NULL;

                    upd[9].x = NULL;
                    upd[9].y = NULL;

                    upd[10].x = NULL;
                    upd[10].y = NULL;
                }
                else {

                /*
                        
                2------------3
                |            |
                1------0/10  |
                         |   |
                         |   |
                      8--9   4---5
                      |          |
                      7----------6
                         */
                    upd[0].x = mouse_x - xpadding - mouse_dx;
                    upd[0].y = mouse_y + (ypadding*2) - mouse_dy;

                    upd[1].x = gx - notch_xpad;
                    upd[1].y = mouse_y + (ypadding*2) - mouse_dy;

                    upd[2].x = gx - notch_xpad;
                    upd[2].y = mouse_y - ypadding - mouse_dy;

                    upd[3].x = mouse_x + xpadding - mouse_dx;
                    upd[3].y = mouse_y - ypadding - mouse_dy;

                    upd[4].x = upd[3].x;
                    upd[4].y = gy + (ypadding*3) ;

                    upd[5].x = mouse_x + xpadding + notch_xpad - mouse_dx;
                    upd[5].y = upd[4].y;

                    upd[6].x = mouse_x + xpadding + notch_xpad - mouse_dx;
                    upd[6].y = gy + ypadding + notch_ypad;

                    upd[7].x = mouse_x - mouse_dx - notch_xpad;
                    upd[7].y = upd[6].y;

                    upd[8].x = mouse_x - mouse_dx - notch_xpad;
                    upd[8].y = upd[4].y;

                    upd[9].x = upd[0].x;
                    upd[9].y = upd[4].y;

                    upd[10].x = upd[0].x;
                    upd[10].y = upd[0].y;
                }


                //TextOut(devc, mouse_x, gy + notch_ypad);
                //TextOut(devc, gx - notch_xpad, mouse_y);
                HRGN upd_r = CreatePolygonRgn(upd, 11, WINDING);
                //UpdateWindow(hwnd);
                RedrawWindow(hwnd, NULL, upd_r, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
                //UpdateWindow(hwnd);
                DeleteObject(upd_r);
                
            }
            else {
                if (mouse_over_graph) {
                    //OutputDebugString("just left graph\n");
                    mouse_over_graph = false;
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
                }
            }
        }

        break;
    case WM_SETCURSOR:
        if (!mouse_over_graph) {
            SetCursor(arrow);
        }
        break;
    case WM_COMMAND:
        if (HIWORD(wParam) == CBN_SELCHANGE)
            // If the user makes a selection from the list:
            //   Send CB_GETCURSEL message to get the index of the selected list item.
            //   Send CB_GETLBTEXT message to get the item.
            //   update current API url used
        {
            int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            //TCHAR  ListItem[256];
            //(TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT, (WPARAM)ItemIndex, (LPARAM)ListItem);

            if ((LOWORD(wParam) == COIN) || (LOWORD(wParam) == CRRC)) {

                if (LOWORD(wParam) == CRRC) {
                    //ids = "bitcoin";
                    vcs = currencies[ItemIndex];
                }
                if (LOWORD(wParam) == COIN) {
                    ids = coins[ItemIndex][0];
                    //vcs = currencies[ItemIndex];
                }

                stop_curl();
                final_url = price_url + "?ids=" + ids + "&vs_currencies=" + vcs;
                start_curl(str_price, final_url);
                //get data even if graph is off, so its ready if the graph is turned on
                get_graph(ids, vcs, api_days[(gstatus-1)]);
                ytxtauto();
                if (gstatus != 0) {
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
                }

            }

            if (LOWORD(wParam) == GRAPH) {
                gstatus = ItemIndex;
                if (gstatus != 0) {
                    get_graph(ids, vcs, api_days[(gstatus - 1)]);
                    ytxtauto();
                }
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
            }

            //MessageBox(hwnd, ListItem, Pairs[ItemIndex][1], MB_OK);
            
            //current_url = Pairs[ItemIndex][1];
            
        }
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            
            str_price = "";
            curl_easy_perform(curl);

            int pstart = str_price.find(vcs) + 5;
            str_price = str_price.substr(pstart, str_price.find('}')-pstart);
            old_price = cur_price;
            cur_price = stod(str_price);
            str_price = prettystr(str_price);
            SetWindowText(hwnd, str_price.c_str());
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
            return 0;
        }
    default:                      /* for messages that we don't deal with */
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}



